#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define PB push_back
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 2500, maxm = 1e5, md = 1e9 + 7;

int seg[maxn + 5];
LL f[maxm + 5];

LL PowMod(LL a, LL b) {
    LL res = 1;
    while(b) {
        if(b & 1) res = res * a % md;
        a = a * a % md, b >>= 1;
    }
    return res;
}

int main() {
    int n, u, m = 0, mx = 0;
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
        scanf("%d", seg + i), m += seg[i], mx = max(mx, seg[i]);
    f[0] = 0, f[1] = LL(m-1) * (m-1) % md * PowMod(m, md-2) % md;
    for(int i = 2; i <= mx; ++i)
        f[i] = (f[i-1] * 2 % md - f[i-2] - LL(m-1) * PowMod(m-i+1, md-2) % md + md * 2LL) % md;
    LL ans = 0;
    for(int i = 1; i <= n; ++i)
        ans = (ans + f[seg[i]]) % md;
    printf("%lld\n", ans);
    return 0;
}
