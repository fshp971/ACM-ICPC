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

const int maxn = 50000;
const int Step = 15;
const int sq = 1280;

typedef bitset<sq> BIT;

BIT bt[maxn+5][42], pfx[sq+5], sfx[sq+5];
int bq[maxn+5], bc[maxn+5], rev[maxn+5];
int cnt[maxn+5][42];

int scc, top, Index;
int sta[maxn+5], DFN[maxn+5], Low[maxn+5], Belong[maxn+5];
bool Insta[maxn+5];

int deg[maxn+5];
vector<int> G[maxn+5], G2[maxn+5];
set<pii> Edge;
queue<int> que;

int n, m, Q;
int ans, mov;

void Tarjan(int u) {
    DFN[u] = Low[u] = ++Index;
    sta[++top] = u, Insta[u] = 1;
    for(auto v : G[u]) {
        if(!DFN[v]) {
            Tarjan(v);
            Low[u] = min(Low[u], Low[v]);
        }
        else if(Insta[v])
            Low[u] = min(Low[u], Low[v]);
    }
    int t;
    if(DFN[u] == Low[u]) {
        ++scc;
        do {
            t = sta[top--];
            Insta[t] = 0;
            Belong[t] = scc;
        } while(t!=u);
    }
}

LL Work() {
    LL res = 0;
    REP(i,1,n) {
        int l = ((ans^i)>>mov)<<mov, r = min(l+(1<<mov)-1, n);
        if(l>r) continue;
        if(bq[l] == bq[r]) {
            BIT tmp = sfx[sq-bc[l]] & pfx[bc[r]+1];
            res += (bt[Belong[i]][bq[l]]&tmp).count();
            continue;
        }
        res += (bt[Belong[i]][bq[l]]&sfx[sq-bc[l]]).count();
        for(int k = bq[l]+1; k < bq[r]; ++k)
            res += cnt[Belong[i]][k];
        res += (bt[Belong[i]][bq[r]]&pfx[bc[r]+1]).count();
    }
    return res;
}

int main() {
    REP(i,0,maxn) bq[i] = i/sq, bc[i] = i%sq;
    pfx[sq].set(); sfx[sq].set();
    for(int i = sq-1; i >= 0; --i) pfx[i] = pfx[i+1]>>1, sfx[i] = sfx[i+1]<<1;

    int _; scanf("%d", &_);
    while(_--) {
        scanf("%d%d%d", &n, &m, &Q);
        REP(i,1,n) G[i].clear();
        for(int i = 1, u,v; i <= m; ++i) {
            scanf("%d%d", &u, &v);
            G[u].PB(v);
        }

        scc = top = Index = 0;
        REP(i,1,n) DFN[i] = Insta[i] = 0;
        REP(i,1,n) if(!DFN[i]) Tarjan(i);

        REP(i,1,scc) {
            G2[i].clear();
            deg[i] = 0;
            REP(k,0,bq[n]) bt[i][k].reset();
        }
        Edge.clear();
        REP(x,1,n) {
            bt[Belong[x]][bq[x]][bc[x]] = 1;
            for(auto y : G[x]) {
                if(Belong[x] == Belong[y]) continue;
                if(Edge.find(pii(Belong[x],Belong[y])) != Edge.end()) continue;
                G2[ Belong[y] ].PB( Belong[x] );
                ++deg[ Belong[x] ];
            }
        }
        REP(i,1,scc) if(!deg[i]) que.push(i);
        while(!que.empty()) {
            int x = que.front(); que.pop();
            for(auto y : G2[x]) {
                REP(k,0,bq[n]) bt[y][k] |= bt[x][k];
                --deg[y];
                if(!deg[y]) que.push(y);
            }
        }
        REP(i,1,scc) {
            REP(k,0,bq[n]) cnt[i][k] = bt[i][k].count();
        }
        int lim = 0;
        while((1<<lim) <= n) ++lim;
        while(Q--) {
            int kk; scanf("%d", &kk);
            ans = 0;
            for(int i = lim-1; i >= 0; --i) {
                ans |= (1<<i);
                mov = i;
                LL tmp = Work();
                if(tmp<kk) ans ^= (1<<i), kk-=tmp;
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}
