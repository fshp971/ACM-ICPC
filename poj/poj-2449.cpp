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

const int INF = 1<<30;
const int maxn = 1000;
const int maxm = 100000;
const int maxnode = 500000 * 10;

struct Node {
    int l, r, val, to;
} heap[maxnode + 5];
int tot = 0;

int Merge(int x, int y) {
    if(!x || !y) return x|y;
    if(heap[x].val > heap[y].val) swap(x,y);
    int t = ++tot;
    heap[t] = heap[x];
    (rand()&1) ? (heap[t].l = Merge(heap[t].l,y)) : (heap[t].r = Merge(heap[t].r,y));
    return t;
}

int n, m, ss, ee, kk, deg[maxn+5];
int dist[maxn+5], rot[maxn+5];
priority_queue< pair<LL,int> > q1;
queue<int> q2;

int top = 0;
int h[maxm+5], e[maxm+5], w[maxm+5], nx[maxm+5];
int ih[maxm+5], ie[maxm+5], iw[maxm+5], inx[maxm+5];
bool flag[maxm+5];
inline void AddEdge(int u, int v, int d) {
    ++top;
    e[top] = v, w[top] = d, nx[top] = h[u], h[u] = top;
    ie[top] = u, iw[top] = d, inx[top] = ih[v], ih[v] = top;
}

void Dij() {
    REP(i,1,n) dist[i] = INF;
    dist[ee] = 0, q1.push( MP(0LL,ee) );
    while(!q1.empty()) {
        pair<LL,int> tmp = q1.top(); q1.pop();
        if(-tmp.fi != dist[tmp.se]) continue;
        int x = tmp.se;
        for(int ii = ih[x]; ii; ii = inx[ii]) {
            if(iw[ii]+dist[x] < dist[ie[ii]]) {
                dist[ie[ii]] = iw[ii] + dist[x];
                q1.push( MP( -LL(dist[ie[ii]]), ie[ii] ) );
            }
        }
    }
}

int main() {
    srand(18395372);
    scanf("%d%d", &n, &m);
    for(int i = 1, u,v,d; i <= m; ++i) {
        scanf("%d%d%d", &u, &v, &d);
        AddEdge(u,v,d);
    }
    scanf("%d%d%d", &ss, &ee, &kk);
    Dij();
    REP(x,1,n) {
        if(x==ee || dist[x] == INF) continue;
        for(int ii = h[x]; ii; ii = nx[ii])
            if(dist[e[ii]]!=INF && dist[x] == dist[e[ii]]+w[ii]) {
                flag[ii] = 1; break;
            }
    }
    tot = 0, q2.push(ee);
    while(!q2.empty()) {
        int x = q2.front();
        q2.pop(), rot[x] = 0;
        if(dist[x] == INF) continue;
        for(int ii = ih[x]; ii; ii = inx[ii])
            if(flag[ii]) q2.push(ie[ii]);
        for(int ii = h[x]; ii; ii = nx[ii]) {
            if(flag[ii]) {
                rot[x] = Merge(rot[x], rot[e[ii]]);
                continue;
            }
            if(dist[e[ii]] == INF) continue;
            ++tot, heap[tot].l = heap[tot].r = 0, heap[tot].to = e[ii];
            heap[tot].val = dist[e[ii]] + w[ii] - dist[x];
            rot[x] = Merge(rot[x], tot);
        }
    }
    if(dist[ss] == INF) exit( puts("-1")*0 );
    if(ss == ee) ++kk;
    --kk;
    if(!kk) exit( printf("%d\n", dist[ss]) * 0 );
    while(!q1.empty()) q1.pop();
    if(rot[ss])
        q1.push( MP( -LL(dist[ss]+heap[rot[ss]].val), rot[ss] ) );
    while(!q1.empty() && (kk--)) {
        pair<LL,int> tmp = q1.top(); q1.pop();
        if(!kk) exit( printf("%lld\n", -tmp.fi) * 0 );
        LL d = -tmp.fi; int x = tmp.se;
        if(rot[heap[x].to])
            q1.push( MP( -(d+heap[rot[heap[x].to]].val), rot[heap[x].to] ) );
        d -= heap[x].val;
        x = Merge(heap[x].l, heap[x].r);
        if(x)
            q1.push( MP( -(d+heap[x].val), x ) );
    }
    puts("-1");
    return 0;
}
