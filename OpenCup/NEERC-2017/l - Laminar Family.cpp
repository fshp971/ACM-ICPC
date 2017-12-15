#include<bits/stdc++.h>

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

const int maxn = 1e5, MaxStep = 17;

int n, m;
int st[maxn + 5][MaxStep + 2], dep[maxn + 5];
int mk[maxn + 5];
vector<int> G[maxn + 5], G2[maxn + 5], nd[maxn + 5];
pii seg[maxn + 5];

void dfs1(int x, int pre) {
    st[x][0] = pre, dep[x] = dep[pre] + 1;
    for(int i = 0; st[x][i]; ++i)
        st[x][i+1] = st[st[x][i]][i];
    for(auto it : G[x])
        if(it != pre)
            dfs1(it, x);
}

int LCA(int u, int v) {
    if(dep[u] < dep[v]) swap(u, v);
    for(int i = 0, del = dep[u] - dep[v]; i <= MaxStep; ++i)
        if(del >> i & 1)
            u = st[u][i];
    if(u == v) return u;
    for(int i = MaxStep; i >= 0; --i)
        if(st[u][i] != st[v][i])
            u = st[u][i], v = st[v][i];
    return st[u][0];
}

int dfs2(int x, int pre) {
    int s = mk[x];
    for(auto it : G[x]) {
        if(it != pre)
            s += dfs2(it, x);
    }
    if(s != 0)
        G2[pre].PB(x), G2[x].PB(pre);
    return s;
}

vector<pii> seg2;
stack<int> sta;
bool ok[maxn + 5];
int id[maxn + 5];

void dfs3(int x, int pre, int dd) {
    id[x] = dd;
    for(auto it : nd[x])
        if(!ok[it])
            seg2.PB(seg[it]), ok[it] = 1;
    for(auto it : G[x]) {
        if(it != pre)
            dfs3(it, x, dd + 1);
    }
}

bool cmp(const pii &a, const pii &b) {
    if(a.fi != b.fi) return a.fi < b.fi;
    return a.se > b.se;
}

bool Run(int x) {
    seg2.clear();
    dfs3(x, 0, 1);
    for(int i = 0; i < seg2.size(); ++i) {
        seg2[i].fi = id[seg2[i].fi];
        seg2[i].se = id[seg2[i].se];
        if(seg2[i].fi > seg2[i].se)
            swap(seg2[i].fi, seg2[i].se);
    }
    sort(seg2.begin(), seg2.end(), cmp);
    while(!sta.empty()) sta.pop();
    for(auto it : seg2) {
        while(!sta.empty()) {
            if(sta.top() >= it.se) break;
            if(sta.top() >= it.fi) return false;
            sta.pop();
        }
        sta.push(it.se);
    }
    return true;
}

bool Work() {
    int u, v;
    scanf("%d%d", &n, &m);
    for(int i = 1; i < n; ++i) {
        scanf("%d%d", &u, &v);
        G[u].PB(v), G[v].PB(u);
    }
    dfs1(1, 0);
    for(int i = 1; i <= m; ++i) {
        scanf("%d%d", &u, &v);
        seg[i] = MP(u,v);
        if(u == v) continue;
        int lca = LCA(u,v);
        ++mk[u], ++mk[v], mk[lca] -= 2;
        nd[u].PB(i), nd[v].PB(i);
    }
    dfs2(1, 0);
    for(int i = 1; i <= n; ++i)
        if(G2[i].size() > 2) return false;
    for(int i = 1; i <= n; ++i)
        if(G2[i].size() == 1 && !id[i]) {
            if(!Run(i)) return false;
        }
    return true;
}

int main() {
    printf(Work() ? "Yes\n" : "No\n");
    return 0;
}
