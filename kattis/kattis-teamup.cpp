#include<bits/stdc++.h>

using namespace std;

#pragma comment(linker, "/STACK:102400000,102400000")

#define LL long long
#define MP(a,b) make_pair(a,b)
#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define pii pair<int,int>
#define sf scanf
#define pf printf

const int maxn = 1000000;
const int maxm = 3000000;

int n, m, pp;

vector<pii> skill[maxn+5];

int sz[maxm+5];
int h[maxm+5], e[maxm*2+5], nex[maxm*2+5];
char vis[maxm+5], cnt[maxm+5];
int fa[maxm+5];

vector<int> sta[maxm+5];

int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

void dfs(int x)
{
    vis[x] = 1;
    int t, lim, all = 0;
    bool fg = 0;
    for(int i=h[x]; i; i=nex[i])
    {
        if(vis[e[i]]) continue;
        all += sz[e[i]];
        dfs(e[i]);
        if(sta[e[i]].size() == 0) return;
        if(!fg) { t = e[i], fg = true; continue; }
        lim = min(sta[t].size(), sta[e[i]].size());
        while(sta[t].size() > lim) sta[t].pop_back();
        while(sta[e[i]].size() > lim) sta[e[i]].pop_back();
        for(int k=0; k<lim; ++k)
            fa[ sta[e[i]][k] ] = sta[t][k];
        sta[e[i]].clear();
    }
    if(all < sz[x]) return;
    if(!fg) return;
    for(int i=0; i<sta[t].size(); ++i)
        sta[x].push_back(sta[t][i]);
    sta[t].clear();
    return;
}

int rot[maxm+5];
vector<int> res[maxm+5];

int main()
{
    //freopen("in.txt","r",stdin);
    //freopen("out.txt","w",stdout);
    sf("%d%d%d", &n, &m, &pp);
    int a, top = 0;
    REP(i,1,m)
    {
        sf("%d", sz+i);
        REP(k,1,sz[i])
        {
            sf("%d", &a);
            skill[a].push_back( MP(sz[i], i) );
        }
    }
    for(int i=1; i<=n; ++i)
    {
        sort(skill[i].begin(), skill[i].end());
        int len = skill[i].size();
        for(int k=len-1; k>=1; --k)
        {
            if(skill[i][k].first == skill[i][k-1].first) continue;
            int &u = skill[i][k].second;
            int &v = skill[i][k-1].second;
            e[++top] = v, nex[top] = h[u], h[u] = top;
            cnt[v] = 1;
        }
    }
    REP(i,1,pp)
    {
        sf("%d", &a);
        sta[a].push_back(i);
        fa[i] = i;
    }
    top = 0;
    for(int i=1; i<=m; ++i) if(!cnt[i])
        dfs(i), rot[++top] = i;
    int cont = 0;
    for(int i=1; i<=top; ++i)
        cont += sz[rot[i]];
    if(cont != n)
    {
        pf("0\n");
        return 0;
    }
    for(int i=2; i<=top; ++i)
    {
        int lim = min(sta[rot[1]].size(), sta[rot[i]].size());
        if(lim == 0)
        {
            pf("0\n");
            return 0;
        }
        while(sta[rot[1]].size() > lim) sta[rot[1]].pop_back();
        while(sta[rot[i]].size() > lim) sta[rot[i]].pop_back();
        for(int k=0; k<lim; ++k)
            fa[ sta[rot[i]][k] ] = sta[rot[1]][k];
    }
    cout << sta[rot[1]].size() << "\n";
    for(int i=1; i<=pp; ++i)
        res[find(i)].push_back(i);
    for(int i=0; i<sta[rot[1]].size(); ++i)
    {
        int u = find(sta[rot[1]][i]);
        int len = res[u].size();
        pf("%d", len);
        for(int k=0; k<len; ++k)
            pf(" %d", res[u][k]);
        pf("\n");
    }
    return 0;
}
