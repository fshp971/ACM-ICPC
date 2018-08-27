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
typedef unsigned long long ULL;
typedef pair<int,int> pii;

const int maxn = 3e5;

int n, m;
int uu[maxn+5], vv[maxn+5], ww[maxn+5], ban[maxn+5];
int h[maxn+5], e[maxn*2+5], ii[maxn*2+5], nx[maxn*2+5], tot;
void AddEdge(int u, int v, int w, int i) {
    e[++tot] = v, ii[tot] = i, nx[tot] = h[u], h[u] = tot;
    e[++tot] = u, ii[tot] = i, nx[tot] = h[v], h[v] = tot;
}

struct Node {
    int u, v, w;
    Node() {}
    Node(int _u, int _v, int _w) : u(_u), v(_v), w(_w) {}
    bool operator<(const Node &a) const { return w < a.w; }
} seg[maxn+5];

int vist[maxn+5];
int su[maxn+5], si[maxn+5], all = 0;
void dfs(int u, int p) {
    if(vist[u] == 2) return;
    if(vist[u] == 1) {
        int mi = 0;
        for(int i = all;; --i) {
            if(mi==0) mi = si[i];
            else if(ww[si[i]] < ww[mi]) mi = si[i];
            if(su[i] == u) break;
        }
        ban[mi] = 1;
        for(int i = all;; --i) {
            if(mi != si[i]) ww[si[i]] += ww[mi];
            if(su[i] == u) break;
        }
        return;
    }
    su[++all] = u, vist[u] = 1;
    for(int i = h[u]; i; i = nx[i]) {
        if(e[i] == p) continue;
        si[all] = ii[i];
        dfs(e[i],u);
    }
    vist[u] = 2, --all;
}

const int Step = 30;
int fa[maxn+5], sz[maxn+5], bit[maxn+5][Step+2];
int find(int x) { return fa[x]==x ? x : fa[x] = find(fa[x]); }

int main() {
    int _; scanf("%d", &_);
    while(_--) {
        scanf("%d%d", &n, &m);
        REP(i,1,n) h[i] = 0, vist[i] = 0;
        tot = 0;
        for(int i=1, u,v,w; i <= m; ++i) {
            scanf("%d%d%d", &u, &v, &w);
            uu[i] = u, vv[i] = v, ww[i] = w, ban[i] = 0;
            AddEdge(u,v,w,i);
        }
        REP(i,1,n) if(!vist[i]) dfs(i,0);
        REP(i,1,n) h[i] = 0;
        tot = 0;
        int tm = 0;
        REP(i,1,m) if(!ban[i]) {
            seg[++tm] = Node(uu[i], vv[i], ww[i]);
        }
        sort(seg+1, seg+1+tm);
        REP(i,1,n) {
            fa[i] = i, sz[i] = 1, mem(bit[i],0);
            REP(k,0,Step)
                if(i>>k&1) ++bit[i][k];
        }
        ULL ans = 0;
        PER(i,tm,1) {
            int u = find(seg[i].u), v = find(seg[i].v), w = seg[i].w;
            REP(k,0,Step) {
                ULL tmp = 0;
                if(w>>k&1)
                    tmp = ULL(sz[u]-bit[u][k]) * ULL(sz[v]-bit[v][k]) + ULL(bit[u][k]) * ULL(bit[v][k]);
                else tmp = ULL(sz[u]-bit[u][k]) * ULL(bit[v][k]) + ULL(bit[u][k]) * ULL(sz[v]-bit[v][k]);
                ans += tmp * ULL(1<<k);
                bit[u][k] += bit[v][k];
            }
            sz[u] += sz[v], fa[v] = u;
        }
        printf("%llu\n", ans);
    }
    return 0;
}
