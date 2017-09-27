#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 1e5;
const int md = 1e9 + 7;

int n, m, kk, xx;
vector<int> G[maxn + 5];
bool par[maxn + 5];
LL f[maxn + 5][2][3][12];

inline void Add(LL &a, LL b) { a = (a + b) % md; }

void dfs(int x, int pre) {
    bool &msk = par[x];
    f[x][msk][0][0] = kk - 1;
    f[x][msk][1][0] = 1;
    f[x][msk][2][0] = m - kk;
    for(auto it : G[x]) {
        if(it == pre) continue;
        dfs(it, x);
        bool &mk2 = par[it];
        mem(f[x][msk^1], 0);
        for(int i = 0; i <= xx; ++i) {
            for(int k = 0; k <= xx; ++k) {
                if(i + k > xx) break;
                Add(f[x][msk^1][0][i+k], (f[it][mk2][0][k] + f[it][mk2][2][k]) % md * f[x][msk][0][i]);
                Add(f[x][msk^1][1][i+k], f[it][mk2][0][k] * f[x][msk][1][i]);
                Add(f[x][msk^1][2][i+k], (f[it][mk2][0][k] + f[it][mk2][2][k]) % md * f[x][msk][2][i]);
                if(i + k + 1 <= xx)
                    Add(f[x][msk^1][0][i+k+1], f[x][msk][0][i] * f[it][mk2][1][k]);
            }
        }
        msk ^= 1;
    }
}

int main() {
    int u, v;
    scanf("%d%d", &n, &m);
    for(int i = 1; i < n; ++i) {
        scanf("%d%d", &u, &v);
        G[u].push_back(v);
        G[v].push_back(u);
    }
    scanf("%d%d", &kk, &xx);
    dfs(1, 0);
    LL ans = 0;
    for(int i = 0; i <= xx; ++i) {
        Add(ans, f[1][par[1]][0][i] + f[1][par[1]][2][i]);
        if(i + 1 <= xx)
            Add(ans, f[1][par[1]][1][i]);
    }
    printf("%lld\n", ans);
    return 0;
}
