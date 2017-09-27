#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define PB push_back
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 1e5;

int n;
LL aa[maxn + 5], f[maxn + 5], pp[3];

int main() {
    scanf("%d%lld%lld%lld", &n, pp, pp + 1, pp + 2);
    for(int i = 1; i <= n; ++i) scanf("%lld", aa + i);
    mem(f, 0x80);
    for(int t = 0; t < 3; ++t) {
        LL now = (t == 0) ? 0 : f[1];
        for(int i = 1; i <= n; ++i) {
            now = max(now, f[i]);
            f[i] = now + pp[t] * aa[i];
        }
    }
    for(int i = 1; i <= n; ++i) f[0] = max(f[0], f[i]);
    printf("%lld\n", f[0]);
    return 0;
}
