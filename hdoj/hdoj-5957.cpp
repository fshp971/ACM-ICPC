#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<cassert>
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<queue>
#include<utility>
#include<bitset>
#include<complex>
#include<map>
#include<set>
#include<unordered_map>
#include<unordered_set>
#include<stack>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define PER(i,a,b) for(int i=a; i>=b; --i)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
#define lson (x<<1)
#define rson (x<<1|1)
#define mid ((l+r)>>1)
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 1e5;
const int maxnode = maxn<<2;

int n, fa[maxn+5], fp[maxn+5], id[maxn+5];
int L1[maxn+5], R1[maxn+5], L2[maxn+5], R2[maxn+5];
int uu, vv;
vector<int> G[maxn+5];
queue<pii> q;

LL tr[maxnode+5], lz[maxnode+5];
void Build(int x, int l, int r) {
    tr[x] = lz[x] = 0;
    if(l < r) {
        Build(lson, l, mid);
        Build(rson, mid+1, r);
    }
}

void PushDown(int x, int l, int r) {
    lz[lson] += lz[x];
    tr[lson] += LL(mid-l+1) * lz[x];

    lz[rson] += lz[x];
    tr[rson] += LL(r-mid) * lz[x];

    lz[x] = 0;
}

void Add(int x, int l, int r, int ll, int rr, int d) {
    if(ll<=l && r<=rr) lz[x] += d, tr[x] += LL(r-l+1)*d;
    else {
        PushDown(x,l,r);
        if(ll<=mid) Add(lson, l, mid, ll, rr, d);
        if(mid<rr) Add(rson, mid+1, r, ll, rr, d);
        tr[x] = tr[lson]+tr[rson];
    }
}

LL Que(int x, int l, int r, int ll, int rr) {
    if(ll<=l && r<=rr) return tr[x];
    PushDown(x,l,r);
    LL ret = 0;
    if(ll<=mid) ret += Que(lson, l, mid, ll, rr);
    if(mid<rr) ret += Que(rson, mid+1, r, ll, rr);
    return ret;
}

int find(int x) { return fa[x]==x ? x : fa[x] = find(fa[x]); }

void dfs(int x, int p) {
    fp[x] = p;
    L1[x] = L2[x] = (1<<30);
    R1[x] = R2[x] = -(1<<30);
    for(auto y : G[x]) if(y!=p) {
        dfs(y,x);
        L1[x] = min(L1[x], id[y]);
        R1[x] = max(R1[x], id[y]);
        L2[x] = min(L2[x], L1[y]);
        R2[x] = max(R2[x], R1[y]);
    }
}

