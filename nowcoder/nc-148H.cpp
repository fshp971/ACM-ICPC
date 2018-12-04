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
//typedef long long LL;
typedef __int128 LL;
typedef pair<int,int> pii;

const int P = 998244353;

LL Gcd(LL a, LL b) { return b ? Gcd(b,a%b) : a; }
inline LL PowMod(LL a, LL b) { LL r=1; while(b) { if(b&1) r=r*a%P; a=a*a%P, b>>=1; } return r; }
const int inv2 = PowMod(2,P-2);

inline LL S1(LL n) { n%=P; return n*(n+1)%P*inv2%P; }

LL F(LL n, LL a, LL b) {
    LL ret = 0;
    if(a>=b) {
        ret = (a/b) * S1(n) % P;
        a%=b;
    }
    if(a*n<b) return ret;
    LL lim = a*n/b;
    ret = (ret + (n%P)*(lim%P) + (n/b) - F(lim,b,a) + P) % P;
    return ret;
}

LL Calc(LL a, LL b, LL c, LL d) {
    LL g;
    g = Gcd(a,b), a/=g, b/=g;
    g = Gcd(c,d), c/=g, d/=g;
    if(c*b==a*d) return -1;
    if(c*b<a*d) swap(a,c), swap(b,d);
    LL n = (a*d+b*d) / (b*c-a*d);
    LL ans = (n+1 + F(n+1,a,b) - F(n,c,d) + P) % P;
    return ans;
}

int main() {
    int _; scanf("%d", &_);
    int a,b,c,d;
    while(_--) {
        scanf("%d%d%d%d", &a, &b, &c, &d);
        printf("%lld\n", (long long)Calc(a,b,c,d));
    }
    return 0;
}
