#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

const int maxn = 3e5, maxk = 18;

int n, m;
vector<int> uj(maxn+5), vj(maxn+5), pj(maxn+5);
vector<vector<pair<int,int>>> G(maxn+5, vector<pair<int,int>>(0));

vector<vector<int>> st(maxn+5, vector<int>(maxk+5));
vector<int> dep(maxn+5), dis(maxn+5);
vector<int> add(maxn+5);
int T = 0;

void dfs(int x, int p, int w) {
    dep[x] = dep[p] + 1, st[x][0] = p, dis[x] = dis[p] + w;
    for(int i = 0; st[x][i]; ++i)
        st[x][i+1] = st[ st[x][i] ][i];
    for(auto pp : G[x]) if(pp.first != p)
        dfs(pp.first, x, pp.second);
}

int lca(int u, int v) {
    if(dep[u] < dep[v]) swap(u, v);
    int d = dep[u] - dep[v];
    for(int i = maxk; i >= 0; --i)
        if(d>>i&1) u = st[u][i];
    if(u == v) return u;
    for(int i = maxk; i >= 0; --i) {
        if(st[u][i] == st[v][i]) continue;
        u = st[u][i], v = st[v][i];
    }
    return st[u][0];
}

bool dfs2(int x, int p, int w, int &cnt, int &least) {
    for(auto pp : G[x]) if(pp.first != p) {
        if(dfs2(pp.first, x, pp.second, cnt, least))
            return true;
        add[x] += add[pp.first];
    }
    return (add[x] == cnt && w >= least);
}

bool check(int lim) {
    int cnt = 0, least = 0;
    for(int i = 1; i <= n; ++i) add[i] = 0;
    for(int i = 1; i <= m; ++i) {
        int &u = uj[i], &v = vj[i], &p = pj[i];
        int d = dis[u] + dis[v] - (dis[p]<<1);
        if(d <= lim) continue;
        ++cnt;
        least = max(least, d-lim);
        ++add[u], ++add[v], add[p] -= 2;
    }
    return dfs2(1, 0, 0, cnt, least);
}

int main() {
    ios::sync_with_stdio(0);
    cin >> n >> m;
    for(int i = 1, a,b,t; i < n; ++i) {
        cin >> a >> b >> t;
        G[a].push_back( pair<int,int>(b, t) );
        G[b].push_back( pair<int,int>(a, t) );
    }
    for(int i = 1; i <= m; ++i)
        cin >> uj[i] >> vj[i];

    dfs(1, 0, 0);
    for(int i = 1; i <= m; ++i)
        pj[i] = lca(uj[i], vj[i]);

    int l = 0, r = 1e9, ans = 1e9+10;
    while(l <= r) {
        int mid = (l+r) >> 1;
        if(check(mid)) ans = mid, r = mid-1;
        else l = mid+1;
    }
    cout << ans << "\n";
    return 0;
}
