#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

const int maxn = 3e5, maxk = 20;

int n, m, si[maxn+5], ti[maxn+5], wi[maxn+5];
int st[maxn+5][maxk+2], dep[maxn+5];
int ans[maxn+5], ct1[maxn*3+5], ct2[maxn*3+5];
vector<int> in_val1[maxn+5], in_val2[maxn+5];
vector<int> out_val1[maxn+5], out_val2[maxn+5];
vector<int> G[maxn+5];

void dfs(int x, int p) {
    st[x][0] = p, dep[x] = dep[p] + 1;
    for(int i = 0; st[x][i]; ++i)
        st[x][i+1] = st[st[x][i]][i];
    for(auto y : G[x]) if(y != p)
        dfs(y, x);
}

int lca(int u, int v) {
    if(dep[u] < dep[v]) swap(u, v);
    int d = dep[u] - dep[v];
    for(int i = maxk; i >= 0; --i)
        if(d>>i&1) u = st[u][i];
    if(u == v) return u;
    for(int i = maxk; i >= 0; --i)
        if(st[u][i] != st[v][i])
            u = st[u][i], v = st[v][i];
    return st[u][0];
}

void dfs2(int x, int p) {
    int c1 = ct1[wi[x]+dep[x]+maxn], c2 = ct2[wi[x]-dep[x]+maxn];
    for(auto v : in_val1[x]) ++ct1[v+maxn];
    for(auto v : in_val2[x]) ++ct2[v+maxn];
    for(auto y : G[x]) if(y != p)
        dfs2(y, x);
    ans[x] += ct1[wi[x]+dep[x]+maxn] - c1;
    ans[x] += ct2[wi[x]-dep[x]+maxn] - c2;
    for(auto v : out_val1[x]) --ct1[v+maxn];
    for(auto v : out_val2[x]) --ct2[v+maxn];
}

int main() {
    ios::sync_with_stdio(0);
    cin >> n >> m;
    for(int i = 1, u,v; i < n; ++i) {
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    for(int i = 1; i <= n; ++i) cin >> wi[i];
    for(int i = 1; i <= m; ++i) cin >> si[i] >> ti[i];
    dfs(1, 0);
    for(int i = 1; i <= m; ++i) {
        int x = lca(si[i], ti[i]);
        if(dep[si[i]] - dep[x] == wi[x]) --ans[x];
        in_val1[si[i]].push_back(dep[si[i]]);
        in_val2[ti[i]].push_back(dep[si[i]] - (dep[x]<<1));
        out_val1[x].push_back(dep[si[i]]);
        out_val2[x].push_back(dep[si[i]] - (dep[x]<<1));
    }
    dfs2(1, 0);
    for(int i = 1; i <= n; ++i)
        cout << ans[i] << ((i==n) ? '\n' : ' ');
    return 0;
}
