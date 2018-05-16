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

inline LL S2(LL n) {
    if(n&1) return ((n+1)>>1) * n;
    return (n>>1) * (n+1);
}

LL Solve(LL a, LL b, LL c, LL n) {
    if(a >= b) return (a/b) * S2(n) + Solve(a%b, b, c, n);
    if(c >= b) return (c/b) * n + Solve(a, b, c%b, n);
    if(c < 0) {
        c = -c;
        return Solve(a, b, b + (c/b)*b - c, n) - n * (c/b+1);
    }
    if((a)*n+c < b) return 0;
    if(a == 0 || n == 0) return n * (c/b);
    return (a*n+c)/b * n - Solve(b, a, -c-1, (a*n+c) / b);
}

int main() {
    LL a, b, c;
    scanf("%lld%lld%lld", &a, &b, &c);
    LL ans = ((c%a)/b) + (c/a) + 1 + Solve(a, b, c%a, c/a);
    printf("%lld\n", ans);
    return 0;
}
