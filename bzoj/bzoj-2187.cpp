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

LL Gcd(LL a, LL b) { return b ? Gcd(b, a%b) : a; }

void Solve(LL a, LL b, LL c, LL d, LL &p, LL &q) {
    if((a/b + 1) * d < c) {
        p = a/b + 1, q = 1;
        return;
    }
    if(a == 0) { p = 1, q = d/c + 1; return; }
    if(a >= b) {
        LL t = a/b;
        Solve(a%b, b, c - d*t, d, p, q);
        p += q*t;
        return;
    }
    Solve(d, c, b, a, q, p);
}

int main() {
    LL a, b, c, d, g, p, q;
    while(~scanf("%lld%lld%lld%lld", &a, &b, &c, &d)) {
        g = Gcd(a,b), a/=g, b/=g;
        g = Gcd(c,d), c/=g, d/=g;
        Solve(a, b, c, d, p, q);
        printf("%lld/%lld\n", p, q);
    }
    return 0;
}
