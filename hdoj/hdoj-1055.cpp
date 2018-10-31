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
typedef double DB;

const int maxn = 1000;

struct Node {
    int x, s;
    DB d;
    Node() {}
    Node(int _x, int _s, DB _d) : x(_x), s(_s), d(_d) {}
    bool operator<(const Node &a) const { return d < a.d; }
};

int n, R, sz[maxn+5];
LL ci[maxn+5];
int fa[maxn+5], fp[maxn+5];
vector<int> G[maxn+5];
priority_queue<Node> q;

int find(int x) { return fp[x]==x ? x : fp[x] = find(fp[x]); }

void dfs(int x, int p) {
    fa[x] = p;
    for(auto y : G[x]) if(y!=p) dfs(y,x);
}

int main() {
    while(scanf("%d%d", &n, &R), n||R) {
        REP(i,1,n) scanf("%lld", ci+i), G[i].clear(), fp[i] = i, sz[i] = 1;
        for(int i = 1, u,v; i < n; ++i) {
            scanf("%d%d", &u, &v);
            G[u].PB(v), G[v].PB(u);
        }
        dfs(R,0);
        REP(i,1,n) if(i!=R) q.push( Node(i, 1, DB(ci[i])/1.0) );
        LL ans = 0;
        while(!q.empty()) {
            Node tmp = q.top(); q.pop();
            if(tmp.s != sz[tmp.x]) continue;
            int x = tmp.x;
            int u = find(fa[x]);
            ans += ci[x] * sz[u];
            ci[u] += ci[x], sz[u] += sz[x], sz[x] = -1;
            fp[x] = u;
            if(u != R) {
                q.push( Node( u, sz[u], DB(ci[u])/sz[u]) );
            }
        }
        ans += ci[R];
        printf("%lld\n", ans);
    }
    return 0;
}
