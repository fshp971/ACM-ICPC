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
#include<stack>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int,int> pii;

const int maxn = 5e4;
const int maxnode = maxn * 40;

int tot = 0;
int ss[maxnode + 5], mul[maxnode + 5], mm[maxnode + 5];
int L[maxnode + 5], R[maxnode + 5];
LL sum[maxnode + 5];

LL Gcd(LL a, LL b) { return b ? Gcd(b,a%b) : a; }

ULL S2(ULL n) {
    if(n&1) return ((n+1)>>1) * n;
    return (n>>1) * (n+1);
}

ULL Solve(ULL n, ULL a, ULL b) {
    if(a*n < b) return 0;
    if(a >= b) return (a/b) * S2(n) + Solve(n, a%b, b);
    return (a*n/b) * n + (n/b) - Solve(a*n/b, b, a);
}

ULL Calc(ULL n, ULL a, ULL b) {
    ULL g = Gcd(a,b);
    return a * S2(n) - b * Solve(n, a/g, b/g);
}

inline void ReCalc(int x, int l, int r) {
    sum[x] = Calc(r-ss[x]+1, mul[x], mm[x]) - Calc(l-1-ss[x]+1, mul[x], mm[x]);
}

void PushDown(int x, int l, int r) {
    if(ss[x]) {
        int &lson = L[x], &rson = R[x];
        if(!lson) lson = ++tot;
        if(!rson) rson = ++tot;
        int mid = (l + r) >> 1;
        ss[lson] = ss[rson] = ss[x], ss[x] = 0;
        mul[lson] = mul[rson] = mul[x];
        mm[lson] = mm[rson] = mm[x];
        ReCalc(lson, l, mid);
        ReCalc(rson, mid+1, r);
    }
}

void Upd(int x, int l, int r, int ll, int rr, int a, int b) {
    if(ll <= l && r <= rr) ss[x] = ll, mul[x] = a, mm[x] = b, ReCalc(x, l, r);
    else {
        PushDown(x, l, r);
        int mid = (l + r) >> 1;
        if(ll <= mid) Upd(L[x], l, mid, ll, rr, a, b);
        if(mid < rr) Upd(R[x], mid+1, r, ll, rr, a, b);
        sum[x] = sum[ L[x] ] + sum[ R[x] ];
    }
}

LL Query(int x, int l, int r, int ll, int rr) {
    if(ll <= l && r <= rr) return sum[x];
    if(ss[x]) {
        int lll = max(ll, l), rrr = min(rr, r);
        return Calc(rrr-ss[x]+1, mul[x], mm[x]) - Calc(lll-1-ss[x]+1, mul[x], mm[x]);
    }
    PushDown(x, l, r);
    int mid = (l + r) >> 1;
    LL res = 0;
    if(ll <= mid) res += Query(L[x], l, mid, ll, rr);
    if(mid < rr) res += Query(R[x], mid+1, r, ll, rr);
    return res;
}

int main() {
    int n, T, rt = 0;
    ss[rt] = 1, mm[rt] = 1;
    scanf("%d%d", &n, &T);
    while(T--) {
        int o, l, r, a, b;
        scanf("%d%d%d", &o, &l, &r);
        if(o == 1) {
            scanf("%d%d", &a, &b);
            Upd(rt, 1, n, l, r, a, b);
        }
        else
            printf("%lld\n", Query(rt, 1, n, l, r));
    }
    return 0;
}
