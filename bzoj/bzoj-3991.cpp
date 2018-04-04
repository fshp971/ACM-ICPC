#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<cassert>
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
const int MaxStep = 17;

int n, m, top = 0, DFN[maxn + 5], dep[maxn + 5];
vector<pii> G[maxn + 5];
int st[maxn + 5][MaxStep + 2];
LL di[maxn + 5][MaxStep + 2], Now = 0;
bool flag[maxn + 5];
map<int,int> Map;

void dfs(int x, int p, int d) {
    dep[x] = dep[p] + 1, DFN[x] = ++top, st[x][0] = p, di[x][0] = d;
    for(int i = 0; st[x][i]; ++i)
        st[x][i+1] = st[st[x][i]][i], di[x][i+1] = di[x][i] + di[st[x][i]][i];
    for(int i = 0; i < G[x].size(); ++i) if(G[x][i].fi != p) dfs(G[x][i].fi, x, G[x][i].se);
}

LL Dist(int u, int v) {
    if(dep[u] < dep[v]) swap(u,v);
    int d = dep[u] - dep[v];
    LL res = 0;
    for(int i = MaxStep - 1; i >= 0; --i)
        if(d>>i&1) res += di[u][i], u = st[u][i];
    if(u == v) return res;
    for(int i = MaxStep - 1; i >= 0; --i)
        if(st[u][i] != st[v][i])
            res += di[u][i] + di[v][i], u = st[u][i], v = st[v][i];
    return res + di[u][0] + di[v][0];
}

LL Modify(int x) {
    if(flag[x]) {
        flag[x] = 0;
        map<int,int>::iterator it = Map.find(DFN[x]), pit = it, nit = it;
        ++nit;
        if(pit != Map.begin())
            --pit, Now -= Dist(pit->se, x), ++pit;
        if(nit != Map.end())
            Now -= Dist(nit->se, x);
        if(pit != Map.begin() && nit != Map.end())
            --pit, Now += Dist(pit->se, nit->se);
        Map.erase(it);
    }
    else {
        flag[x] = 1;
        Map.insert( MP(DFN[x], x) );
        map<int,int>::iterator it = Map.find(DFN[x]), pit = it, nit = it;
        ++nit;
        if(pit != Map.begin())
            --pit, Now += Dist(pit->se, x), ++pit;
        if(nit != Map.end())
            Now += Dist(nit->se, x);
        if(pit != Map.begin() && nit != Map.end())
            --pit, Now -= Dist(pit->se, nit->se);
    }
    if(!Map.size()) return 0;
    map<int,int>::iterator hh = Map.begin(), tt = Map.end(); --tt;
    return Now + Dist(hh->se, tt->se);
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1, u, v, w; i < n; ++i) {
        scanf("%d%d%d", &u, &v, &w);
        G[u].PB(MP(v,w)), G[v].PB(MP(u,w));
    }
    dfs(1,0,0);
    while(m--) {
        int u; scanf("%d", &u);
        printf("%lld\n", Modify(u));
    }
    return 0;
}
