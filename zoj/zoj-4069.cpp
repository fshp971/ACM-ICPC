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
typedef long long LL;
typedef pair<int,int> pii;

const int P = 1e9+7;
const int maxn = 3e5;

inline LL PowMod(LL a, LL b) { LL r=1; while(b) { if(b&1) r=r*a%P; a=a*a%P, b>>=1; } return r; }

LL Fac[maxn+5], InvFac[maxn+5];
LL inv2 = PowMod(2, P-2), ipw2[maxn+5], pw2[maxn+5];

inline LL C(int n, int m) {
    assert(n>=m && m>=0 && n<=maxn);
    return Fac[n] * InvFac[m] % P * InvFac[n-m] % P;
}

LL Calc(int n, int m) {
    LL res = 0;
    for(int i = 0; i <= n; ++i) {
        int ii = m*2-i;
        if(ii<0 || ii>m) continue;
        LL cof1 = C(m,ii) * pw2[ii] % P;
        if((m-ii)&1) cof1 = (P-cof1) % P;
        LL cof2 = C(n-i+m-1, n-i);
        res = (res + cof1*cof2) % P;
    }
    res = res * ipw2[m] % P * Fac[n] % P * InvFac[m] % P;
    return res;
}

int main() {
    Fac[0] = 1, ipw2[0] = 1, pw2[0] = 1;
    REP(i,1,maxn) {
        Fac[i] = Fac[i-1] * i % P;
        ipw2[i] = ipw2[i-1] * inv2 % P;
        pw2[i] = pw2[i-1] * 2 % P;
    }
    InvFac[maxn] = PowMod(Fac[maxn], P-2);
    PER(i,maxn-1,0) InvFac[i] = InvFac[i+1] * (i+1) % P;
    int _; scanf("%d", &_);
    while(_--) {
        int n;
        LL m;
        scanf("%d%lld", &n, &m);
        if(n<m) puts("0");
        else if(n==m) printf("%lld\n", Fac[n-1] * inv2 % P);
        else printf("%lld\n", Calc(n,n-m));
    }
    return 0;
}
