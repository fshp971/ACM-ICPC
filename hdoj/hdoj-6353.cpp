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
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 1e5;
const int Step = 17;

int n, m, dep[maxn+5], st[maxn+5][Step+2];
int top, h[maxn+5], e[maxn*2+5], nex[maxn*2+5];
void AddEdge(int u, int v) {
    e[++top] = v, nex[top] = h[u], h[u] = top;
    e[++top] = u, nex[top] = h[v], h[v] = top;
}

bool vist[maxn+5];
int sz[maxn+5], msz[maxn+5], fa[maxn+5];
int q[maxn+5];
int FindRoot(int x) {
    int s = 1, t = 1;
    q[1] = x; fa[x] = 0;
    while(s<=t) {
        x = q[s++]; sz[x] = 1, msz[x] = 0;
        for(int i=h[x];i;i=nex[i]) {
            int u = e[i];
            if(!vist[u] && u!=fa[x])
                q[++t] = u, fa[u] = x;
        }
    }
    for(int i = t; i >= 1; --i) {
        x = q[i];
        msz[x] = max(msz[x], t-sz[x]);
        if((msz[x]<<1) <= t) return x;
        sz[fa[x]] += sz[x], msz[fa[x]] = max(msz[fa[x]], sz[x]);
    }
    assert(false);
    return 0;
}

int rot[maxn+5][Step+5];
int idx[maxn+5][Step+5], idx2[maxn+5][Step+5];
int tot, cnt[maxn*Step*2+5], mxd[maxn+5][Step+5];
int dis[maxn+5][Step+5], in[maxn+5], out[maxn+5], dfn[maxn+5], DFN;
void dfs2(int x, int p, int d, int depth) {
    dfn[++DFN] = x, in[x] = DFN, dis[x][depth] = d;
    mxd[x][depth] = d;
    for(int i=h[x];i;i=nex[i]) {
        int u = e[i];
        if(!vist[u] && u!=p) {
            dfs2(u, x, d+1, depth);
            mxd[x][depth] = max(mxd[x][depth], mxd[u][depth]);
        }
    }
    out[x] = DFN;
}
void Solve(int x, int d) {
    x = FindRoot(x);
    DFN = 0;
    dfs2(x,0,0,d);
    idx[x][d] = idx2[x][d] = tot+1; tot += mxd[x][d]+1;
    REP(i,0,mxd[x][d]) cnt[i+idx[x][d]] = 0;
    REP(i,1,DFN) ++cnt[ idx[x][d] + dis[dfn[i]][d] ], rot[dfn[i]][d] = x;
    REP(i,1,mxd[x][d]) cnt[i+idx[x][d]] += cnt[i-1+idx[x][d]];
    for(int k=h[x];k;k=nex[k]) {
        int u = e[k];
        if(vist[u]) continue;
        idx[u][d] = idx[x][d], idx2[u][d] = tot+1, tot += mxd[u][d]+1;
        REP(i,0,mxd[u][d]) cnt[i+idx2[u][d]] = 0;
        for(int i = in[u]; i <= out[u]; ++i) {
            ++cnt[ idx2[u][d] + dis[dfn[i]][d] ];
            idx[dfn[i]][d] = idx[u][d], idx2[dfn[i]][d] = idx2[u][d];
            mxd[dfn[i]][d] = mxd[u][d];
        }
        REP(i,1,mxd[u][d]) cnt[i+idx2[u][d]] += cnt[i-1+idx2[u][d]];
    }
    vist[x] = 1;
    for(int i=h[x];i;i=nex[i]) {
        int u = e[i];
        if(!vist[u]) Solve(u, d+1);
    }
}

void dfs(int x, int p, int d) {
    mem(st[x],0);
    st[x][0] = p, dep[x] = d;
    for(int i = 0; st[x][i]; ++i)
        st[x][i+1] = st[st[x][i]][i];
    for(int i=h[x];i;i=nex[i]) {
        int u = e[i];
        if(u != p) dfs(u, x, d+1);
    }
}

int LCA(int u, int v) {
    if(u == v) return u;
    if(dep[u] < dep[v]) swap(u,v);
    int d = dep[u]-dep[v];
    for(int i = Step; i >= 0; --i)
        if(d>>i&1) u = st[u][i];
    if(u == v) return u;
    for(int i = Step; i >= 0; --i)
        if(st[u][i] != st[v][i])
            u = st[u][i], v = st[v][i];
    return st[u][0];
}

