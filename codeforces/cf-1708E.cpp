#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define PER(i,a,b) for(int i = a; i >= b; --i)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
typedef long long LL;
typedef long double LD;

const int maxn = 1e5;
const int maxm = 2e5;
const int maxk = 16;

int n, m;
int uu[maxm+5], vv[maxm+5], in[maxm+5];

vector<int> G[maxn+5];
int st[maxn+5][maxk+2], lz[maxn+5], dep[maxn+5];
char ans[maxn+5];

struct DSU {
    vector<int> fa;
    int n;
    DSU(int _n): n(_n), fa(_n+1) { for(int i = 1; i <= n; ++i) fa[i] = i; }
    int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
    void merge(int x, int y) { fa[find(x)] = find(y); }
};

void dfs(int x, int p) {
    st[x][0] = p, dep[x] = dep[p]+1;
    for(int i = 0; st[x][i]; ++i)
        st[x][i+1] = st[ st[x][i] ][i];
    for(auto y : G[x]) if(y != p)
        dfs(y,x);
}

void dfs2(int x, int p, int c) {
    c += lz[x];
    ans[x] = (c == m-n+1) + '0';
    for(auto y : G[x]) if(y != p)
        dfs2(y,x,c);
}

int main() {
    scanf("%d%d", &n, &m);
    DSU dsu(n);
    REP(i,1,m) {
        scanf("%d%d", uu+i, vv+i);
        if(dsu.find(uu[i]) == dsu.find(vv[i])) continue;
        G[ uu[i] ].PB( vv[i] );
        G[ vv[i] ].PB( uu[i] );
        in[i] = 1;
        dsu.merge(uu[i], vv[i]);
    }
    dfs(1,0);
    REP(i,1,m) {
        if(in[i]) continue;
        int u = uu[i], v = vv[i];
        if(dep[u] == dep[v]) { ++lz[u], ++lz[v]; continue; }
        if(dep[u] > dep[v]) swap(u,v);
        int dis = dep[v]-dep[u]-1, hh = v;
        for(int k = 0; dis; ++k, dis>>=1)
            if(dis&1) hh = st[hh][k];
        if(st[hh][0] == u) ++lz[1], --lz[hh], ++lz[v];
        else ++lz[u], ++lz[v];
    }
    dfs2(1,0,0);
    ans[n+1] = '\0';
    printf("%s\n", ans+1);
    return 0;
}
