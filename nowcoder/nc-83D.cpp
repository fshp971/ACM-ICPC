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

const int maxn = 5e5;
const int md = 1e9 + 7;

inline LL PowMod(LL a, LL b) { LL r=1; while(b) { if(b&1) r=r*a%md; a=a*a%md, b>>=1; } return r; }

LL Fac[maxn + 5], InvFac[maxn + 5];
LL f[maxn + 5];

inline LL C(int n, int m) { return Fac[n] * InvFac[m] % md * InvFac[n-m] % md; }

int main() {
    Fac[0] = 1;
    for(int i = 1; i <= maxn; ++i) Fac[i] = Fac[i-1] * i % md;
    InvFac[maxn] = PowMod(Fac[maxn], md-2);
    for(int i = maxn-1; i >= 0; --i) InvFac[i] = InvFac[i+1] * (i+1) % md;
    f[1] = 1;
    for(int i = 2; i <= maxn; ++i) f[i] = ((i-1) * f[i-1] + (i-2) * f[i-2]) % md;
    int n, kk;
    scanf("%d%d", &n, &kk);
    LL ans = 0;
    for(int i = 0; i <= kk; ++i)
        ans = (ans + f[n-i] * C(n-1, i) % md) % md;
    printf("%lld\n", ans);
    return 0;
}
