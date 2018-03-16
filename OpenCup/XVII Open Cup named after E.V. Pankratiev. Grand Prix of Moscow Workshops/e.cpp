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

const int maxn = 2e5, maxnode = maxn << 2, maxk = 18;


struct Tree {
    int mi[maxnode + 5], mx[maxnode + 5];
    void Build(int x, int l, int r, pii* a) {
        if(l == r) mi[x] = a[l].fi, mx[x] = a[l].se;
        else {
            Build(lson, l, mid, a);
            Build(rson, mid+1, r, a);
            mi[x] = min(mi[lson], mi[rson]);
            mx[x] = max(mx[lson], mx[rson]);
        }
    }
    pii Query(int x, int l, int r, int ll, int rr) {
        if(ll <= l && r <= rr) return MP(mi[x], mx[x]);
        int rmi = 1<<30, rmx = -(1<<30);
        pii tmp;
        if(ll <= mid) {
            tmp = Query(lson, l, mid, ll, rr);
            rmi = min(rmi, tmp.fi), rmx = max(rmx, tmp.se);
        }
        if(mid < rr) {
            tmp = Query(rson, mid+1, r, ll, rr);
            rmi = min(rmi, tmp.fi), rmx = max(rmx, tmp.se);
        }
        return MP(rmi, rmx);
    }
} tree[maxk + 2];

int n, seg[maxn + 5];
int mi[maxn + 5], mx[maxn + 5];
pii ran[maxk + 2][maxn + 5];
pii re[maxn + 5], retmp[maxn + 5];

bool cmp(int a, int b) { return retmp[a] < retmp[b]; }

int main() {
    scanf("%d", &n);
    REP(i,1,n) {
        scanf("%d", seg + i);
        ran[0][i] = MP( max(1,i-seg[i]), min(n,i+seg[i]) );
    }
    tree[0].Build(1, 1, n, ran[0]);
    for(int k = 1; k < maxk; ++k) {
        for(int i = 1; i <= n; ++i)
            ran[k][i] = tree[k-1].Query(1, 1, n, ran[k-1][i].fi, ran[k-1][i].se);
        tree[k].Build(1, 1, n, ran[k]);
    }
    int ans = 0;
    REP(i,1,n) re[i] = MP(i,i);
    for(int k = maxk-1; k >= 0; --k) {
        for(int i = 1; i <= n; ++i) {
            pii tmp = tree[k].Query(1, 1, n, re[i].fi, re[i].se);
            retmp[i] = MP( min(re[i].fi,tmp.fi), max(re[i].se,tmp.se) );
            mi[i] = retmp[i].se, mx[i] = retmp[i].fi;
        }
        for(int i = 2; i <= n; ++i) mi[i] = min(mi[i], mi[i-1]);
        for(int i = n-1; i >= 1; --i) mx[i] = max(mx[i], mx[i+1]);
        int fg = 0;
        for(int i = 1; i <= n && !fg; ++i) {
            if(retmp[i].se+1 <= n && i < mx[retmp[i].se+1]) fg |= 1;
            if(retmp[i].fi-1 >= 1 && i > mi[retmp[i].fi-1]) fg |= 1;
        }
        if(fg) {
            ans |= 1<<k;
            for(int i = 1; i <= n; ++i)
                re[i] = retmp[i];
        }
    }
    printf("%d\n", ans+1);
    return 0;
}
