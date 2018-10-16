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

const int maxn = 2e5;

int n, m, p, xi[maxn+5];
vector<pii> G[maxn+5];
int from[maxn+5];
LL dist[maxn+5];
LL ans[maxn+5];

priority_queue<pair<LL,pii>> q;
void Dij() {
    REP(i,1,n) dist[i] = 1LL << 60;
    REP(i,1,p) {
        dist[xi[i]] = 0, from[xi[i]] = xi[i];
        q.push( pair<LL,pii>( 0LL, pii(xi[i],xi[i]) ) );
    }
    while(!q.empty()) {
        LL d = -q.top().fi;
        int x = q.top().se.fi, px = q.top().se.se;
        q.pop();
        if(dist[x] != d) continue;
        for(auto pp : G[x]) {
            if(d+pp.se < dist[pp.fi]) {
                dist[pp.fi] = d+pp.se, from[pp.fi] = px;
                q.push( pair<LL,pii>( -dist[pp.fi], pii(pp.fi,px) ) );
            }
        }
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &p);
    REP(i,1,p) scanf("%d", xi+i);
    for(int i = 1, u,v,w; i <= m; ++i) {
        scanf("%d%d%d", &u, &v, &w);
        G[u].PB( pii(v,w) );
        G[v].PB( pii(u,w) );
    }
    Dij();
    REP(i,1,n) ans[i] = 1LL << 60;
    REP(x,1,n) {
        for(auto pp : G[x]) {
            int &y = pp.fi;
            if(from[x] != from[y]) {
                ans[from[x]] = min(ans[from[x]], dist[x]+dist[y]+pp.se);
                ans[from[y]] = min(ans[from[y]], dist[x]+dist[y]+pp.se);
            }
        }
    }
    REP(i,1,p) printf("%lld%c", ans[xi[i]], (i==p)?'\n':' ');
    return 0;
}
