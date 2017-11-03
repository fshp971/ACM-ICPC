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

const int maxn = 15e4, maxnode = maxn << 2;

int n, m, hh, ai[maxn + 5], bi[maxn + 5];
int tree[maxnode + 5], lazy[maxnode + 5];

void Build(int x, int l, int r) {
    lazy[x] = 0;
    if(l == r) tree[x] = -l;
    else {
        Build(lson, l, mid);
        Build(rson, mid + 1, r);
        tree[x] = min(tree[lson], tree[rson]);
    }
}

void Update(int x, int l, int r, int ll, int rr, int del) {
    if(ll <= l && r <= rr) lazy[x] += del;
    else {
        if(ll <= mid) Update(lson, l, mid, ll, rr, del);
        if(mid < rr) Update(rson, mid + 1, r, ll, rr, del);
        tree[x] = min(tree[lson] + lazy[lson], tree[rson] + lazy[rson]);
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &hh);
    REP(i,1,m) scanf("%d", bi + i);
    sort(bi + 1, bi + 1 + m);
    REP(i,1,n) {
        scanf("%d", ai + i);
        ai[i] = lower_bound(bi + 1, bi + 1 + m, hh - ai[i]) - bi;
    }
    Build(1, 1, m);
    for(int i = 1; i <= m - 1; ++i)
        if(ai[i] <= m) Update(1, 1, m, ai[i], m, 1);
    int ans = 0;
    for(int i = 1, k = m; k <= n; ++i, ++k) {
        if(ai[k] <= m) Update(1, 1, m, ai[k], m, 1);
        if(tree[1] + lazy[1] >= 0) ++ans;
        if(ai[i] <= m) Update(1, 1, m, ai[i], m, -1);
    }
    printf("%d\n", ans);
    return 0;
}
