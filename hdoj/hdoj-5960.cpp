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

const int maxn = 4e5 * 2 + 10;
const int maxnode = 2e6;

struct Node {
    int l, r, to;
    LL val;
    Node() {}
    Node(int _l, int _r, LL _val, int _to) : l(_l), r(_r), val(_val), to(_to) {}
} heap[maxnode + 5];
int tot = 0;

int Merge(int x, int y) {
    if(!x || !y) return x|y;
    if(heap[x].val < heap[y].val) swap(x,y);
    int t = ++tot;
    heap[t] = heap[x];
    (rand()&1) ? (heap[t].l = Merge(heap[t].l,y)) : (heap[t].r = Merge(heap[t].r,y));
    return t;
}

int n, kk, ss, tt, rt[maxn+5];
LL dist[maxn+5];
int c0[maxn+5], c1[maxn+5], col[maxn+5];
vector<pii> G[maxn+5];
priority_queue<pair<LL,int>> q;

LL Kth() {
    dist[tt] = 0;
    PER(i,n,1) {
        dist[i] = dist[i+n] = -1;
        for(auto pp : G[i])
            dist[i] = max(dist[i], dist[pp.fi]+pp.se);
        for(auto pp : G[i+n])
            dist[i+n] = max(dist[i+n], dist[pp.fi]+pp.se);
    }
    dist[0] = -1;
    for(auto pp : G[0])
        dist[0] = max(dist[0], dist[pp.fi]+pp.se);
    tot = 0;
    rt[tt] = 0;
    PER(i,n,1) {
        rt[i] = rt[i+n] = 0;
        bool fg = 0;
        for(auto pp : G[i]) {
            if(dist[pp.fi]+pp.se == dist[i] && !fg) {
                fg = 1, rt[i] = Merge(rt[i], rt[pp.fi]);
                continue;
            }
            heap[++tot] = Node(0, 0, dist[pp.fi]+pp.se - dist[i], pp.fi);
            rt[i] = Merge(rt[i], tot);
        }
        fg = 0;
        for(auto pp : G[i+n]) {
            if(dist[pp.fi]+pp.se == dist[i+n] && !fg) {
                fg = 1, rt[i+n] = Merge(rt[i+n], rt[pp.fi]);
                continue;
            }
            heap[++tot] = Node(0, 0, dist[pp.fi]+pp.se - dist[i+n], pp.fi);
            rt[i+n] = Merge(rt[i+n], tot);
        }
    }
    rt[0] = 0;
    bool fg = 0;
    for(auto pp : G[0]) {
        if(dist[pp.fi]+pp.se == dist[0] && !fg) {
            fg = 1, rt[0] = Merge(rt[0], rt[pp.fi]);
            continue;
        }
        heap[++tot] = Node(0, 0, dist[pp.fi]+pp.se - dist[0], pp.fi);
        rt[0] = Merge(rt[0], tot);
    }
    if(kk==1) return dist[0];
    --kk;
    while(!q.empty()) q.pop();
    q.push( MP(dist[0]+heap[rt[0]].val, rt[0]) );
    while((kk--) >= 2) {
        LL d = q.top().fi;
        int x = q.top().se;
        q.pop();
        if(rt[heap[x].to])
            q.push( MP(d+heap[rt[heap[x].to]].val, rt[heap[x].to]) );
        d -= heap[x].val;
        x = Merge(heap[x].l, heap[x].r);
        if(x)
            q.push( MP(d+heap[x].val, x) );
    }
    return q.top().fi;
}

inline void AddEdge(int u, int v, int d) {
    G[u].PB( MP(v,d) );
}

int main() {
    srand(time(NULL));
    int _; scanf("%d", &_);
    while(_--) {
        scanf("%d%d", &n, &kk);
        REP(i,1,n) scanf("%d%d%d", c0+i, c1+i, col+i);
        REP(i,0,n*2+1) G[i].clear();
        ss = 0, tt = n*2+1;
        REP(i,1,n-1) {
            AddEdge(i, i+1+col[i+1]*n, c0[i+1]);
            AddEdge(n+i, i+1+col[i+1]*n, c1[i+1]);
            AddEdge(i, i+1, 0);
            AddEdge(i+n, i+1+n, 0);
        }
        AddEdge(0, 1+col[1]*n, c0[1]);
        AddEdge(0, 1, 0);
        AddEdge(n, n*2+1, 0);
        AddEdge(n*2, n*2+1, 0);
        printf("%lld\n", Kth());
    }
    return 0;
}
