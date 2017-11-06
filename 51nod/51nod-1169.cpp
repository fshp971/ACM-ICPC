//#include<cstdio>
#include<stdio.h>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
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

const int maxn = 100, md = 1e9 + 7;

int n, aa[maxn + 5];
LL f[maxn + 5][2];

LL Run() {
    LL ans = 0;
    for(int i = 30; i >= 0; --i) {
        f[n + 1][0] = 1, f[n + 1][1] = 0;
        for(int k = n; k >= 1; --k) {
            if(aa[k] >> i & 1) {
                f[k][0] = (f[k+1][1] * (aa[k]%(1<<i)+1) % md + f[k+1][0] * (1<<i) % md) % md;
                f[k][1] = (f[k+1][0] * (aa[k]%(1<<i)+1) % md + f[k+1][1] * (1<<i) % md) % md;
            }
            else {
                f[k][0] = f[k+1][0] * (aa[k]%(1<<i)+1) % md;
                f[k][1] = f[k+1][1] * (aa[k]%(1<<i)+1) % md;
            }
        }
        int fg = 0;
        LL pre = 1;
        for(int k = 1; k <= n; ++k) {
            if(aa[k] >> i & 1) {
                ans = (ans + f[k+1][fg] * pre % md) % md;
                fg ^= 1;
            }
            pre = pre * (aa[k] % (1<<i) + 1) % md;
        }
        if(fg) break;
    }
    int tmp = 0;
    REP(i,1,n) tmp ^= aa[i];
    if(!tmp) ans = (ans + 1) % md;
    return ans;
}

int main() {
    scanf("%d", &n);
    REP(i,1,n) scanf("%d", aa + i);
    LL ans = Run();
    REP(i,1,n) --aa[i];
    ans = (ans - Run() + md) % md;
    printf("%lld\n", ans);
    return 0;
}
