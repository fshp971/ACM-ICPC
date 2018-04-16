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

const int maxn = 1e5;
const LL INF = 1LL << 50;

int n, m;
int uu[maxn + 5], vv[maxn + 5], ww[maxn + 5];
vector<pii> G1[maxn + 5], G2[maxn + 5];
LL dist1[maxn + 5], dist2[maxn + 5], cnt1[maxn + 5], cnt2[maxn + 5];

priority_queue<pair<LL,int>> que;
queue<int> que2;
int du[maxn + 5];
void Dij(int ss, vector<pii> *G, LL *dist, LL *cnt) {
    REP(i,1,n) dist[i] = INF, cnt[i] = 0, du[i] = 0;
    dist[ss] = 0, que.push(MP(0,ss));
    while(!que.empty()) {
        pair<LL,int> x = que.top(); que.pop();
        if(-x.fi != dist[x.se]) continue;
        for(auto it : G[x.se])
            if(dist[x.se] + it.se < dist[it.fi]) {
                dist[it.fi] = dist[x.se] + it.se;
                que.push(MP(-dist[it.fi],it.fi));
            }
    }
    for(int i = 1; i <= n; ++i) {
        for(auto it : G[i]) {
            if(dist[i] + it.se == dist[it.fi])
                ++du[it.fi];
        }
    }
    que2.push(ss); cnt[ss] = 1;
    while(!que2.empty()) {
        int x = que2.front(); que2.pop();
        for(auto it : G[x]) {
            if(dist[x] + it.se == dist[it.fi]) {
                --du[it.fi], cnt[it.fi] += cnt[x];
                if(!du[it.fi]) que2.push(it.fi);
            }
        }
    }
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; ++i) {
        scanf("%d%d%d", uu + i, vv + i, ww + i);
        G1[ uu[i] ].PB( MP(vv[i], ww[i]) );
        G2[ vv[i] ].PB( MP(uu[i], ww[i]) );
    }
    Dij(1, G1, dist1, cnt1);
    Dij(2, G2, dist2, cnt2);
    for(int i = 1; i <= m; ++i) {
        if(dist1[uu[i]] + dist2[vv[i]] + ww[i] == dist1[2]) {
            if(cnt1[uu[i]] * cnt2[vv[i]] == cnt1[2]) puts("SAD");
            else puts("SOSO");
        }
        else {
            if(dist1[vv[i]] + dist2[uu[i]] + ww[i] < dist1[2]) puts("HAPPY");
            else puts("SOSO");
        }
    }
    return 0;
}
