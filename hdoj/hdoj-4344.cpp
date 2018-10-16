#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<cassert>
#include<iostream>
#include<algorithm>

using namespace std;

typedef long long LL;

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

const int MaxTry = 30;

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

int tot;
LL deco[100];

void PollardRho(LL n) {
    if(n == 1) return;
    if(MillerRabin(n)) { deco[++tot] = n; return; }
    while(1) {
        LL c = rand() % (n-1) + 1;
        LL x = rand() % n;
        LL y = (MulMod(x,x,n)+c) % n;
        while(x != y) {
            LL d = Gcd(abs(x-y), n);
            if(d != 1) {
                PollardRho(d);
                PollardRho(n/d);
                return;
            }
            x = (MulMod(x,x,n)+c) % n;
            y = (MulMod(y,y,n)+c) % n;
            y = (MulMod(y,y,n)+c) % n;
        }
    }
}

int main() {
    srand(time(NULL));
    int _; scanf("%d", &_);
    while(_--) {
        LL n; scanf("%lld", &n);
        tot = 0;
        PollardRho(n);
        sort(deco+1, deco+1+tot);
        int kk = 0;
        LL sum = 0;
        for(int i = 1; i <= tot; ++i) {
            LL now = deco[i];
            while(i+1<=tot && deco[i]==deco[i+1]) now*=deco[++i];
            if(now == n) now /= deco[i];
            if(now > 1) ++kk, sum += now;
        }
        printf("%d %lld\n", kk, sum);
    }
    return 0;
}
