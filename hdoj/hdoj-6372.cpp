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

const int maxn = 15e5 + 10;
const int P = 1e9 + 7;

int Fac[maxn+5], InvFac[maxn+5];
int prime[maxn+5];
bool vis[maxn+5];

inline LL C(int n, int m) { return LL(Fac[n]) * InvFac[m] % P * InvFac[n-m] % P; }
inline LL PowMod(LL a, LL b) { LL r=1; while(b) { if(b&1) r=r*a%P; a=a*a%P, b>>=1; } return r; }

void Pre() {
    int tot = 1;
    prime[1] = 2;
    for(int i = 3; i <= maxn; i += 2) {
        if(!vis[i]) {
            prime[++tot] = i;
            for(LL k = LL(i)*i; k <= maxn; k += i)
                vis[k] = 1;
        }
    }
    Fac[0] = 1;
    REP(i,1,maxn) Fac[i] = LL(Fac[i-1])*i%P;
    InvFac[maxn] = PowMod(Fac[maxn], P-2);
    PER(i,maxn-1,0) InvFac[i] = LL(InvFac[i+1])*(i+1)%P;
}

inline LL Calc(int n, LL v) {
    if(v==0) return 0;
    if(v==1) return n;
    return (PowMod(v,n)-1+P) * v % P * PowMod(v-1,P-2) % P;
}

int main() {
    Pre();
    int _; scanf("%d", &_);
    while(_--) {
        int cc, n, kk;
        scanf("%d%d%d", &cc, &n, &kk);
        LL ans = 0;
        for(int j = 1; j <= kk; ++j) {
            ans += Calc(n, C(prime[cc]+j, j+1));
            if(ans >= P) ans -= P;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
