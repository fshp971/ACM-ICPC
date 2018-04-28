#include <bits/stdc++.h>

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

int m, n;

inline LL S2(LL n) {
    if(n&1) return ((n+1)>>1) * n;
    return (n>>1) * (n+1);
}

LL Solve(LL a, LL b, LL l) {
    if(b*l < a) return 0;
    if(b >= a) return (b/a) * S2(l) + Solve(a, b%a, l);
    LL lt = b*l/a;
    return lt * l + min(b*l/a, lt/b) - Solve(b, a, lt);
}

LL Calc(LL a, LL b) {
    LL res = 0;
    LL lx = a*(n-1) / b;
    if(lx < m-1) res += LL(m-1-lx) * (n-1);
    else lx = m-1;
    res += Solve(a, b, lx);
    return res;
}

int main() {
    int T;
    LL c;
    scanf("%d%d%d", &n, &m, &T);
    while(T--) {
        scanf("%lld", &c);
        if(c <= m-1) { printf("%lld %lld\n", 1LL, c+1); continue; }
        if(c > LL(m-1)*n) { printf("%lld %lld\n", c-LL(m-1)*n+1, 1LL); continue; }
        c -= m-1;
        LL q1 = 1, p1 = 0, q2 = 0, p2 = 1;
        while(1) {
            LL on = min( (m-1)/(q1+q2), (n-1)/(p1+p2) );
            LL cnt = Calc(q1+q2, p1+p2);
            if(cnt-on < c && c <= cnt) {
                q1 = q1+q2, p1 = p1+p2;
                c -= cnt-on;
                break;
            }
            if(c <= cnt) q2 = q1+q2, p2 = p1+p2;
            else q1 = q1+q2, p1 = p1+p2;
        }
        printf("%lld %lld\n", p1*c+1, q1*c+1);
    }
    return 0;
}
