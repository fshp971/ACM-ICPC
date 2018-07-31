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

const int maxn = 3000;
const int md = 998244353;

inline LL PowMod(LL a, LL b) { LL r=1; while(b) { if(b&1) r=r*a%md; a=a*a%md, b>>=1; } return r; }

LL Fac[maxn + 5], InvFac[maxn + 5];
int gg[maxn + 5][maxn + 5];
int two[maxn*maxn + 5];

void Pre() {
    Fac[0] = 1;
    for(int i = 1; i <= maxn; ++i) Fac[i] = Fac[i-1] * i % md;
    InvFac[maxn] = PowMod(Fac[maxn], md-2);
    for(int i = maxn-1; i >= 0; --i) InvFac[i] = InvFac[i+1] * (i+1) % md;

    LL one[2] = {1, md-1};
    for(int i = 0; i <= maxn; ++i) {
        gg[i][i] = InvFac[i];
        for(int k = i-1; k >= 0; --k)
            gg[i][k] = (gg[i][k+1] + InvFac[k] * InvFac[i-k] % md * one[(i-k)&1]) % md;
    }
    two[0] = 1;
    for(int i = 1; i <= maxn*maxn; ++i) two[i] = two[i-1] * 2 % md;
}

void Add(LL &a, LL b) { a+=b; if(a>=md) a-=md; }

int main() {
    Pre();
    int n, m, A, B;
    while(~scanf("%d%d%d%d", &n, &m, &A, &B)) {
        LL ans = 0;
        for(int i = 0; i <= n-A; ++i) {
            LL tmp = LL(gg[n-i][A]) * InvFac[i] % md;
            LL sum = 0;
            for(int k = 0; k <= m-B; ++k)
                Add(sum, LL(gg[m-k][B]) * InvFac[k] % md * two[i*k] % md);
            Add(ans, sum * tmp % md);
        }
        ans = ans * Fac[n] % md * Fac[m] % md;
        printf("%lld\n", ans);
    }
    return 0;
}
