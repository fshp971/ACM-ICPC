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
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 1e5;
const LL INF = 1LL << 30;

inline LL PowMod(LL a, LL b, LL P) { a%=P; LL r=1; while(b) { if(b&1) r=r*a%P; a=a*a%P; b>>=1; } return r; }

inline LL PowMax(LL a, LL b) {
    LL r=1;
    while(b) {
        if(b&1) r = min(r*a, INF);
        a = min(a*a, INF), b >>= 1;
    }
    return r;
}

LL GetPhi(int n) {
    LL res = n, a = n;
    for(int i = 2; i*i <= a; ++i) {
        if(a%i == 0) {
            res = res / i * (i-1);
            while(a%i == 0) a /= i;
        }
    }
    if(a > 1) res = res / a * (a-1);
    return res;
}
int phi[maxn + 5];

int n, mod[maxn + 5];
char str[maxn + 5];

int main() {
    phi[0] = 1e9 + 7;
    for(int i = 1; i <= maxn; ++i) {
        phi[i] = GetPhi(phi[i-1]);
    }
    int T; scanf("%d", &T);
    while(T--) {
        scanf("%s", str + 1), n = strlen(str+1);
        mod[n] = 0;
        for(int i = n-1; i >= 0; --i)
            mod[i] = mod[i+1] + (str[i+1] == '2');
        for(int i = 0; i <= n; ++i) mod[i] = phi[ mod[i] ];
        LL ans = 0, sum = 0;
        for(int i = 1; i <= n; ++i) {
            if(str[i] == '0') {
                ans = (ans + 1) % mod[i];
                sum = min(sum+1, INF);
            }
            else if(str[i] == '1') {
                ans = (ans + 1) * 2LL % mod[i];
                sum = min((sum+1)*2LL, INF);
            }
            else {
                ans = (6LL * PowMod(2LL, ans + (sum>=mod[i-1] ? mod[i-1] : 0), mod[i]) - 3LL + mod[i]) % mod[i];
                sum = min( 6LL * PowMax(2, sum) - 3LL, INF );
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
