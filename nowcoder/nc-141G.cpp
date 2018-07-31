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

const int maxn = 5000;
const int md = 1e9 + 7;

int n, kk, D, s1, s2;
vector<int> G[maxn + 5];
queue<int> que;
bool vist[maxn + 5];

void dfs(int x, int p, int d) {
    if(d < D) s1 += vist[x];
    if(d < D+1) s2 += vist[x];
    for(auto it : G[x])
        if(it != p) dfs(it,x,d+1);
}

LL Solve() {
    mem(vist, 0);
    que.push(1);
    LL ret1 = 1, ret2 = 1;
    while(!que.empty()) {
        int x = que.front(); que.pop();
        s1 = s2 = 0, dfs(x,0,0);
        ret1 = ret1 * max(kk-s1,0) % md;
        ret2 = ret2 * max(kk-s2,0) % md;
        vist[x] = 1;
        for(auto it : G[x])
            if(!vist[it]) que.push(it);
    }
    return (ret1 - ret2 + md) % md;
}

int main() {
    scanf("%d%d%d", &n, &kk, &D);
    for(int i = 1, u, v; i < n; ++i) {
        scanf("%d%d", &u, &v);
        G[u].PB(v), G[v].PB(u);
    }
    printf("%lld\n", Solve());
    return 0;
}
