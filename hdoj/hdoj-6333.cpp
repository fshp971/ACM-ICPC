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
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 1e5;
const int sq = 300;
const int md = 1e9 + 7;

inline LL PowMod(LL a, LL b) { LL r=1; while(b) { if(b&1) r=r*a%md; a=a*a%md, b>>=1; } return r; }
inline void Add(LL &a, LL b) { a+=b; if(a>=md) a-=md; }

LL Fac[maxn + 5], InvFac[maxn + 5];
int S[maxn + 5][410];

inline LL C(int n, int m) {
    if(n<m) return 0LL;
    return Fac[n] * InvFac[m] % md * InvFac[n-m] % md;
}

void Pre() {
    Fac[0] = 1;
    for(int i = 1; i <= maxn; ++i) Fac[i] = Fac[i-1] * i % md;
    InvFac[maxn] = PowMod(Fac[maxn], md-2);
    for(int i = maxn-1; i >= 0; --i) InvFac[i] = InvFac[i+1] * (i+1) % md;

    LL now = 0;
    for(int i = 0, t = 1; i <= maxn; ++i) {
        Add(now, C(maxn,i));
        if((i+1)%sq == 0) S[maxn][t++] = now;
    }
    LL inv2 = PowMod(2, md-2);
    for(int i = maxn-1; i >= 1; --i) {
        for(int k = sq-1, t = 1; k <= i; k += sq, ++t)
            S[i][t] = (S[i+1][t] + C(i,k)) * inv2 % md;
    }
}

int main() {
    Pre();
    int T; scanf("%d", &T);
    while(T--) {
        int n, m; scanf("%d%d", &n, &m);
        LL ans = S[n][m/sq];
        for(int i = (m/sq)*sq; i <= m; ++i)
            Add(ans, C(n,i));
        printf("%lld\n", ans);
    }
    return 0;
}
