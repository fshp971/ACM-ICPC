#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define PER(i,a,b) for(int i = a; i >= b; --i)
#define PB push_back
#define MP make_pair
#define fi first
#define se second
typedef long long LL;
typedef long double LD;

const int maxn = 1e5, maxk = 16;
const LL INF = 1e12;

int n, m, pi[maxn+5];
vector<int> G[maxn+5];
int st[maxn+5][maxk+5], dep[maxn+5];
LL f[2][maxn+5];
LL h[2][2][maxn+5][maxk+5];

void dfs1(int x, int p) {
    f[0][x] = 0, f[1][x] = pi[x];

    st[x][0] = p, dep[x] = dep[p] + 1;
    for(int i = 0; st[x][i]; ++i)
        st[x][i+1] = st[st[x][i]][i];

    for(auto &y : G[x]) if(y != p) {
        dfs1(y, x);
        f[0][x] += f[1][y];
        f[1][x] += min(f[0][y], f[1][y]);
    }
}

void dfs2(int x, int p) {
    if(p == 0) {
        h[0][0][x][0] = h[0][1][x][0] = INF;
        h[1][0][x][0] = h[1][1][x][0] = INF;
    }
    else {
        h[0][0][x][0] = INF;
        h[1][0][x][0] = f[0][p] - f[1][x];
        h[0][1][x][0] = h[1][1][x][0] = f[1][p] - min(f[0][x], f[1][x]);
    }
    for(int i = 1; st[x][i]; ++i) {
        int &y = st[x][i-1];
        REP(c1,0,1) REP(c2,0,1) {
            h[c1][c2][x][i] = INF;
            REP(c3,0,1)
                h[c1][c2][x][i] = min(h[c1][c2][x][i], h[c1][c3][x][i-1] + h[c3][c2][y][i-1]);
        }
    }
    for(auto &y : G[x]) if(y != p) dfs2(y, x);
}

int lca(int x, int y) {
    if(dep[x] < dep[y]) swap(x, y);
    int d = dep[x] - dep[y];
    REP(i,0,maxk) if(d>>i&1) x = st[x][i];
    if(x == y) return x;
    PER(i,maxk,0) if(st[x][i] != st[y][i])
        x = st[x][i], y = st[y][i];
    return st[x][0];
}

void dp(int x, int c, int d, LL *res) {
    res[c] = 0, res[c^1] = INF;
    if(d == 0) return;
    LL tmp[2];
    REP(i,0,maxk) if(d>>i&1) {
        REP(c1,0,1) {
            tmp[c1] = INF;
            REP(c2,0,1)
                tmp[c1] = min(tmp[c1], res[c2] + h[c2][c1][x][i]);
        }
        REP(k,0,1) res[k] = tmp[k];
        x = st[x][i];
    }
}

int main() {
    ios::sync_with_stdio(0);
    char _s[10];
    cin >> n >> m >> _s;
    REP(i,1,n) cin >> pi[i];
    for(int i = 1, u,v; i < n; ++i) {
        cin >> u >> v;
        G[u].PB(v), G[v].PB(u);
    }
    dfs1(1, 0);
    dfs2(1, 0);
    while(m--) {
        int x, a, y, b;
        cin >> x >> a >> y >> b;
        int z = lca(x, y);

        LL rsx[2], rsy[2], rsz[2];
        dp(x, a, dep[x]-dep[z], rsx);
        dp(y, b, dep[y]-dep[z], rsy);

        LL ans = INF;
        REP(c,0,1) {
            if(rsx[c]>=INF || rsy[c]>=INF) continue;
            LL tmp = rsx[c] + rsy[c];

            if(x == z) tmp += f[b][y];
            else if(y == z) tmp += f[a][x];
            else tmp += f[a][x] + f[b][y] - f[c][z];

            dp(z, c, dep[z]-1, rsz);
            tmp += min(rsz[0], rsz[1]);
            ans = min(ans, tmp);
        }
        if(ans >= INF) cout << "-1\n";
        else cout << ans << '\n';
    }
    return 0;
}
