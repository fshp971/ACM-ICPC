#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<cassert>
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
const int md = 1e9 + 7;

LL PowMod(LL a, LL b) { LL r=1; while(b) { if(b&1) r=r*a%md; a=a*a%md, b>>=1; } return r; }

int n;
LL xi[maxn + 5], yi[maxn + 5], di[maxn + 5];

int main() {
    scanf("%d", &n);
    for(int i = 0; i <= n; ++i) {
        scanf("%lld%lld", xi + i, yi + i);
        xi[i] = (xi[i] + md) % md, yi[i] = (yi[i] + md) % md;
    }
    for(int i = 1; i <= n; ++i)
        di[i] = LL(yi[i] - yi[i-1] + md) % md * PowMod((xi[i] - xi[i-1] + md) % md, md-2) % md;
    LL sum1 = 0, sum2 = 0, inv2 = PowMod(2, md-2);
    for(int i = 1; i < n; ++i) {
        sum1 = (sum1 + (di[i+1] - di[i] + md) % md * inv2 % md * (xi[i] - xi[0] + md) % md) % md;
        sum2 = (sum2 + (di[i+1] - di[i] + md) % md * inv2 % md * (xi[n] - xi[i] + md) % md) % md;
    }
    if((di[1]+di[n])%md == 0 && sum1 == yi[0] && sum2 == yi[n]) puts("Yes");
    else puts("No");
    return 0;
}
