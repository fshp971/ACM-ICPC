#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
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

const int maxn = 2e4, MaxStep = 15;

int n, st[maxn + 5][MaxStep + 2], dep[maxn + 5], id[maxn + 5][61];
LL val[maxn + 5], f[maxn + 5][61];
vector<int> G[maxn + 5];

void dfs(int x, int par, int d) {
    st[x][0] = par, dep[x] = d;
    for(int i = 0; st[x][i]; ++i)
        st[x][i+1] = st[st[x][i]][i];
    memcpy(f[x], f[par], sizeof(f[par]));
    memcpy(id[x], id[par], sizeof(id[par]));
    for(int i = 60, k = d; i >= 0; --i) {
        if(!(val[x] >> i & 1)) continue;
        if(!f[x][i]) { f[x][i] = val[x], id[x][i] = k; break; }
        if(k > id[x][i]) swap(f[x][i], val[x]), swap(id[x][i], k);
        val[x] ^= f[x][i];
    }
    for(int i = 0; i < G[x].size(); ++i)
        if(G[x][i] != par)
            dfs(G[x][i], x, d + 1);
}

int LCA(int u, int v) {
    if(dep[u] < dep[v]) swap(u, v);
    int del = dep[u] - dep[v];
    for(int i = MaxStep; i >= 0; --i)
        if(del >> i & 1) u = st[u][i];
    if(u == v) return u;
    for(int i = MaxStep; i >= 0; --i)
        if(st[u][i] != st[v][i])
            u = st[u][i], v = st[v][i];
    return st[u][0];
}

int main() {
    int q, u, v;
    scanf("%d%d", &n, &q);
    for(int i = 1; i <= n; ++i) scanf("%lld", val + i);
    for(int i = 1; i < n; ++i) {
        scanf("%d%d", &u, &v);
        G[u].PB(v), G[v].PB(u);
    }
    dfs(1, 0, 1);
    LL A[61];
    for(int i = 1; i <= q; ++i) {
        scanf("%d%d", &u, &v);
        int dd = dep[LCA(u,v)];
        mem(A, 0);
        for(int k = 60; k >= 0; --k)
            if(id[u][k] >= dd) A[k] = f[u][k];
        for(int k = 60; k >= 0; --k) {
            if(id[v][k] < dd) continue;
            LL vv = f[v][k];
            for(int j = k; j >= 0; --j) {
                if(!(vv >> j & 1)) continue;
                if(!A[j]) { A[j] = vv; break; }
                vv ^= A[j];
            }
        }
        LL ans = 0;
        for(int k = 60; k >= 0; --k) {
            if(ans >> k & 1) continue;
            ans ^= A[k];
        }
        printf("%lld\n", ans);
    }
    return 0;
}
