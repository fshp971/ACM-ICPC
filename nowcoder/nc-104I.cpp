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

const int maxn = 2e5, maxnode = maxn << 2;

int tot = 0, uu[maxn + 5], vv[maxn + 5];
int L[maxn + 5], R[maxn + 5];
map<pii,int> Id;
int GetId(pii x) {
    if(Id.find(x) == Id.end())
        uu[tot] = x.fi, vv[tot] = x.se, Id[x] = tot++;
    return Id[x];
}

vector<int> vec[maxnode + 5];
void Upd(int x, int l, int r, int ll, int rr, int v) {
    if(ll <= l && r <= rr) vec[x].PB(v);
    else {
        if(ll <= mid) Upd(lson, l, mid, ll, rr, v);
        if(mid < rr) Upd(rson, mid+1, r, ll, rr, v);
    }
}

int n, m, que[maxn + 5][3], ans[maxn + 5];
int fa[maxn + 5], sz[maxn + 5];

int find(int x) { return fa[x] == x ? x : find(fa[x]); }

struct Node {
    int u, sz, id;
    Node() {}
    Node(int _u, int _sz, int _id) { u = _u, sz = _sz, id = _id; }
};

stack<Node> sta;
void Process(int x) {
    for(auto it : vec[x]) {
        int u = find(uu[it]), v = find(vv[it]);
        if(u == v) continue;
        sta.push( Node(u, sz[u], x) );
        sta.push( Node(v, sz[v], x) );
        if(sz[u] < sz[v]) swap(u,v);
        sz[u] += sz[v], fa[v] = u;
    }
}

void RollBack(int x) {
    while(!sta.empty()) {
        Node tmp = sta.top();
        if(tmp.id != x) break;
        sta.pop();
        fa[tmp.u] = tmp.u, sz[tmp.u] = tmp.sz;
    }
}

void Solve(int x, int l, int r) {
    Process(x);
    if(l == r) {
        if(que[l][0] == 3)
            ans[l] = sz[ find(que[l][1]) ];
        else if(que[l][0] == 4)
            ans[l] = find(que[l][1]) == find(que[l][2]);
    }
    else {
        Solve(lson, l, mid);
        Solve(rson, mid+1, r);
    }
    RollBack(x);
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; ++i) {
        int o, x, y;
        scanf("%d%d", &o, &x);
        if(o == 1) {
            scanf("%d", &y);
            if(x > y) swap(x, y);
            int id = GetId( MP(x,y) );
            L[id] = i, R[id] = m;
        }
        else if(o == 2) {
            scanf("%d", &y);
            if(x > y) swap(x, y);
            int id = GetId( MP(x,y) );
            R[id] = i-1, Id.erase( MP(x,y) );
        }
        else if(o == 3) {
            que[i][0] = o, que[i][1] = x;
        }
        else {
            scanf("%d", &y);
            que[i][0] = o, que[i][1] = x, que[i][2] = y;
        }
    }
    for(int i = 0; i < tot; ++i)
        Upd(1, 1, m, L[i], R[i], i);
    REP(i,1,n) fa[i] = i, sz[i] = 1;
    Solve(1,1,m);
    for(int i = 1; i <= m; ++i) {
        if(que[i][0] == 3) printf("%d\n", ans[i]);
        else if(que[i][0] == 4)
            printf("%s\n", ans[i] ? "Yes,cap" : "No");
    }
    return 0;
}
