// ICPC 2017 Nanning M
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

const int maxn = 100;

bool vis[maxn+5], g[maxn+5][maxn+5];
int R[maxn+5];
int n, m;

int dfs(int u) {
    for(int i = 1; i <= n; ++i) if(g[u][i]&&!vis[i]) {
        vis[i] = 1;
        if(R[i]==0 || dfs(R[i])) {
            R[i] = u;
            return 1;
        }
    }
    return 0;
}

int Run() {
    int res = 0;
    REP(i,1,n) R[i] = 0;
    for(int i = 1; i <= n; ++i) {
        REP(k,1,n) vis[k] = 0;
        res += dfs(i);
    }
    return res;
}

int main() {
    int _; scanf("%d", &_);
    while(_--) {
        scanf("%d%d", &n, &m);
        REP(i,1,n) REP(k,1,n) g[i][k] = 0;
        for(int i = 1, u,v; i <= m; ++i)
            scanf("%d%d", &u, &v), g[u][v] = 1;
        REP(k,1,n) REP(i,1,n) REP(j,1,n) g[i][j] |= g[i][k]&g[k][j];
        int ans = n - Run();
        printf("%d\n", ans);
    }
    return 0;
}
