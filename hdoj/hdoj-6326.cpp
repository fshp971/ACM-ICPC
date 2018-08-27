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

const int maxn = 1e5;

struct Node {
    LL a, b;
    Node() {}
    Node(LL _a, LL _b): a(_a), b(_b) {}
    bool operator<(const Node &nd) const {
        if(a<=b && nd.a<=nd.b) return !(a < nd.a);
        if(a>b && nd.a>nd.b) return !(b > nd.b);
        return !(a <= b);
    }
    void Append(const Node &nd) {
        LL ta, tb;
        if(b >= nd.a) ta = a, tb = b - nd.a + nd.b;
        else ta = a + nd.a - b, tb = nd.b;
        a = ta, b = tb;
    }
} ans[maxn + 5];

int n, vist[maxn + 5], T;
int fa[maxn + 5], pp[maxn + 5];
vector<int> G[maxn + 5];

int find(int x) { return pp[x] == x ? x : pp[x] = find(pp[x]); }

void dfs(int x) {
    for(auto it : G[x]) {
        if(it != fa[x])
            fa[it] = x, dfs(it);
    }
}

priority_queue<pair<Node,pii>> que;
int main() {
    int _; scanf("%d", &_);
    while(_--) {
        scanf("%d", &n);
        REP(i,1,n) G[i].clear(), pp[i] = i, vist[i] = 0;
        ans[1] = Node(0,0);
        for(int i = 2, a, b; i <= n; ++i) {
            scanf("%d%d", &a, &b);
            ans[i] = Node(a,b);
            que.push( MP(ans[i], MP(0,i)) );
        }
        for(int i = 1, u, v; i < n; ++i) {
            scanf("%d%d", &u, &v);
            G[u].PB(v), G[v].PB(u);
        }
        dfs(1);
        T = 0;
        while(!que.empty()) {
            auto tmp = que.top(); que.pop();
            if(tmp.se.fi != vist[tmp.se.se]) continue;
            if(tmp.se.se == 1) continue;
            int x = tmp.se.se, y = find(fa[x]);
            pp[x] = y;
            ans[y].Append( tmp.fi );
            vist[y] = ++T;
            que.push( MP(ans[y], MP(T, y)) );
        }
        printf("%lld\n", ans[1].a);
    }
    return 0;
}
