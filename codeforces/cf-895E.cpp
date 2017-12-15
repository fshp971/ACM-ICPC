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

const int maxn = 1e5, maxnode = maxn << 2;

int seg[maxn + 5];
double tree[maxnode + 5], cof[maxnode + 5], del[maxnode + 5];

void Build(int x, int l, int r) {
    cof[x] = 1, del[x] = 0;
    if(l == r) { tree[x] = seg[l]; return; }
    Build(lson, l, mid);
    Build(rson, mid + 1, r);
    tree[x] = tree[lson] + tree[rson];
}

void PushDown(int x, int l, int r) {
    cof[lson] *= cof[x], del[lson] = del[lson] * cof[x] + del[x];
    cof[rson] *= cof[x], del[rson] = del[rson] * cof[x] + del[x];
    tree[lson] = tree[lson] * cof[x] + del[x] * (mid-l+1);
    tree[rson] = tree[rson] * cof[x] + del[x] * (r-mid);
    cof[x] = 1, del[x] = 0;
}

void Upd(int x, int l, int r, int ll, int rr, double mu, double ad) {
    if(ll <= l && r <= rr) {
        cof[x] *= mu, del[x] = del[x] * mu + ad;
        tree[x] = tree[x] * mu + ad * (r-l+1);
    }
    else {
        PushDown(x, l, r);
        if(ll <= mid) Upd(lson, l, mid, ll, rr, mu, ad);
        if(mid < rr) Upd(rson, mid + 1, r, ll, rr, mu, ad);
        tree[x] = cof[x] * (tree[lson] + tree[rson]) + del[x] * (r-l+1);
    }
}

double Query(int x, int l, int r, int ll, int rr) {
    if(ll <= l && r <= rr) return tree[x];
    double ret = 0;
    if(ll <= mid) ret += Query(lson, l, mid, ll, rr);
    if(mid < rr) ret += Query(rson, mid + 1, r, ll, rr);
    return cof[x] * ret + del[x] * (min(rr, r) - max(ll, l) + 1);
}

int main() {
    int n, T, od, l1, r1, l2, r2;
    scanf("%d%d", &n, &T);
    for(int i = 1; i <= n; ++i) scanf("%d", seg + i);
    Build(1, 1, n);
    while(T--) {
        scanf("%d", &od);
        if(od == 1) {
            scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
            int len1 = (r1-l1+1), len2 = (r2-l2+1);
            double sum1 = Query(1, 1, n, l1, r1);
            double sum2 = Query(1, 1, n, l2, r2);
            Upd(1, 1, n, l1, r1, double(len1-1)/len1, sum2/len1/len2);
            Upd(1, 1, n, l2, r2, double(len2-1)/len2, sum1/len1/len2);
        }
        else {
            scanf("%d%d", &l1, &r1);
            printf("%.7f\n", Query(1, 1, n, l1, r1));
        }
    }
    return 0;
}
