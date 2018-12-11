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

const int maxn = 2500;

int n;
int G[maxn+5][maxn+5];
vector<int> be[maxn+5];
int xi[maxn+5], si[maxn+5];
bool vi[maxn+5];
LL dist[maxn+5];
LL ans = 0;

int scc, top, Index;
int sta[maxn+5], DFN[maxn+5], Low[maxn+5], Belong[maxn+5];
bool Insta[maxn+5], deg[maxn+5];
vector<int> G2[maxn+5];

void Tarjan(int u) {
    DFN[u] = Low[u] = ++Index;
    sta[++top] = u, Insta[u] = 1;
    for(auto v : G2[u]) {
        if(!DFN[v]) {
            Tarjan(v);
            Low[u] = min(Low[u], Low[v]);
        }
        else if(Insta[v]) Low[u] = min(Low[u], Low[v]);
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

int main() {
    scanf("%d", &n);
    REP(i,1,n) {
        scanf("%d%d", xi+i, si+i);
        ans += si[i];
        if(xi[i]!=i) G2[xi[i]].PB(i), deg[i] = 1;
        REP(j,0,n) scanf("%d", &G[j][i]), G[j][i]-=si[i];
    }

    scc = top = Index = 0;
    REP(i,0,n) if(!DFN[i]) Tarjan(i);

    REP(i,0,n) be[Belong[i]].PB(i);
    REP(i,1,scc) {
        if(be[i].size()==0) continue;
        if(be[i].size()==1 && deg[be[i][0]]) continue;
        int mi = 2e9;
        for(auto x : be[i]) mi = min(mi, G[n][x]);
        ans += mi;
        for(auto x : be[i]) {
            REP(i,0,n) G[i][x] -= mi;
        }
    }
    mem(dist, 0x7f);
    dist[0] = 0;
    for(int i = 0; i <= n; ++i) {
        int x = -1;
        for(int k = 0; k <= n; ++k) if(!vi[k]) {
            if(x==-1 || dist[x]>dist[k]) x = k;
        }
        vi[x] = 1;
        for(int k = 0; k <= n; ++k) dist[k] = min(dist[k], dist[x]+G[x][k]);
        for(auto y : G2[x]) dist[y] = min(dist[y], dist[x]);
    }
    ans += dist[n];
    printf("%lld\n", ans);
    return 0;
}
