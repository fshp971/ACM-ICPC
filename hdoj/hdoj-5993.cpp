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
#define lson (x<<1)
#define rson (x<<1|1)
#define mid ((l+r)>>1)
typedef long long LL;
typedef pair<int,int> pii;
 
const int maxn = 1e5;
const int Step = 16;
 
inline void Read(int &x) {
    char c = getchar();
    while(c<'0' || c>'9') c = getchar();
    for(x=0;'0'<=c&&c<='9';x=x*10+c-'0',c=getchar());
}
 
int kkk[maxn*2+2];
int n, m;
int uu[maxn+2], ww[maxn+2];
int dep[maxn+2], dis[maxn+2], st[maxn+5][Step+1];
vector<pii> G[maxn+2];
 
int DFN, dfn[maxn+2], in[maxn+2], out[maxn+2];
int DF2, df2[maxn*2+2], vi2[maxn*2+2];
void dfs(int x, int p, int id) {
    df2[++DF2] = x, vi2[x] = DF2;
    in[x] = ++DFN, dfn[DFN] = x;
    uu[id] = x;
    dep[x] = dep[p]+1, dis[x] = dis[p]+ww[id];
    mem(st[x],0);
    st[x][0] = p;
    for(int i = 0; st[x][i]; ++i) st[x][i+1] = st[st[x][i]][i];
    for(auto pp : G[x]) if(pp.fi!=p) {
        dfs(pp.fi, x, pp.se);
        df2[++DF2] = x;
    }
    out[x] = DFN;
}
 
int rm2[maxn*2+2][Step+2];
int LCA(int u, int v) {
    int l = vi2[u], r = vi2[v];
    if(l>r) swap(l,r);
    if(dep[rm2[l][kkk[r-l+1]]] < dep[rm2[r-(1<<kkk[r-l+1])+1][kkk[r-l+1]]])
        return rm2[l][kkk[r-l+1]];
    return rm2[r-(1<<kkk[r-l+1])+1][kkk[r-l+1]];
}
 
int GetDist(int u, int v) {
    return dis[u] + dis[v] - dis[LCA(u,v)]*2;
}
 
struct Node {
    int p1, p2, d;
    Node() {}
    Node(int _p1, int _p2, int _d) : p1(_p1), p2(_p2), d(_d) {}
    void Merge(Node a) {
        if(d==-1) { p1 = a.p1, p2 = a.p2, d = a.d; return; }
        int tp1 = p1, tp2 = p2;
        if(d < a.d) p1 = a.p1, p2 = a.p2, d = a.d;
        int tmp;
        tmp = GetDist(tp1, a.p1);
        if(d < tmp) p1 = tp1, p2 = a.p1, d = tmp;
 
        tmp = GetDist(tp1, a.p2);
        if(d < tmp) p1 = tp1, p2 = a.p2, d = tmp;
 
        tmp = GetDist(tp2, a.p1);
        if(d < tmp) p1 = tp2, p2 = a.p1, d = tmp;
 
        tmp = GetDist(tp2, a.p2);
        if(d < tmp) p1 = tp2, p2 = a.p2, d = tmp;
    }
};
 
Node rmq[maxn+2][Step+1];
void Build() {
    REP(i,1,n) rmq[i][0] = Node(dfn[i], dfn[i], 0);
    for(int k = 1; (1<<k) <= n; ++k) {
        for(int i = 1; i+(1<<k)-1 <= n; ++i) {
            rmq[i][k] = rmq[i][k-1];
            rmq[i][k].Merge( rmq[i+(1<<(k-1))][k-1] );
        }
    }
}
 
Node Query(int l, int r) {
    Node ret = rmq[l][kkk[r-l+1]];
    ret.Merge( rmq[r-(1<<kkk[r-l+1])+1][kkk[r-l+1]] );
    return ret;
}
 
int main() {
    for(int i = 1; i <= maxn*2; ++i) {
        kkk[i] = kkk[i-1];
        if((1<<(kkk[i]+1)) < i) ++kkk[i];
    }
    int _; scanf("%d", &_);
    while(_--) {
        scanf("%d%d", &n, &m);
        REP(i,1,n) G[i].clear();
        for(int i = 1, u,v,w; i < n; ++i) {
            scanf("%d%d%d", &u, &v, &w);
            ww[i] = w;
            G[u].PB( pii(v,i) );
            G[v].PB( pii(u,i) );
        }
        DFN = 0, DF2 = 0;
        dfs(1,0,0);
 
        REP(i,1,DF2) rm2[i][0] = df2[i];
        for(int k = 1; (1<<k) <= DF2; ++k) {
            for(int i = 1; i+(1<<k)-1 <= DF2; ++i) {
                if(dep[rm2[i][k-1]] < dep[rm2[i+(1<<(k-1))][k-1]])
                    rm2[i][k] = rm2[i][k-1];
                else rm2[i][k] = rm2[i+(1<<(k-1))][k-1];
            }
        }
        Build();
        while(m--) {
            int e1, e2; scanf("%d%d", &e1, &e2);
            int l1 = in[uu[e1]], r1 = out[uu[e1]];
            int l2 = in[uu[e2]], r2 = out[uu[e2]];
            if(l1>l2) swap(l1,l2), swap(r1,r2);
            if(r1 < l2) {
                Node ans1 = Query(l1, r1);
                Node ans2 = Query(l2, r2);
                Node ans3 = Node(-1,-1,-1);
                if(l1-1>=1) ans3.Merge( Query(1,l1-1) );
                if(r1+1<=l2-1) ans3.Merge( Query(r1+1,l2-1) );
                if(r2+1<=n) ans3.Merge( Query(r2+1,n) );
                printf("%d\n", max(ans1.d, max(ans2.d,ans3.d)) );
            }
            else {
                Node ans1 = Query(l2, r2);
                Node ans2 = Node(-1,-1,-1);
                if(l1-1>=1) ans2.Merge( Query(1,l1-1) );
                if(r1+1<=n) ans2.Merge( Query(r1+1,n) );
                Node ans3 = Node(-1,-1,-1);
                if(l1<=l2-1) ans3.Merge( Query(l1,l2-1) );
                if(r2+1<=r1) ans3.Merge( Query(r2+1,r1) );
                printf("%d\n", max(ans1.d, max(ans2.d,ans3.d)) );
            }
        }
    }
    return 0;
}
