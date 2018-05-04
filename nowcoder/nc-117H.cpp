#include <bits/stdc++.h>

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

const int maxn = 5e5;
const int maxnode = maxn << 2;

int n, m, seg[maxn + 5];
int mi[maxnode + 5], lz[maxnode + 5];

void Build(int x, int l, int r) {
    lz[x] = 0;
    if(l == r) mi[x] = seg[l];
    else {
        Build(lson, l, mid);
        Build(rson, mid+1, r);
        mi[x] = min(mi[lson], mi[rson]);
    }
}

void Upd(int x, int l, int r, int ll, int rr, int v) {
    if(ll <= l && r <= rr) lz[x] += v;
    else {
        if(ll <= mid) Upd(lson, l, mid, ll, rr, v);
        if(mid < rr) Upd(rson, mid+1, r, ll, rr, v);
        mi[x] = min(mi[lson] + lz[lson], mi[rson] + lz[rson]);
    }
}

void PushDown(int x, int l, int r) {
    lz[lson] += lz[x], lz[rson] += lz[x], mi[x] += lz[x], lz[x] = 0;
}

int Query0(int x, int l, int r, int p) {
    if(l == r) return mi[x] + lz[x];
    if(p <= mid) return Query0(lson, l, mid, p) + lz[x];
    return Query0(rson, mid+1, r, p) + lz[x];
}

int Query1(int x, int l, int r, int ll, int rr, int v) {
    if(ll <= l && r <= rr && lz[x] + mi[x] >= v) return -1;
    if(l == r) return l;
    PushDown(x,l,r);
    int res;
    if(ll <= mid) {
        res = Query1(lson, l, mid, ll, rr, v);
        if(res != -1) return res;
    }
    if(mid < rr) {
        res = Query1(rson, mid+1, r, ll, rr, v);
        if(res != -1) return res;
    }
    return -1;
}

int Query2(int x, int l, int r, int ll, int rr, int v) {
    if(l == r) return l;
    PushDown(x,l,r);
    if(lz[rson] + mi[rson] <= v)
        return Query2(rson, mid+1, r, ll, rr, v);
    return Query2(lson, l, mid, ll, rr, v);
}

char str[maxn + 5];
int main() {
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d%s", &n, &m, str+1);
        for(int i = 1; i <= n; ++i)
            seg[i] = seg[i-1] + (str[i] == '(' ? 1 : -1);
        Build(1, 0, n);
        while(m--) {
            int o, x;
            scanf("%d%d", &o, &x);
            if(o == 1) {
                if(str[x] == '(')
                    Upd(1,0,n,x,n,-2), str[x] = ')';
                else
                    Upd(1,0,n,x,n,2), str[x] = '(';
            }
            else {
                int sub = Query0(1,0,n,x-1);
                int p = Query1(1,0,n,x,n,sub);
                if(p != -1) { printf("%d\n", p-x); continue; }
                printf("%d\n", Query2(1,0,n,x,n,sub) - (x-1));
            }
        }
    }
    return 0;
}
