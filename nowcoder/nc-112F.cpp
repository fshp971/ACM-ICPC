#include <bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
#define mid ((l + r) >> 1)
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 1e5;
const int maxnode = maxn * 20;

int n, m, kk;
int tot = 0, tr[maxnode + 5], L[maxnode + 5], R[maxnode + 5];
int rot[maxn + 5];
int cnt[maxn + 5], val[maxn + 5];
vector<int> G[maxn + 5];

int Build(int l, int r) {
    int rt = ++tot;
    tr[rt] = 0;
    if(l < r) {
        L[rt] = Build(l, mid);
        R[rt] = Build(mid+1, r);
    }
    return rt;
}

int Upd(int prt, int l, int r, int p, int v) {
    int rt = ++tot;
    L[rt] = L[prt], R[rt] = R[prt];
    if(l == r) tr[rt] = v;
    else {
        if(p <= mid) L[rt] = Upd(L[prt], l, mid, p, v);
        else R[rt] = Upd(R[prt], mid+1, r, p, v);
        tr[rt] = min(tr[ L[rt] ], tr[ R[rt] ]);
    }
    return rt;
}

int Query(int rt, int l, int r, int v) {
    if(l == r) return l;
    if(tr[ L[rt] ] < v) return Query(L[rt], l, mid, v);
    return Query(R[rt], mid+1, r, v);
}

int main() {
    scanf("%d%d%d", &n, &m, &kk);
    for(int i = 1, u, v; i <= m; ++i)
        scanf("%d%d", &u, &v), G[u].PB(v);
    int mx = -1;
    for(int i = 1; i <= n; ++i) {
        val[i] = mx + 1;
        for(auto it : G[i]) {
            --cnt[ val[it] ];
            if(cnt[ val[it] ] == 0) val[i] = min(val[i], val[it]);
        }
        mx = max(mx, val[i]);
        for(auto it : G[i]) ++cnt[ val[it] ];
        ++cnt[ val[i] ];
    }
    rot[0] = Build(0, n);
    for(int i = 1; i <= n; ++i) {
        rot[i] = Upd(rot[i-1], 0, n, val[i], i);
    }
    int ans = 0;
    for(int i = 1, l, r; i <= kk; ++i) {
        scanf("%d%d", &l, &r);
        ans ^= Query(rot[r], 0, n, l);
    }
    if(ans) puts("Alice");
    else puts("Bob");
    return 0;
}
