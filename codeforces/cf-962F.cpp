#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define PB push_back
#define SZ(a) (int)(a.size())
#define fi first
#define se second
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 1e5;

int n, m, tot = 0;
int dep[maxn + 5], tod[maxn + 5], be[maxn + 5];
bool inter[maxn + 5];
set<int> rm[maxn + 5];
vector<pii> G[maxn + 5];
vector<int> ans;

int Merge(int a, int b) {
    if(a == 0) return b;
    if(b == 0) return a;
    inter[a] = inter[b] = 1;
    return tod[a] < tod[b] ? a : b;
}

int dfs(int x, int d, int id) {
    dep[x] = d;
    int val = 0;
    for(auto it : G[x]) {
        if(dep[it.fi] >= dep[x] - 1) continue;
        if(!dep[it.fi]) {
            int tmp = dfs(it.fi, d+1, it.se);
            if(rm[x].find(tmp) == rm[x].end())
                val = Merge(val, tmp);
        }
        else {
            tod[++tot] = dep[it.fi];
            be[it.se] = tot;
            rm[it.fi].insert(tot);
            val = Merge(val, tot);
        }
    }
    return be[id] = val;
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1, u, v; i <= m; ++i) {
        scanf("%d%d", &u, &v);
        G[u].PB(MP(v,i)), G[v].PB(MP(u,i));
    }
    for(int i = 1; i <= n; ++i)
        if(!dep[i]) dfs(i,2,0);
    for(int i = 1; i <= m; ++i)
        if(be[i] && !inter[be[i]]) ans.PB(i);
    sort(ans.begin(), ans.end());
    printf("%d\n", SZ(ans));
    for(int i = 0; i < SZ(ans); ++i)
        printf("%d%c", ans[i], (i == SZ(ans)-1) ? '\n' : ' ');
    return 0;
}