int main() {
    int _; scanf("%d", &_);
    char ord[10];
    while(_--) {
        scanf("%d", &n);
        REP(i,1,n) G[i].clear(), fa[i] = i;
        for(int i = 1, u,v; i <= n; ++i) {
            scanf("%d%d", &u, &v);
            if(find(u) == find(v)) uu = u, vv = v;
            else {
                fa[find(u)] = find(v);
                G[u].PB(v), G[v].PB(u);
            }
        }
        int DFN = 0;
        q.push( pii(1,0) );
        while(!q.empty()) {
            int x = q.front().fi, p = q.front().se;
            q.pop();
            id[x] = ++DFN;
            for(auto y : G[x]) if(y!=p) {
                q.push( pii(y,x) );
            }
        }
        L1[0] = L2[0] = (1<<30);
        R1[0] = R2[0] = -(1<<30);
        dfs(1,0);
        Build(1,1,n);
        int T; scanf("%d", &T);
        while(T--) {
            int u, k, d;
            scanf("%s%d%d", ord, &u, &k);
            if(ord[0] == 'M') {
                scanf("%d", &d);
                Add(1, 1, n, id[u], id[u], d);
                if(k>=1) {
                    if(L1[u]<=R1[u]) Add(1, 1, n, L1[u], R1[u], d);
                    if(fp[u]) Add(1, 1, n, id[fp[u]], id[fp[u]], d);
                    if(u==vv) swap(uu,vv);
                    if(u==uu) Add(1, 1, n, id[vv], id[vv], d);
                }
                if(k>=2) {
                    if(L2[u]<=R2[u]) Add(1, 1, n, L2[u], R2[u], d);
                    if(fp[u]) {
                        Add(1, 1, n, L1[fp[u]], R1[fp[u]], d);
                        Add(1, 1, n, id[u], id[u], -d);
                        if(fp[fp[u]]) Add(1, 1, n, id[ fp[fp[u]] ], id[ fp[fp[u]] ], d);
                    }
                    if(uu==fp[u] || vv==fp[u]) {
                        if(vv==fp[u]) swap(uu,vv);
                        if((id[vv]<L1[u] || id[vv]>R1[u]) && (id[vv]<L2[u] || id[vv]>R2[u]))
                            Add(1, 1, n, id[vv], id[vv], d);
                    }
                    else if((L1[u]<=id[uu] && id[uu]<=R1[u]) || (L1[u]<=id[vv] && id[vv]<=R1[u])) {
                        if(L1[u]<=id[vv] && id[vv]<=R1[u]) swap(uu,vv);
                        if( vv!=fp[fp[u]] && (id[vv]<L1[u]||id[vv]>R1[u]) && (id[vv]<L2[u]||id[vv]>R2[u]) && (id[vv]<L1[fp[u]]||id[vv]>R1[fp[u]]) )
                            Add(1, 1, n, id[vv], id[vv], d);
                    }
                    else if(uu==u || vv==u) {
                        if(vv==u) swap(uu,vv);
                        if(L1[vv]<=R1[vv]) Add(1, 1, n, L1[vv], R1[vv], d);
                        if(fp[vv]) Add(1, 1, n, id[fp[vv]], id[fp[vv]], d);
                        if( fp[fp[u]]==vv || fp[vv]==fp[u]) {
                            Add(1, 1, n, id[vv], id[vv], -d);
                            Add(1, 1, n, id[fp[u]], id[fp[u]], -d);
                        }
                        else if(fp[ fp[fp[u]] ]==vv || fp[vv]==fp[fp[u]])
                            Add(1, 1, n, id[fp[fp[u]]], id[fp[fp[u]]], -d);
                        else if(fp[vv] && L1[fp[u]]<=id[fp[vv]] && id[fp[vv]]<=R1[fp[u]])
                            Add(1, 1, n, id[fp[vv]], id[fp[vv]], -d);
                        else if(L2[u]<=id[vv] && id[vv]<=R2[u]) {
                            Add(1, 1, n, id[vv], id[vv], -d);
                            Add(1, 1, n, id[fp[vv]], id[fp[vv]], -d);
                        }
                        else if(fp[vv] && L2[u]<=id[fp[vv]] && id[fp[vv]]<=R2[u])
                            Add(1, 1, n, id[fp[vv]], id[fp[vv]], -d);
                    }
                }
            }
            else {
                LL ans = 0;
                ans += Que(1, 1, n, id[u], id[u]);
                if(k>=1) {
                    if(L1[u]<=R1[u]) ans += Que(1, 1, n, L1[u], R1[u]);
                    if(fp[u]) ans += Que(1, 1, n, id[fp[u]], id[fp[u]]);
                    if(u==vv) swap(uu,vv);
                    if(u==uu) ans += Que(1, 1, n, id[vv], id[vv]);
                }
                if(k>=2) {
                    if(L2[u]<=R2[u]) ans += Que(1, 1, n, L2[u], R2[u]);
                    if(fp[u]) {
                        ans += Que(1, 1, n, L1[fp[u]], R1[fp[u]]);
                        ans -= Que(1, 1, n, id[u], id[u]);
                        if(fp[fp[u]]) ans += Que(1, 1, n, id[ fp[fp[u]] ], id[ fp[fp[u]] ]);
                    }
                    if(uu==fp[u] || vv==fp[u]) {
                        if(vv==fp[u]) swap(uu,vv);
                        if((id[vv]<L1[u] || id[vv]>R1[u]) && (id[vv]<L2[u] || id[vv]>R2[u]))
                            ans += Que(1, 1, n, id[vv], id[vv]);
                    }
                    else if((L1[u]<=id[uu] && id[uu]<=R1[u]) || (L1[u]<=id[vv] && id[vv]<=R1[u])) {
                        if(L1[u]<=id[vv] && id[vv]<=R1[u]) swap(uu,vv);
                        if( vv!=fp[fp[u]] && (id[vv]<L1[u]||id[vv]>R1[u]) && (id[vv]<L2[u]||id[vv]>R2[u]) && (id[vv]<L1[fp[u]]||id[vv]>R1[fp[u]]) )
                            ans += Que(1, 1, n, id[vv], id[vv]);
                    }
                    else if(uu==u || vv==u) {
                        if(vv==u) swap(uu,vv);
                        if(L1[vv]<=R1[vv]) ans += Que(1, 1, n, L1[vv], R1[vv]);
                        if(fp[vv]) ans += Que(1, 1, n, id[fp[vv]], id[fp[vv]]);
                        if( fp[fp[u]]==vv || fp[vv]==fp[u]) {
                            ans -= Que(1, 1, n, id[vv], id[vv]);
                            ans -= Que(1, 1, n, id[fp[u]], id[fp[u]]);
                        }
                        else if(fp[ fp[fp[u]] ]==vv || fp[vv]==fp[fp[u]])
                            ans -= Que(1, 1, n, id[fp[fp[u]]], id[fp[fp[u]]]);
                        else if(fp[vv] && L1[fp[u]]<=id[fp[vv]] && id[fp[vv]]<=R1[fp[u]])
                            ans -= Que(1, 1, n, id[fp[vv]], id[fp[vv]]);
                        else if(L2[u]<=id[vv] && id[vv]<=R2[u]) {
                            ans -= Que(1, 1, n, id[vv], id[vv]);
                            ans -= Que(1, 1, n, id[fp[vv]], id[fp[vv]]);
                        }
                        else if(fp[vv] && L2[u]<=id[fp[vv]] && id[fp[vv]]<=R2[u])
                            ans -= Que(1, 1, n, id[fp[vv]], id[fp[vv]]);
                    }
                }
                printf("%lld\n", ans);
            }
        }
    }
    return 0;
}
