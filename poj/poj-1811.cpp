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
#define PER(i,a,b) for(int i=a; i>=b; --i)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
typedef long long LL;
typedef pair<int,int> pii;

LL Gcd(LL a, LL b) { return b ? Gcd(b,a%b) : a; }
const long double eps = 1e-8;
LL MulMod(LL a,LL b,LL c) {
	a%=c, b%=c;
	LL ans=a*b-(LL)((long double)a*b/c+eps)*c;
	if(ans<0) ans+=c;
	return ans;
}
LL PowMod(LL a, LL b, LL p) {
    LL r = 1 % p;
    while(b) {
        if(b&1) r = MulMod(r,a,p);
        a = MulMod(a,a,p);
        b >>= 1;
    }
    return r;
}

const int MaxTry = 10;

bool MillerRabin(LL n) {
    if(n==2) return true;
    if(n==0 || n==1 || !(n&1)) return false;
    LL u = n-1, t = 0;
    while((u&1) == 0) u >>= 1, ++t;
    for(int s = 1; s <= MaxTry; ++s) {
        LL a = rand() % (n-1) + 1;
        LL x = PowMod(a, u, n);
        for(int i = 1; i <= t; ++i) {
            LL tx = MulMod(x, x, n);
            if(tx==1 && x!=1 && x!=n-1) return false;
            x = tx;
        }
        if(x!=1) return false;
    }
    return true;
}

LL PollardRho(LL n) {
    LL x = rand() % (n-1);
    LL c = rand() % (n-1) + 1;
    LL y = x;
    for(LL i = 1, k = 2; ; ++i) {
        x = (MulMod(x,x,n)+c) % n;
        LL d = Gcd(x>y ? x-y : y-x, n);
        if(d!=1 && d!=n) return PollardRho(d);
        if(x == y) return n;
        if(i == k) y = x, k <<= 1;
    }
}

int tot;
LL deco[100];
void Deco(LL n) {
    if(n == 1) return;
    if(MillerRabin(n)) { deco[++tot] = n; return; }
    LL p = n;
    while(p == n) p = PollardRho(n);
    Deco(p), Deco(n/p);
}

int main() {
    srand(133485);
    int _; scanf("%d", &_);
    while(_--) {
        LL n; scanf("%lld", &n);
        tot = 0;
        Deco(n); sort(deco+1, deco+1+tot);
        if(tot == 1) puts("Prime");
        else printf("%lld\n", deco[1]);
    }
    return 0;
}
