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

const int maxn = 2e5;
const LL INF = 1LL << 55;

int col[maxn + 5];
vector<pii> G[maxn + 5];
LL f[maxn + 5][3];

void dfs(int x, int p) {
    if(col[x]) f[x][col[x]] = 0;
    else f[x][0] = f[x][1] = f[x][2] = 0;
    for(auto it : G[x]) {
        int nx = it.fi;
        if(nx == p) continue;
        dfs(nx, x);
        if(col[x])
            f[x][col[x]] += min(f[nx][0], min(f[nx][col[x]], f[nx][col[x]%2+1] + it.se));
        else {
            f[x][0] += min(f[nx][0], min(f[nx][1], f[nx][2]) + it.se);
            f[x][1] += min(f[nx][0], min(f[nx][1], f[nx][2] + it.se));
            f[x][2] += min(f[nx][0], min(f[nx][1] + it.se, f[nx][2]));
        }
    }
}

int main() {
    //freopen("in.txt", "r", stdin);
    int n, m;
    scanf("%d", &n);
    for(int i = 1, u, v, w; i < n; ++i) {
        scanf("%d%d%d", &u, &v, &w);
        G[u].PB( MP(v,w) ), G[v].PB( MP(u,w) );
    }
    scanf("%d", &m);
    for(int i = 1, u; i <= m; ++i)
        scanf("%d", &u), col[u] = 1;
    scanf("%d", &m);
    for(int i = 1, u; i <= m; ++i)
        scanf("%d", &u), col[u] = 2;
    REP(i,1,n) FOR(k,0,3) f[i][k] = INF;
    dfs(1, 0);
    printf("%lld\n", min(f[1][0], min(f[1][1], f[1][2])));
    return 0;
}
