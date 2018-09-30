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
#include<stack>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define PER(i,a,b) for(int i=a; i>=b; --i)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
#define lson (x<<1)
#define rson ((x<<1)|1)
#define mid ((l+r)>>1)
typedef long long LL;
typedef pair<int,int> pii;

const int P = 1e9+7;
const int maxn = 2e5;
const int maxnode = maxn<<2;

int n, q;
LL p[maxn+5], ai[maxn+5], si[maxn+5];
LL tr[maxnode+5], lz[maxnode+5];

void Add(int x, LL v) { for(;x<=n;x+=x&(-x)) si[x]+=v; }
LL Sum(int x) { LL r=0; for(;x;x-=x&(-x)) r+=si[x]; return r; }

void Build(int x, int l, int r) {
    if(l == r) tr[x] = Sum(l)%P * (p[l+1]-p[l]-1) % P;
    else {
        Build(lson, l, mid); Build(rson, mid+1, r);
        tr[x] = (tr[lson] + tr[rson]) % P;
    }
}

void PushDown(int x, int l, int r) {
    lz[lson] = (lz[lson]+lz[x]) % P;
    lz[rson] = (lz[rson]+lz[x]) % P;
    tr[lson] = (tr[lson] + (p[mid+1]-p[l]-(mid+1-l))*lz[x]) % P;
    tr[rson] = (tr[rson] + (p[r+1]-p[mid+1]-(r-mid))*lz[x]) % P;
    lz[x] = 0;
}

void Upd(int x, int l, int r, int ll, int rr, LL v) {
    if(ll<=l && r<=rr) {
        lz[x] = (lz[x]+v) % P;
        tr[x] = (tr[x] + (p[r+1]-p[l]-(r+1-l))*v) % P;
    }
    else {
        PushDown(x,l,r);
        if(ll<=mid) Upd(lson, l, mid, ll, rr, v);
        if(mid<rr) Upd(rson, mid+1, r, ll, rr, v);
        tr[x] = (tr[lson] + tr[rson]) % P;
    }
}

LL Query(int x, int l, int r, int ll, int rr) {
    if(ll<=l && r<=rr) return tr[x];
    PushDown(x,l,r);
    LL ret = 0;
    if(ll<=mid) ret = Query(lson, l, mid, ll, rr);
    if(mid<rr) ret = (ret + Query(rson, mid+1, r, ll, rr)) % P;
    return ret;
}

int main() {
    scanf("%d%d", &n, &q);
    REP(i,1,n) scanf("%lld", p+i);
    REP(i,1,n) scanf("%lld", ai+i), Add(i,ai[i]);
    Build(1,0,n-1);
    while(q--) {
        int a, b; scanf("%d%d", &a, &b);
        if(a<0) {
            a = -a;
            LL da = b-ai[a];
            ai[a] = b;
            Add(a,da);
            if(a<=n-1) Upd(1, 0, n-1, a, n-1, (da+P)%P);
        }
        else {
            LL sl = Sum(a-1), sr = Sum(b);
            int l = a, r = b-1, pt = a-1;
            while(l<=r) {
                LL sm = Sum(mid);
                if(sm-sl < sr-sm) pt = mid, l = mid+1;
                else r = mid-1;
            }
            LL ans = 0;
            if(pt>=a) {
                ans = (ans + Query(1, 0, n-1, a, pt)) % P;
                ans = ( ans - sl%P * (p[pt+1]-p[a]-(pt-a+1)) % P + P ) % P;
            }
            if(pt+1<=b-1) {
                ans = (ans - Query(1, 0, n-1, pt+1, b-1) + P) % P;
                ans = ( ans + sr%P * (p[b]-p[pt+1]-(b-1-pt)) ) % P;
            }
            printf("%lld\n", ans);
        }
    }
    return 0;
}
