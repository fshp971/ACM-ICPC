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

const int maxn = 5e5;
const int maxnode = maxn << 2;

int n, val[maxn + 5];
int tree[maxnode + 5];

int Gcd(int a, int b) { return b ? Gcd(b, a%b) : a; }

void Build(int x, int l, int r) {
    if(l == r) tree[x] = val[l];
    else {
        Build(lson, l, mid);
        Build(rson, mid + 1, r);
        tree[x] = Gcd(tree[lson], tree[rson]);
    }
}

void Upd(int x, int l, int r, int ps, int vv) {
    if(l == r) tree[x] = vv;
    else {
        if(ps <= mid) Upd(lson, l, mid, ps, vv);
        else Upd(rson, mid + 1, r, ps, vv);
        tree[x] = Gcd(tree[lson], tree[rson]);
    }
}

int chan;
int Check(int x, int l, int r, int ll, int rr, int vv) {
    if(ll <= l && r <= rr) {
        if(tree[x] % vv) {
            if(chan == 0) return 0;
            if(l == r) { chan = 0; return 1; }
            if(tree[lson]%vv && tree[rson]%vv) return 0;
            if(tree[lson]%vv)
                return Check(lson, l, mid, ll, rr, vv);
            else
                return Check(rson, mid+1, r, ll, rr, vv);
        }
        return 1;
    }
    if(rr <= mid) return Check(lson, l, mid, ll, rr, vv);
    if(mid+1 <= ll) return Check(rson, mid+1, r, ll, rr, vv);

    int err;
    err = Check(lson, l, mid, ll, rr, vv);
    if(err == 0) return 0;
    err = Check(rson, mid+1, r, ll, rr, vv);
    if(err == 0) return 0;
    return 1;
}

int main() {
    scanf("%d", &n);
    REP(i,1,n) scanf("%d", val + i);
    Build(1,1,n);
    int T, ord, l, r, x, ps;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &ord);
        if(ord == 1) {
            scanf("%d%d%d", &l, &r, &x);
            chan = 1;
            if(!Check(1,1,n,l,r,x))
                puts("NO");
            else puts("YES");
        }
        else {
            scanf("%d%d", &ps, &x);
            Upd(1,1,n,ps,x);
        }
    }
    return 0;
}
