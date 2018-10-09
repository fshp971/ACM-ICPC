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

const int Step = 17;
const int maxn = 1e5;
const LL INF = 1LL << 60;

int n, m, ai[maxn+5], fa[maxn+5];
int uu[maxn*2+5], vv[maxn*2+5], num[maxn*2+5];
int st[maxn+5][Step+2], dep[maxn+5];
LL wt[maxn+5][Step+2];
LL ww[maxn*2+5];
LL dis[maxn+5];
vector<pair<int,LL>> G[maxn+5];

priority_queue<pair<LL,int>> q;
void Dij() {
    REP(i,1,n) {
        if(ai[i]) dis[i] = 0, q.push( MP(0LL,i) );
        else dis[i] = INF;
    }
    while(!q.empty()) {
        LL d = -q.top().fi;
        int x = q.top().se;
        q.pop();
        if(dis[x] != d) continue;
        for(auto pp : G[x]) {
            if(dis[x]+pp.se < dis[pp.fi]) {
                dis[pp.fi] = dis[x] + pp.se;
                q.push( MP(-dis[pp.fi], pp.fi) );
            }
        }
    }
}

void dfs(int x, int p, int d, LL w) {
    dep[x] = d, st[x][0] = p, wt[x][0] = w;
    for(int i = 0; st[x][i]; ++i) {
        st[x][i+1] = st[st[x][i]][i];
        wt[x][i+1] = max(wt[x][i], wt[st[x][i]][i]);
    }
    for(auto pp : G[x]) if(pp.fi != p) {
        dfs(pp.fi, x, d+1, pp.se);
    }
}

LL Calc(int u, int v) {
    if(u == v) return 0;
    if(dep[u]<dep[v]) swap(u,v);
    LL ret = 0;
    int del = dep[u]-dep[v];
    for(int i = Step; i >= 0; --i)
        if(del>>i&1) {
            ret = max(ret, wt[u][i]);
            u = st[u][i];
        }
    if(u==v) return ret;
    for(int i = Step; i >= 0; --i)
        if(st[u][i] != st[v][i]) {
            ret = max(ret, max(wt[u][i], wt[v][i]));
            u = st[u][i], v = st[v][i];
        }
    return max(ret, max(wt[u][0], wt[v][0]));
}

bool cmp(const int &a, const int &b) { return ww[a] < ww[b]; }
int find(int x) { return fa[x]==x ? x : fa[x]=find(fa[x]); }

int main() {
    scanf("%d%d", &n, &m);
    REP(i,1,n) scanf("%d", ai+i);
    for(int i = 1; i <= m; ++i) {
        scanf("%d%d%lld", uu+i, vv+i, ww+i);
        G[uu[i]].PB( MP(vv[i],ww[i]) );
        G[vv[i]].PB( MP(uu[i],ww[i]) );
    }
    Dij();
    REP(i,1,n) G[i].clear(), fa[i] = i;
    REP(i,1,m) ww[i] += dis[uu[i]] + dis[vv[i]], num[i] = i;
    sort(num+1, num+1+m, cmp);
    REP(i,1,m) {
        if(find(uu[num[i]]) == find(vv[num[i]])) continue;
        fa[find(uu[num[i]])] = find(vv[num[i]]);
        G[uu[num[i]]].PB( MP(vv[num[i]],ww[num[i]]) );
        G[vv[num[i]]].PB( MP(uu[num[i]],ww[num[i]]) );
    }
    dfs(1,0,0,0);
    int _; scanf("%d", &_);
    while(_--) {
        int u,v; scanf("%d%d", &u, &v);
        printf("%lld\n", Calc(u,v));
    }
    return 0;
}
