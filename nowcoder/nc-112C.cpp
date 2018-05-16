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

int main() {
    LL n, x;
    int T;
    scanf("%lld%d", &n, &T);
    while(T--) {
        scanf("%lld", &x);
        LL ss = 1, del = 1, ans = 0;
        int fg = 0;
        while(1) {
            LL sss = ss + fg * del;
            if(sss > n) {
                ++ans; break;
            }
            ss = ss + (fg^1) * del;
            if((x - sss) % (del<<1) == 0) {
                ans += (x-sss) / (del<<1) + 1;
                break;
            }
            if((n - ans) & 1) fg ^= 1;
            ans += (n-sss) / (del<<1) + 1;
            del <<= 1;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
