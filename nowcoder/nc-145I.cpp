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
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 2e5;
const int P = 1e9 + 7;

int n, D;
vector<int> G[maxn + 5];

bool vist[maxn + 5];
int ti[maxn + 5];
int sz[maxn + 5], msz[maxn + 5];

int dfn[maxn + 5], DFN;
int in[maxn + 5], out[maxn + 5];
int dep[maxn + 5], fa[maxn + 5], mxd[maxn + 5];
int dc[maxn + 5], S[maxn + 5];
int dc2[maxn + 5], S2[maxn + 5];
int ini[maxn + 5];
unordered_map<int,int> cnt[maxn + 5];

int que[maxn + 5];
int FindRoot(int x) {
    int s = 1, t = 1;
    que[1] = x, fa[x] = 0;
    while(s <= t) {
        x = que[s++]; sz[x] = 1; msz[x] = 0;
        for(auto it : G[x]) {
            if(vist[it] || it == fa[x]) continue;
            que[++t] = it, fa[it] = x;
        }
    }
    for(int i = t; i >= 1; --i) {
        x = que[i];
        msz[x] = max(msz[x], t-sz[x]);
        if((msz[x]<<1) <= t) return x;
        sz[fa[x]] += sz[x], msz[fa[x]] = max(msz[fa[x]], sz[x]);
    }
    assert(false);
    return 0;
}

void dfs(int x, int p, int d) {
    in[x] = ++DFN, dfn[DFN] = x;
    fa[x] = p, dep[x] = mxd[x] = d;
    for(auto it : G[x]) {
        if(vist[it] || it == p) continue;
        dfs(it, x, d+1);
        mxd[x] = max(mxd[x], mxd[it]);
    }
    out[x] = DFN;
}

void Solve(int x) {
    x = FindRoot(x);
    DFN = 0;
    dfs(x, 0, 0);
    REP(i,0,mxd[x]) dc[i] = 0;
    for(int i = 1; i <= DFN; ++i) {
        dc[ dep[dfn[i]] ] += ti[ dfn[i] ];
    }
    S[0] = dc[0];
    REP(i,1,mxd[x]) S[i] = S[i-1] + dc[i];

    ini[x] += S[min(D-1,mxd[x])];

    for(auto it : G[x]) {
        if(vist[it]) continue;
        REP(i,1,mxd[it]) dc2[i] = 0;
        for(int i = in[it]; i <= out[it]; ++i)
            dc2[ dep[dfn[i]] ] += ti[ dfn[i] ];

        if(D <= mxd[it]) cnt[x][it] += dc2[D];

        for(int i = 1; i <= mxd[it]; ++i) S2[i] = S2[i-1] + dc2[i];
        for(int i = in[it]; i <= out[it]; ++i) {
            int &u = dfn[i];
            if(0<=D-1-dep[u])
                ini[u] += S[ min(D-1-dep[u],mxd[x]) ] - S2[ min(D-1-dep[u],mxd[it]) ];
            if(0<=D-dep[u] && D-dep[u]<=mxd[x])
                cnt[u][fa[u]] += dc[D-dep[u]] - ( (D-dep[u]<=mxd[it]) ? dc2[D-dep[u]] : 0 );
        }
    }

    vist[x] = 1;
    for(auto it : G[x])
        if(!vist[it]) Solve(it);
}

LL pw[maxn + 5];
int main() {
    pw[0] = 1;
    REP(i,1,maxn) pw[i] = (pw[i-1]<<1) % P;
    scanf("%d", &n);
    for(int i = 1, u, v; i < n; ++i) {
        scanf("%d%d", &u, &v);
        G[u].PB(i+n); G[i+n].PB(v);
        G[v].PB(i+n); G[i+n].PB(u);
    }
    scanf("%d", &D);
    REP(i,1,n) ti[i] = 1;
    Solve(1);
    LL ans = 0;
    for(int i = 1; i < (n<<1); ++i) {
        LL tmp = 1;
        int c = 0;
        for(auto it : cnt[i]) {
            tmp = (tmp + pw[it.se]-1+P) % P;
            c += it.se;
        }
        tmp = (pw[c] - tmp + P) % P;
        ans = (ans + tmp * pw[ ini[i] ]) % P;
    }
    printf("%lld\n", ans);
    return 0;
}
