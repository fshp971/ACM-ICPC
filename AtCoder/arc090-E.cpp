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

const int maxn = 1e5, maxm = 2e5;
const int md = 1e9 + 7;

struct Edge {
    int u, v, dd;
    Edge() {}
    Edge(int _u, int _v, int _dd) { u = _u, v = _v, dd = _dd; }
} edge[maxm + 5];

int n, m, S, T;
vector<pii> G[maxn + 5];
LL dist1[maxn + 5], dist2[maxn + 5], cnt1[maxn + 5], cnt2[maxn + 5];

void Run(int ss, LL* dist, LL *cnt) {
    for(int i = 1; i <= n; ++i) dist[i] = 1LL << 60, cnt[i] = 0;
    priority_queue<pair<LL,int>> que;
    dist[ss] = 0, cnt[ss] = 1, que.push(MP(0LL,ss));
    while(!que.empty()) {
        pair<LL,int> x = que.top(); que.pop();
        if(-x.fi != dist[x.se]) continue;
        for(auto it : G[x.se]) {
            if(-x.fi + it.se < dist[it.fi]) {
                dist[it.fi] = -x.fi + it.se, cnt[it.fi] = cnt[x.se];
                que.push(MP(-dist[it.fi],it.fi));
            }
            else if(-x.fi + it.se == dist[it.fi])
                cnt[it.fi] = (cnt[it.fi] + cnt[x.se]) % md;
        }
    }
}

int main() {
    scanf("%d%d%d%d", &n, &m, &S, &T);
    for(int i = 1, u, v, d; i <= m; ++i) {
        scanf("%d%d%d", &u, &v, &d);
        edge[i] = Edge(u,v,d);
        G[u].PB( MP(v,d) );
        G[v].PB( MP(u,d) );
    }
    Run(S, dist1, cnt1);
    Run(T, dist2, cnt2);
    LL ans = (cnt1[T] - 1 + md) % md * cnt1[T] % md;
    for(int i = 1; i <= n; ++i)
        if(dist1[i] == dist2[i] && (dist1[i] << 1) == dist1[T]) {
            LL tmp = cnt1[i] * cnt2[i] % md;
            ans = (ans - (tmp-1+md) % md * tmp % md + md) % md;
        }
    for(int i = 1; i <= m; ++i) {
        int u = edge[i].u, v = edge[i].v, d = edge[i].dd;
        if(abs(dist1[u]-dist2[v]) < d && dist1[u] + d + dist2[v] == dist1[T]) {
            LL tmp = cnt1[u] * cnt2[v] % md;
            ans = (ans - (tmp-1+md) % md * tmp % md + md) % md;
        }
        u = edge[i].v, v = edge[i].u;
        if(abs(dist1[u]-dist2[v]) < d && dist1[u] + d + dist2[v] == dist1[T]) {
            LL tmp = cnt1[u] * cnt2[v] % md;
            ans = (ans - (tmp-1+md) % md * tmp % md + md) % md;
        }
    }
    printf("%lld\n", ans);
    return 0;
}
