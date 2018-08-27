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
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
#define lson (x<<1)
#define rson (x<<1|1)
#define mid ((l+r)>>1)
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 2e5;
const int maxnode = maxn << 2;

int tr[maxnode + 5], lz[maxnode + 5];

void Build(int x, int l, int r) {
    lz[x] = 0;
    if(l == r) tr[x] = l;
    else {
        Build(lson, l, mid);
        Build(rson, mid+1, r);
        tr[x] = min(tr[lson], tr[rson]);
    }
}

void Add(int x, int l, int r, int ll, int rr, int v) {
    if(ll <= l && r <= rr) lz[x] += v, tr[x] += v;
    else {
        lz[lson] += lz[x], tr[lson] += lz[x];
        lz[rson] += lz[x], tr[rson] += lz[x];
        lz[x] = 0;
        if(ll <= mid) Add(lson, l, mid, ll, rr, v);
        if(mid < rr) Add(rson, mid+1, r, ll, rr, v);
        tr[x] = min(tr[lson], tr[rson]);
    }
}

int n, ps[maxn + 5];

int bit[maxn + 5];
void Inc(int x) { for(;x<=n;x+=x&(-x)) ++bit[x]; }
int Sum(int x) { int r=0; for(;x;x-=x&(-x)) r+=bit[x]; return r; }

int main() {
    scanf("%d", &n), n>>=1;
    LL ans = 0;
    for(int i = 1, a; i <= n; ++i) {
        scanf("%d", &a), a >>= 1;
        ps[a] = i;
        Inc(a);
        ans += i - Sum(a);
    }
    Build(1, 0, n);
    for(int i = 1; i <= n; ++i) {
        ans += tr[1];
        Add(1, 0, n, 0, ps[i]-1, 1);
        Add(1, 0, n, ps[i], n, -1);
    }
    printf("%lld\n", ans);
    return 0;
}
