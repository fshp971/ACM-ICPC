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
typedef pair<LL, int> pLi;

const int maxn = 2e5;
const LL INF = (1LL << 55);

int n, m;
vector<pLi> G[maxn + 5];
LL dist[maxn + 5];
priority_queue<pLi> que;

int main() {
    int u, v;
    LL w;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; ++i) {
        scanf("%d%d%lld", &u, &v, &w);
        G[u].PB(MP(w<<1,v)), G[v].PB(MP(w<<1,u));
    }
    for(int i = 1; i <= n; ++i)
        scanf("%lld", &w), G[0].PB(MP(w,i));
    REP(i,1,n) dist[i] = INF;
    que.push(MP(0,0));
    while(!que.empty()) {
        pLi tmp = que.top(); que.pop();
        if(-tmp.fi != dist[tmp.se]) continue;
        LL d = -tmp.fi;
        int x = tmp.se;
        for(auto it : G[x]) {
            if(d + it.fi < dist[it.se]) {
                dist[it.se] = d + it.fi;
                que.push( MP(-dist[it.se], it.se) );
            }
        }
    }
    for(int i = 1; i <= n; ++i)
        printf("%lld%c", dist[i], (i == n) ? '\n' : ' ');
    return 0;
}
