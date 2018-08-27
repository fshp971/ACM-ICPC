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
#define PER(i,a,b) for(int i=a;i>=b;--i)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 5e5 + 10;
const int P = 1e9 + 7;

LL Inv[maxn + 5];
LL Fac[maxn + 5], InvFac[maxn + 5];
inline LL C(int n, int m) { return Fac[n] * InvFac[m] % P * InvFac[n-m] % P; }

inline LL Calc(LL n, LL k) {
    return C(n-1, k-2) * n % P * (n+1) % P * (n-k+1) % P * Inv[k] % P * Inv[k+1] % P;
}

int main() {
    Inv[1] = 1;
    REP(i,2,maxn) Inv[i] = LL(P - P/i) * Inv[P%i] % P;
    Fac[0] = 1, InvFac[0] = 1;
    REP(i,1,maxn) {
        Fac[i] = Fac[i-1] * i % P;
        InvFac[i] = InvFac[i-1] * Inv[i] % P;
    }

    int n; scanf("%d", &n);
    LL ans = 0;
    for(LL d = 1; d <= n-1; ++d) {
        for(LL k = 2; k <= n-(k-1)*(d-1); ++k)
            ans = ( ans + C(n-(k-1)*(d-1), k) * (k-1)*(d-1) + Calc(n-(k-1)*(d-1), k) ) % P;
    }
    printf("%lld\n", ans);
    return 0;
}
