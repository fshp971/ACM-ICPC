#include<bits/stdc++.h>

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

const int maxn = 3e5;
const double INF = 1e100;

int n, m, deg[maxn + 5], cnt[maxn + 5];
vector<int> G[maxn + 5];
double dist[maxn + 5], sum[maxn + 5];
bool vist[maxn + 5];
priority_queue<pair<double,int>> que;

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1, u, v; i <= m; ++i) {
        scanf("%d%d", &u, &v);
        ++deg[u], ++deg[v];
        G[u].PB(v), G[v].PB(u);
    }
    for(int i = 1; i < n; ++i) dist[i] = INF;
    dist[n] = 0;
    que.push( MP(double(0),n) );
    while(!que.empty()) {
        pair<double,int> x = que.top(); que.pop();
        if(vist[x.se]) continue;
        vist[x.se] = 1;
        for(auto it : G[x.se]) {
            if(vist[it]) continue;
            sum[it] += dist[x.se], ++cnt[it];
            dist[it] = (sum[it] + deg[it]) / cnt[it];
            que.push( MP(-dist[it],it) );
        }
    }
    printf("%.10f\n", dist[1]);
    return 0;
}
