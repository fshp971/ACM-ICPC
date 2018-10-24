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
typedef unsigned long long ULL;
typedef pair<int,int> pii;

ULL Run(ULL a, ULL b, ULL c, ULL n) {
    ULL ret = ((n*(n+1)) >> 1) * (a/c);
    ret ^= (n+1) * (b/c);
    a %= c, b %= c;
    ULL nn = (a*n+b) / c;
    if(nn >= 1) {
        ret ^= ((n+2)*nn) ^ Run(c, c-b-1, a, nn-1);
    }
    return ret;
}

LL Calc(LL a, LL b, LL n) {
    LL lim = a*n+b, p = 1, ret = 0;
    while(p <= lim) {
        ret ^= (Run(a,b,p,n)&1) ? p : 0;
        p <<= 1;
    }
    return ret;
}

const int maxn = 1e7;

int main() {
    int _; scanf("%d", &_);
    while(_--) {
        LL n; scanf("%lld", &n);
        LL ans = 0;
        for(LL i = 1; i <= n && i <= maxn; ++i) ans ^= n%i;
        for(LL i = maxn+1, nx; i <= n; i = nx+1) {
            nx = n / (n/i);
            LL a = n/i, b = n%nx, t = nx-i;
            ans ^= Calc(a, b, t);
        }
        printf("%lld\n", ans);
    }
    return 0;
}