inline int Go(int u, int d) {
    for(int i = Step; i >= 0; --i)
        if(d>>i&1) u = st[u][i];
    return u;
}

int Calc(int u, int d) {
    int ret = 0;
    for(int i = 0;; ++i) {
        if(dis[u][i]<=d) ret += cnt[ idx[u][i] + min(mxd[rot[u][i]][i], d-dis[u][i]) ];
        if(idx[u][i] == idx2[u][i]) break;
        if(dis[u][i]<=d) ret -= cnt[ idx2[u][i] + min(d-dis[u][i], mxd[u][i]) ];
    }
    return ret;
}

int Calc(int u, int v, int d) {
    int ret = 0;
    bool fu = 1, fv = 1;
    for(int i = 0; fu||fv;++i) {
        int du = d-dis[u][i], dv = d-dis[v][i];
        if(fu&&fv && du>=0&&dv>=0 && idx[u][i]==idx[v][i]) {
            if(idx[u][i]==idx2[u][i]) {
                int rk = min(mxd[u][i], du);
                ret += cnt[idx[u][i]+rk] - cnt[idx2[v][i]+min(mxd[v][i],rk)];
            }
            else if(idx[v][i]==idx2[v][i]) {
                int rk = min(mxd[v][i], dv);
                ret += cnt[idx[v][i]+rk] - cnt[idx2[u][i]+min(mxd[u][i],rk)];
            }
            else if(idx2[u][i]==idx2[v][i]) {
                int rk = min(mxd[rot[u][i]][i], max(du,dv));
                if(rk>=0)
                    ret += cnt[idx[u][i]+rk] - cnt[idx2[u][i]+min(mxd[u][i],rk)];
            }
            else {
                int rk = min(mxd[rot[u][i]][i], max(du,dv));
                if(rk>=0) {
                    ret += cnt[idx[u][i]+rk];
                    ret -= cnt[idx2[u][i]+min(mxd[u][i],rk)];
                    ret -= cnt[idx2[v][i]+min(mxd[v][i],rk)];
                }
            }
        }
        else {
            if(fu&&du>=0) {
                ret += cnt[idx[u][i] + min(mxd[rot[u][i]][i], du)];
                if(idx[u][i]!=idx2[u][i])
                    ret -= cnt[ idx2[u][i] + min(d-dis[u][i], mxd[u][i]) ];
            }
            if(fv&&dv>=0) {
                ret += cnt[idx[v][i] + min(mxd[rot[v][i]][i], dv)];
                if(idx[v][i]!=idx2[v][i])
                    ret -= cnt[ idx2[v][i] + min(d-dis[v][i], mxd[v][i]) ];
            }
        }
        if(fu&&idx[u][i]==idx2[u][i]) fu = 0;
        if(fv&&idx[v][i]==idx2[v][i]) fv = 0;
    }
    return ret;
}

int main() {
    int _; scanf("%d", &_);
    while(_--) {
        scanf("%d%d", &n, &m);
        REP(i,1,n) h[i] = 0, vist[i] = 0;
        top = 0;
        for(int i = 1, u, v; i < n; ++i) {
            scanf("%d%d", &u, &v);
            AddEdge(u,v);
        }
        dfs(1,0,1);
        tot = 0;
        Solve(1,0);
        int ans = 0;
        while(m--) {
            int u, v, d;
            scanf("%d%d%d", &u, &v, &d);
            u = (u+ans)%n+1;
            v = (v+ans)%n+1;
            d = (d+ans)%n;

            int x, y, lca = LCA(u,v), di = dep[u]+dep[v]-dep[lca]*2;
            if((di>>1) <= dep[u]-dep[lca]) x = Go(u,di>>1);
            else x = Go(v,di-(di>>1));
            if(((di+1)>>1) <= dep[u]-dep[lca]) y = Go(u,(di+1)>>1);
            else y = Go(v,di-((di+1)>>1));

            ans = Calc(u,d) + Calc(v,d);
            if(x==y) ans -= Calc(x, d-((di+1)>>1));
            else ans -= Calc( x, y, d-((di+1)>>1) );
            printf("%d\n", ans);
        }
    }
    return 0;
}
