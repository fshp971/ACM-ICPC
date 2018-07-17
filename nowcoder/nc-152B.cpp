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
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 2e5;

int n, m, uu[maxn + 5], vv[maxn + 5], vist[maxn + 5];
vector<int> G[maxn + 5];

inline int Get(int u, int d) {
    u = (u-1-d+n+n) % n;
    if(u == 0) u = n;
    return u;
}

bool dfs(int x) {
    if(vist[x] == 1) return true;
    if(vist[x] == 2) return false;
    vist[x] = 1;
    for(auto it : G[x])
        if(dfs(it)) return true;
    vist[x] = 2;
    return false;
}

bool Chk(int x) {
    for(int i = 1; i <= n; ++i) G[i].clear(), vist[i] = 0;
    G[ Get(vv[1],0) ].PB( Get(uu[1],0) );
    x = min(x+1, m);
    for(int i = 2; i <= x; ++i)
        G[ Get(vv[i],1) ].PB( Get(uu[i],1) );
    for(int i = 1; i <= n; ++i)
        if(dfs(i)) return true;
    return false;
}

int main() {
    scanf("%d%d", &n, &m);
    REP(i,1,m) scanf("%d%d", uu+i, vv+i);
    int l = 1, r = m, ans = m;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(Chk(mid)) ans = mid, r = mid - 1;
        else l = mid + 1;
    }
    for(int i = 1; i <= ans; ++i) puts("1");
    for(int i = ans+1; i <= m; ++i) puts("0");
    return 0;
}
