#include<cassert>
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

const int maxn = 1e5, maxm = 2e5;

int n, m;
int uu[maxm + 5], vv[maxm + 5], ok[maxm + 5], dist[maxm + 5];
int vist[maxn + 5], the[maxn + 5];
pii mx[maxn + 5][2];
vector<int> G[maxn + 5];

bool dfs(int e) {
    int x = vv[e];
    if(vist[x]&1) {
        if(G[x].size() > 1 || (e^1) != G[x][0]) return false;
        dist[e] = 1;
        return true;
    }
    if((vist[x]>>1&1) && (vist[x]>>2&1)) {
        if((e^1) != mx[x][0].se) dist[e] = mx[x][0].fi + 1;
        else dist[e] = mx[x][1].fi + 1;
        return true;
    }
    if(vist[x]>>1&1) {
        if((e^1) == the[x]) {
            dist[e] = mx[x][0].fi + 1;
            return true;
        }
        vist[x] |= 1;
        if(!dfs(the[x])) return false;
        pii tmp = MP(dist[the[x]], the[x]);
        if(mx[x][0].fi < tmp.fi) swap(mx[x][0], tmp);
        if(mx[x][1].fi < tmp.fi) swap(mx[x][1], tmp);
        if((e^1) != mx[x][0].se) dist[e] = mx[x][0].fi + 1;
        else dist[e] = mx[x][1].fi + 1;
        vist[x] ^= 1, vist[x] |= (1<<2);
        return true;
    }
    vist[x] |= 1, vist[x] |= (1<<2), the[x] = -1, dist[e] = 0;
    mx[x][0] = mx[x][1] = MP(0,-1);
    for(auto it : G[x]) {
        if((e^1) == it) {
            vist[x] ^= (1<<2), the[x] = it;
            continue;
        }
        if(!dfs(it)) return false;
        pii tmp = MP(dist[it], it);
        if(mx[x][0].fi < tmp.fi) swap(mx[x][0], tmp);
        if(mx[x][1].fi < tmp.fi) swap(mx[x][1], tmp);
    }
    vist[x] ^= 1, vist[x] |= (1<<1);
    if((e^1) != mx[x][0].se) dist[e] = mx[x][0].fi + 1;
    else dist[e] = mx[x][1].fi + 1;
    return true;
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 0, u, v, t; i < m; ++i) {
        scanf("%d%d%d", &u, &v, &t);
        uu[i<<1] = u, vv[i<<1] = v, ok[i<<1] = 1, G[u].PB(i<<1);
        if(t == 2)
            uu[i<<1|1] = v, vv[i<<1|1] = u, ok[i<<1|1] = 1, G[v].PB(i<<1|1);
    }
    int ans = 0;
    for(int i = 0; i < (m<<1); ++i) {
        if(!ok[i]) continue;
        if(!dfs(i)) exit(0*puts("Infinite"));
        ans = max(ans, dist[i]);
    }
    printf("%d\n", ans);
    return 0;
}
