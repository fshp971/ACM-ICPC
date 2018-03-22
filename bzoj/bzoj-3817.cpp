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

char NC() {
    static char buf[100000], *p1 = NULL, *p2 = NULL;
    if(p1 == p2) { p2 = (p1 = buf) + fread(buf, 1, 100000, stdin); if(p1 == p2) return EOF; }
    return *(p1++);
}

void Read(int &x) {
    char c;
    do { c = NC(); } while(c != EOF && (c<'0' || c>'9'));
    if(c == EOF) return;
    for(x = 0; '0' <= c && c <= '9'; x = x*10 + c - '0', c = NC());
}

LL Gcd(LL a, LL b) { return b ? Gcd(b,a%b) : a; }

LL Solve(LL a, LL b, LL c, LL x, LL n) {
    if(!n) return 0;
    LL g = Gcd(abs(c), Gcd(abs(a), abs(b)));
    a /= g, b /= g, c /= g;
    LL res = 0;
    double T = (a*sqrt(x)+b) / c;
    if(T >= 1) {
        res += ((n*(n+1)) >> 1) * LL(floor(T));
        res += Solve(a, b-LL(floor(T)) * c, c, x, n);
    }
    else {
        res += n * LL(floor(n*T));
        res -= Solve(a*c, -b*c, a*a*x-b*b, x, LL(floor(n*T)));
    }
    return res;
}

int main() {
    int N, R, T;
    Read(T);
    while(T--) {
        Read(N), Read(R);
        int x = sqrt(R);
        if(x*x == R) {
            if(x&1)
                printf("%d\n", (N&1) ? -1 : 0);
            else printf("%d\n", N);
        }
        else {
            LL ans = N + 4 * Solve(1,0,2,R,N) - 2 * Solve(1,0,1,R,N);
            printf("%lld\n", ans);
        }
    }
    return 0;
}
