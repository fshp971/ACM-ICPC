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

const int maxn = 5000;
const short INF = 1<<14;

int n;
vector<int> G[maxn+5];
int f[maxn+5][maxn+5], g[maxn+5][maxn+5];

void dfs(int x, int p) {
    REP(i,0,n) f[x][i] = INF;
    bool fg = 0;
    for(auto y : G[x]) {
        if(y == p) continue;
        fg = 1;
        dfs(y,x);
        REP(i,0,n) {
            if(i+1<=n) {
                f[x][i] = min(f[x][i]+g[y][i], f[y][i+1]+g[x][i+1]);
            }
            g[x][i] += g[y][i-1];
        }
    }
    if(fg) {
        g[x][0] = f[x][0];
        f[x][n] = n;
        REP(i,1,n-1) f[x][i] = min(f[x][i], g[x][i+1] + i);
    }
    else {
        f[x][0] = g[x][0] = 1;
        REP(i,1,n) f[x][i] = i;
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 1, u,v; i < n; ++i) {
        scanf("%d%d", &u, &v);
        G[u].PB(v), G[v].PB(u);
    }
    dfs(1,0);
    int ans = 1<<30;
    REP(i,0,n) ans = min(ans, (int)f[1][i]);
    printf("%d\n", ans);
    return 0;
}
