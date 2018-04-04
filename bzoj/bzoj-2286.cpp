#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<cassert>
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

const int maxn = 250000;
const int MaxStep = 18;

int n, m, top = 0, DFN[maxn + 5], dep[maxn + 5];
int T, vist[maxn + 5];
vector< pair<int,int> > G[maxn + 5], G2[maxn + 5];

int st[maxn + 5][MaxStep + 2];
int wi[maxn + 5][MaxStep + 2];

void dfs(int x, int p, int w) {
    dep[x] = dep[p] + 1, st[x][0] = p, wi[x][0] = w;
    for(int i = 0; st[x][i]; ++i) {
        st[x][i+1] = st[st[x][i]][i];
        wi[x][i+1] = min(wi[x][i], wi[st[x][i]][i]);
    }
    DFN[x] = ++top;
    for(int i = 0; i < G[x].size(); ++i) if(G[x][i].fi != p) dfs(G[x][i].fi, x, G[x][i].se);
}

pair<int,int> LCA(int u, int v) {
    if(u == v) return MP(u,0);
    if(dep[u] < dep[v]) swap(u,v);
    int d = dep[u] - dep[v];
    int w = 1 << 30;
    for(int i = MaxStep - 1; i >= 0; --i)
        if(d>>i&1)
            w = min(w, wi[u][i]), u = st[u][i];
    if(u == v) return MP(u,w);
    for(int i = MaxStep - 1; i >= 0; --i)
        if(st[u][i] != st[v][i])
            w = min( w, min(wi[u][i], wi[v][i]) ), u = st[u][i], v = st[v][i];
    return MP( st[u][0], min(w, min(wi[u][0], wi[v][0])) );
}

const bool cmp(const int &a, const int &b) { return DFN[a] < DFN[b]; }

vector<int> seg;
stack<int> sta;
void Build() {
    sort(seg.begin(), seg.end(), cmp);
    sta.push(1);
    for(int i = 0; i < seg.size(); ++i) {
        int x = sta.top(), nx; sta.pop();
        pair<int,int> tmp = LCA(x, seg[i]), tmp2;
        while(!sta.empty() && dep[nx = sta.top()] >= dep[tmp.fi]) {
            tmp2 = LCA(nx, x);
            if(vist[nx] != T) G2[nx].clear(), vist[nx] = T;
            G2[nx].PB( MP(x, tmp2.se) );
            x = nx, sta.pop();
        }
        if(x != tmp.fi) {
            tmp2 = LCA(x, tmp.fi);
            if(vist[tmp.fi] != T) G2[tmp.fi].clear(), vist[tmp.fi] = T;
            G2[tmp.fi].PB( MP(x, tmp2.se) );
            sta.push(tmp.fi);
        }
        else sta.push(x);
        sta.push(seg[i]);
    }
    int x = sta.top(); sta.pop();
    while(!sta.empty()) {
        int nx = sta.top(); sta.pop();
        if(vist[nx] != T) G2[nx].clear(), vist[nx] = T;
        pair<int, LL> tmp = LCA(nx, x);
        G2[nx].PB( MP(x, tmp.se) );
        x = nx;
    }
}

LL dp[maxn + 5][2];
int flag[maxn + 5];
void dfs2(int x, int p) {
    int c = 0;
    dp[x][0] = 0, dp[x][1] = 0;
    for(int i = 0; i < G2[x].size(); ++i)
        if(G2[x][i].fi != p) {
            int nx = G2[x][i].fi;
            dfs2(nx, x);
            dp[x][1] += dp[nx][1];
            dp[x][0] += min(dp[nx][0], dp[nx][1] + G2[x][i].se);
        }
    if(flag[x] == T) dp[x][0] = 1LL << 50;
}

int main() {
    scanf("%d", &n);
    for(int i = 1, u, v, w; i < n; ++i) {
        scanf("%d%d%d", &u, &v, &w);
        G[u].PB(MP(v,w)), G[v].PB(MP(u,w));
    }
    dfs(1,0,0);
    scanf("%d", &m);
    for(T = 1; T <= m; ++T) {
        seg.clear();
        int a, b;
        scanf("%d", &a);
        while(a--) scanf("%d", &b), seg.PB(b), flag[b] = T;
        Build();
        dfs2(1, -1);
        printf("%lld\n", dp[1][0]);
    }
    return 0;
}
