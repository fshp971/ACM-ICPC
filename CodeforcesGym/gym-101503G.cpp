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

#define lson (x << 1)
#define rson (x << 1 | 1)
#define mid ((l + r) >> 1)

const int maxn = 4000, MaxStep = 13, INF = 1e9;

int n, st[maxn + 5][MaxStep + 5], dist[maxn + 5], dep[maxn + 5];
vector<pii> G[maxn + 5], Gtree[maxn + 5];

void dfs1(int x, int p) {
    st[x][0] = p, dep[x] = dep[p] + 1;
    for(int i = 0; st[x][i]; ++i)
        st[x][i+1] = st[st[x][i]][i];
    for(auto it : Gtree[x])
        if(it.fi != p) {
            dist[it.fi] = dist[x] + it.se;
            dfs1(it.fi, x);
        }
}

int LCA(int u, int v) {
    if(dep[u] < dep[v]) swap(u, v);
    int del = dep[u] - dep[v];
    for(int i = 0; i <= MaxStep; ++i)
        if(del >> i & 1)
            u = st[u][i];
    if(u == v) return u;
    for(int i = MaxStep; i >= 0; --i)
        if(st[u][i] != st[v][i])
            u = st[u][i], v = st[v][i];
    return st[u][0];
}

const int maxnode = maxn << 2;
int tree[maxnode + 5], lazy[maxnode + 5];

void PushDown(int x) {
    lazy[lson] = min(lazy[lson], lazy[x]);
    lazy[rson] = min(lazy[rson], lazy[x]);
    tree[lson] = min(tree[lson], lazy[x]);
    tree[rson] = min(tree[rson], lazy[x]);
    lazy[x] = INF;
}

void Update(int x, int l, int r, int ll, int rr, int val) {
    if(ll <= l && r <= rr)
        lazy[x] = min(lazy[x], val), tree[x] = min(tree[x], val);
    else {
        PushDown(x);
        if(ll <= mid) Update(lson, l, mid, ll, rr, val);
        if(mid < rr) Update(rson, mid + 1, r, ll, rr, val);
        tree[x] = min(tree[lson], tree[rson]);
    }
}

void ResetPos(int x, int l, int r, int pos) {
    if(l == r) lazy[x] = tree[x] = INF;
    else {
        PushDown(x);
        if(pos <= mid) ResetPos(lson, l, mid, pos);
        else ResetPos(rson, mid + 1, r, pos);
        tree[x] = min(tree[lson], tree[rson]);
    }
}

int Query(int x, int l, int r, int ll, int rr) {
    if(ll <= l && r <= rr) return tree[x];
    PushDown(x);
    int res = INF;
    if(ll <= mid) res = min(res, Query(lson, l, mid, ll, rr));
    if(mid < rr) res = min(res, Query(rson, mid + 1, r, ll, rr));
    return res;
}

int ans[maxn + 5];
void dfs2(int x, int p) {
    ResetPos(1, 1, n, dep[x]);
    for(auto it : G[x]) {
        int lca = LCA(x, it.fi);
        if(dep[lca] + 1 <= dep[x])
            Update(1, 1, n, dep[lca] + 1, dep[x], dist[x] + dist[it.fi] + it.se);
    }
    for(auto it : Gtree[x])
        if(it.fi != p)
            dfs2(it.fi, x);
    int res = Query(1, 1, n, dep[x], dep[x]);
    ans[x] = (res == INF) ? -1 : (res - dist[x]);
}

int main() {
    int m, u, v, l, t;
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; ++i) {
        scanf("%d%d%d%d", &u, &v, &l, &t);
        if(t) Gtree[u].PB(MP(v,l)), Gtree[v].PB(MP(u,l));
        else G[u].PB(MP(v,l)), G[v].PB(MP(u,l));
    }
    dfs1(1, 0);
    dfs2(1, 0);
    for(int i = 2; i <= n; ++i) {
        if(i != 2) printf(" ");
        printf("%d", ans[i]);
    }
    printf("\n");
    return 0;
}
