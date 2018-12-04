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

const int maxn = 1e5;

int n, m, vis[maxn+5], pa[maxn+5];
vector<int> G[maxn+5];
vector<tuple<int,int,int>> ans;

void dfs(int x) {
    vis[x] = 1;
    for(auto y : G[x]) {
        if(!vis[y]) dfs(y);
        if(vis[y]!=1) {
            if(pa[y]) {
                ans.PB( tuple<int,int,int>(x,y,pa[y]) );
                pa[pa[y]] = 0, pa[y] = 0;
            }
            else if(pa[x]) {
                ans.PB( tuple<int,int,int>(y,x,pa[x]) );
                pa[pa[x]] = 0, pa[x] = 0;
            }
            else {
                pa[x] = y, pa[y] = x;
            }
        }
    }
    vis[x] = 2;
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1, u,v; i <= m; ++i) {
        scanf("%d%d", &u, &v);
        G[u].PB(v), G[v].PB(u);
    }
    REP(i,1,n) if(!vis[i]) dfs(i);
    printf("%d\n", int(ans.size()) );
    for(auto x : ans) printf("%d %d %d\n", get<0>(x), get<1>(x), get<2>(x));
    return 0;
}
