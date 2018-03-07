#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 5e4, maxq = 1e5;

struct DSU {
    int fa[maxn + 5], sz[maxn + 5];
    void Init(int n) { REP(i,1,n) fa[i] = i, sz[i] = 1; }
    int Find(int x) { return fa[x] == x ? x : fa[x] = Find(fa[x]); }
    int Merge(int x, int y) {
        x = Find(x), y = Find(y);
        if(x == y) return 0;
        int del = sz[x] * sz[y];
        if(sz[x] < sz[y]) swap(x,y);
        fa[y] = x, sz[x] += sz[y];
        return del;
    }
} dsu1, dsu2;

int n, m, sz, st[maxn + 5], ed[maxn + 5];
vector<int> G[maxn + 5];
int uu[(maxn<<1) + 5], vv[(maxn<<1) + 5];
int ql[maxq + 5], qr[maxq + 5], qd[maxq + 5];
int ans[maxq + 5];

bool cmp(const int &a, const int &b) {
    if((ql[a]-1)/sz == (ql[b]-1)/sz) return qr[a] < qr[b];
    return (ql[a]-1)/sz < (ql[b]-1)/sz;
}

int main() {
    int T, Q;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d%d", &n, &m, &Q);
        REP(i,1,n) G[i].clear();
        for(int i = 1, u, v; i <= m; ++i) {
            scanf("%d%d", &u, &v);
            G[u].PB(v), G[v].PB(u);
        }
        m = 0;
        for(int i = 1; i <= n; ++i) {
            st[i] = m+1;
            for(auto it : G[i])
                uu[++m] = i, vv[m] = it;
            ed[i] = m;
        }
        sz = sqrt(m);
        for(int i = 1, l, r; i <= Q; ++i) {
            scanf("%d%d", &l, &r);
            ql[i] = st[l], qr[i] = ed[r], qd[i] = i;
        }
        sort(qd + 1, qd + 1 + Q, cmp);
        dsu1.Init(n);
        for(int i = 1, pt = 1; (i-1)*sz < m && pt <= Q; ++i) {
            int r = min(i*sz, m);
            if(ql[qd[pt]] > r) continue;
            while(pt <= Q && qr[qd[pt]] <= r) {
                ans[qd[pt]] = 0;
                for(int k = ql[qd[pt]]; k <= qr[qd[pt]]; ++k) {
                    if(uu[ql[qd[pt]]] <= vv[k] && vv[k] <= uu[qr[qd[pt]]])
                        ans[qd[pt]] += dsu1.Merge(uu[k], vv[k]);
                }
                for(int k = ql[qd[pt]]; k <= qr[qd[pt]]; ++k) {
                    dsu1.fa[uu[k]] = uu[k], dsu1.fa[vv[k]] = vv[k];
                    dsu1.sz[uu[k]] = dsu1.sz[vv[k]] = 1;
                }
                ++pt;
            }
            if(pt > Q || ql[qd[pt]] > r) continue;
            int t = r+1, sum = 0;
            dsu2.Init(n);
            while(pt <= Q && ql[qd[pt]] <= r) {
                while(t <= qr[qd[pt]]) {
                    if(uu[r+1] <= vv[t] && vv[t] <= uu[qr[qd[pt]]])
                        sum += dsu2.Merge(uu[t], vv[t]);
                    ++t;
                }
                for(int k = ql[qd[pt]], fk; k <= r; ++k) {
                    fk = dsu2.Find(uu[k]), dsu1.sz[fk] = dsu2.sz[fk], dsu1.fa[uu[k]] = fk;
                    fk = dsu2.Find(vv[k]), dsu1.sz[fk] = dsu2.sz[fk], dsu1.fa[vv[k]] = fk;
                }
                ans[qd[pt]] = sum;
                for(int k = ql[qd[pt]]; k <= r; ++k) {
                    if(uu[ql[qd[pt]]] <= vv[k] && vv[k] <= uu[qr[qd[pt]]]) {
                        ans[qd[pt]] += dsu1.Merge(uu[k], vv[k]);
                    }
                }
                for(int k = ql[qd[pt]], fk; k <= r; ++k) {
                    fk = dsu2.Find(uu[k]), dsu1.fa[fk] = fk, dsu1.sz[fk] = 1, dsu1.fa[uu[k]] = uu[k];
                    fk = dsu2.Find(vv[k]), dsu1.fa[fk] = fk, dsu1.sz[fk] = 1, dsu1.fa[vv[k]] = vv[k];
                }
                ++pt;
            }
        }
        for(int i = 1; i <= Q; ++i) printf("%d\n", ans[i]);
    }
    return 0;
}
