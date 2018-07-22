//#include<cstdio>
#include<stdio.h>
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
typedef pair<int,int> pii;

const int maxk = 2000 + 10;
const int md = 1e9 + 7;

inline LL PowMod(LL a, LL b) { a%=md; LL r=1; while(b) { if(b&1) r=r*a%md; a=a*a%md, b>>=1; } return r; }

LL Fac[maxk + 5], InvFac[maxk + 5], B[maxk + 5];
inline LL C(int n, int m) { return Fac[n] * InvFac[m] % md * InvFac[n-m] % md; }

int main() {
    Fac[0] = 1;
    for(int i = 1; i <= maxk; ++i) Fac[i] = Fac[i-1] * i % md;
    InvFac[maxk] = PowMod(Fac[maxk], md-2);
    for(int i = maxk-1; i >= 0; --i) InvFac[i] = InvFac[i+1] * (i+1) % md;
    B[0] = 1;
    for(int i = 1; i < maxk; ++i) {
        LL tmp = 0;
        for(int k = 0; k < i; ++k)
            tmp = (tmp + C(i+1, k) * B[k]) % md;
        tmp = tmp * PowMod(i+1, md-2) % md;
        B[i] = (md - tmp) % md;
    }

    int T; scanf("%d", &T);
    while(T--) {
        LL n; int kk;
        scanf("%lld%d", &n, &kk);
        LL ans = 0;
        for(int i = 0; i <= kk; ++i)
            ans = (ans + C(kk+1,i) * B[i] % md * PowMod(n+1,kk+1-i)) % md;
        ans = ans * PowMod(kk+1, md-2) % md;
        printf("%lld\n", ans);
    }
    return 0;
}
