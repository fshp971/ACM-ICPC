#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<cassert>
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

const int maxn = 1e5, MaxS = 4;

int n, NT, vist[maxn + 5], dist[maxn + 5];
vector<int> G[maxn + 5];

int fa[maxn + 5];
int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

queue<pii> que;
int bfs(int ss, int tt) {
    vist[ss] = NT, dist[ss] = 0, que.push(MP(ss,0));
    while(!que.empty()) {
        pii x = que.front(); que.pop();
        if(x.se == MaxS) continue;
        for(auto it : G[x.fi])
            if(vist[it] != NT)
                vist[it] = NT, dist[it] = x.se + 1, que.push(MP(it,dist[it]));
    }
    if(vist[tt] == NT) return dist[tt];
    int res = n+10;
    vist[tt] = NT, dist[tt] = -1, que.push(MP(tt,0));
    while(!que.empty()) {
        pii x = que.front(); que.pop();
        if(x.se == MaxS) continue;
        for(auto it : G[x.fi]) {
            if(vist[it] != NT)
                vist[it] = NT, dist[it] = -1, que.push(MP(it,x.se+1));
            else if(dist[it] != -1)
                res = min(res, dist[it] + x.se + 1);
        }
    }
    return res == n+10 ? -1 : res;
}

int bf(int ss, int tt) {
    REP(i,1,n) vist[i] = 0;
    vist[ss] = NT, dist[ss] = 0, que.push(MP(ss,0));
    while(!que.empty()) {
        pii x = que.front(); que.pop();
        for(auto it : G[x.fi])
            if(vist[it] != NT)
                vist[it] = NT, dist[it] = x.se + 1, que.push(MP(it,dist[it]));
    }
    return dist[tt];
}

int main() {
    freopen("travelling.in", "r", stdin);
    freopen("travelling.out", "w", stdout);
    int T, u, v;
    scanf("%d%d", &n, &T);
    REP(i,1,n) fa[i] = i;
    for(int i = 1; i <= T; ++i) {
        scanf("%d%d", &u, &v);
        G[u].PB(v), G[v].PB(u);
        fa[find(u)] = find(v);
    }
    scanf("%d", &T);
    for(NT = 1; NT <= T; ++NT) {
        scanf("%d%d", &u, &v);
        if(find(u) != find(v)) { puts("-1"); continue; }
        int d = bfs(u, v);
        if(d == -1) d = bf(u, v);
        printf("%d\n", d);
    }
    return 0;
}
