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

const int maxn = 2e6;

inline LL PowMod(LL a, LL b, LL P) { LL r=1; while(b) { if(b&1) r=r*a%P; a=a*a%P, b>>=1; } return r; }

int n, P;
LL b0, A, B;
LL ai[maxn+5];
LL Fac[maxn+5], InvFac[maxn+5], inv[maxn+5];

inline LL Cat(int n) { return Fac[n*2] * InvFac[n] % P * InvFac[n] % P * inv[n+1] % P; }

int main() {
    int _; scanf("%d", &_);
    while(_--) {
        scanf("%d%d%lld%lld%lld", &n, &P, &b0, &A, &B);
        Fac[0] = 1;
        REP(i,1,n*2) Fac[i] = Fac[i-1] * i % P;
        InvFac[n*2] = PowMod(Fac[n*2], P-2, P);
        PER(i,n*2-1,0) InvFac[i] = InvFac[i+1] * (i+1) % P;
        inv[1] = 1;
        REP(i,2,n+10) inv[i] = LL(P-P/i) * inv[P%i] % P;
        REP(i,1,n*2) {
            b0 = (A*b0 + B)  % P;
            ai[i] = (ai[i-1] + b0 + 1) % P;
            //printf("ai[%d] = %lld\n", i, ai[i]);
        }
        LL ans1 = 0, ans2 = 0;
        LL now = 0;
        REP(i,2,n*2) {
            if( !(i&1) ) {
                int k = i>>1;
                now = (now + Cat(k-1) * Cat(n-k)) % P;
            }
            ans1 = (ans1 + now*ai[i]) % P;
        }
        now = 0;
        PER(i,n*2-1,1) {
            if( !((n*2-i+1)&1) ) {
                int k = (n*2-i+1)>>1;
                now = (now + Cat(k-1) * Cat(n-k)) % P;
            }
            //printf("now2 = %lld, i = %d\n", now, i);
            ans2 = (ans2 + now*ai[i]) % P;
        }
        //printf("ans1 = %lld, ans2 = %lld, Cat(%d) = %lld\n", ans1, ans2, n, Cat(n));
        LL ans = (ans1-ans2+P) % P * Fac[n] % P * Fac[n] % P * InvFac[n*2] % P * (n+1) % P;
        printf("%lld\n", ans);
        //printf("%lld\n", (ans1-ans2+P) % P * PowMod(Cat(n), P-2, P) % P);
    }
    return 0;
}
