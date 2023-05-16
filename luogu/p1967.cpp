#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

const int maxn = 1e4, maxm = 5e4, maxk = 14, INF = 1e6;

int n, m;
int ui[maxm+5], vi[maxm+5], wi[maxm+5], id[maxm+5];
int dep[maxn+5], st[maxn+5][maxk+2], mi[maxn+5][maxk+2];
vector<pair<int,int>> G[maxn+5];

int fa[maxn+5], sz[maxn+5], flag[maxn+5];
int find(int x) { return fa[x]==x ? x : fa[x] = find(fa[x]); }

void dfs(int x, int p, int w) {
    flag[x] = 1, dep[x] = dep[p] + 1;
    st[x][0] = p;
    mi[x][0] = w;
    for(int i = 0; st[x][i]; ++i) {
        st[x][i+1] = st[ st[x][i] ][i];
        mi[x][i+1] = min(mi[x][i], mi[ st[x][i] ][i]);
    }
    for(auto pp : G[x]) if(pp.first != p)
        dfs(pp.first, x, pp.second);
}

int lca(int x, int y) {
    if(dep[x] < dep[y]) swap(x, y);
    int d = dep[x] - dep[y];
    int res = INF;
    for(int k = maxk; k >= 0; --k) if(d>>k&1) {
        res = min(res, mi[x][k]);
        x = st[x][k];
    }
    if(x == y) return res;
    for(int k = maxk; k >= 0; --k) if(st[x][k] != st[y][k]) {
        res = min(res, min(mi[x][k], mi[y][k]));
        x = st[x][k], y = st[y][k];
    }
    res = min(res, min(mi[x][0], mi[y][0]));
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    cin >> n >> m;
    for(int i = 1; i <= m; ++i)
        cin >> ui[i] >> vi[i] >> wi[i], id[i] = i;
    sort(id+1, id+1+m, [&](const int &a, const int &b) { return wi[a] > wi[b]; });
    for(int i = 1; i <= n; ++i) fa[i] = i, sz[i] = 1;
    for(int i = 1; i <= m; ++i) {
        int u = ui[id[i]], v = vi[id[i]], w = wi[id[i]];
        if(find(u) == find(v)) continue;
        if(sz[find(u)] > sz[find(v)]) swap(u, v);
        sz[find(v)] += sz[find(u)];
        fa[find(u)] = find(v);
        G[u].push_back(pair<int,int>(v, w));
        G[v].push_back(pair<int,int>(u, w));
    }
    for(int i = 1; i <= n; ++i) if(!flag[i])
        dfs(i, 0, INF);
    int _; cin >> _;
    while(_--) {
        int x, y;
        cin >> x >> y;
        if(find(x) != find(y)) {
            cout << "-1\n";
            continue;
        }
        cout << lca(x, y) << "\n";
    }
    return 0;
}
