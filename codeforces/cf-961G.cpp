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

const int maxn = 2e5;
const int md = 1e9 + 7;

inline LL PowMod(LL a, LL b) { LL r=1; while(b) { if(b&1) r=r*a%md; a=a*a%md, b>>=1; } return r; }

LL Fac[maxn + 5], InvFac[maxn + 5], no[maxn + 5];

inline LL C(int n, int m) { return Fac[n] * InvFac[m] % md * InvFac[n-m] % md; }

LL S(int n, int k) {
    LL res = 0;
    for(int i = 1; i <= k; ++i)
        res = (res + no[k-i] * C(k,i) % md * PowMod(i,n)) % md;
    return res * InvFac[k] % md;
}

int main() {
    Fac[0] = 1, no[0] = 1;
    for(int i = 1; i <= maxn; ++i) Fac[i] = Fac[i-1] * i % md, no[i] = no[i-1] * (md-1) % md;
    InvFac[maxn] = PowMod(Fac[maxn], md-2);
    for(int i = maxn-1; i >= 0; --i) InvFac[i] = InvFac[i+1] * (i+1) % md;
    int n, kk;
    LL sum = 0;
    scanf("%d%d", &n, &kk);
    for(int i = 1, a; i <= n; ++i) scanf("%d", &a), sum = (sum + a) % md;
    LL tmp = (S(n,kk) + S(n-1,kk) * (n-1)) % md;
    printf("%lld\n", tmp * sum % md);
    return 0;
}
