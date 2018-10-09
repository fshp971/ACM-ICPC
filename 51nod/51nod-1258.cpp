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
const int maxn = 50000+10;

inline LL PowMod(LL a, LL b) { LL r=1; while(b) { if(b&1) r=r*a%P; a=a*a%P, b>>=1; } return r; }

LL f[maxn+5], inv[maxn+5];
LL pfx[maxn+5], sfx[maxn+5];

LL Lagrange(LL n, LL x) {
    x %= P;
    LL div = 1;
    REP(i,1,n-1) div = div * LL(-i+P) % P;
    div = PowMod(div, P-2);
    pfx[0] = sfx[n+1] = 1;
    REP(i,1,n) pfx[i] = ((x-i+P)%P) * pfx[i-1] % P;
    PER(i,n,1) sfx[i] = ((x-i+P)%P) * sfx[i+1] % P;
    LL ret = 0;
    REP(i,1,n) {
        ret = (ret + pfx[i-1] * sfx[i+1] % P * div % P * f[i]) % P;
        div = div * inv[i] % P * (P-(n-i)) % P;
    }
    return ret;
}

int main() {
    LL n; int kk;
    inv[1] = 1;
    REP(i,2,maxn) inv[i] = LL(P-P/i) * inv[P%i] % P;
    int _; scanf("%d", &_);
    while(_--) {
        scanf("%lld%d", &n, &kk);
        REP(i,1,kk+2) f[i] = (PowMod(i,kk) + f[i-1]) % P;
        printf("%lld\n", Lagrange(kk+2,n));
    }
    return 0;
}
