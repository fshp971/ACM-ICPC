// ans = 2129970655314432
// hint: lucas's theorem, DP
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
#define PER(i,a,b) for(int i=a; i>=b; --i)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
typedef long long LL;

const int LEN = 20;

int num[LEN+5];
LL f[LEN+5][2];
bool vi[LEN+5][2];

LL dfs(int pt, bool fg) {
    if(vi[pt][fg]) return f[pt][fg];
    vi[pt][fg] = 1;
    if(pt==0) return f[pt][fg] = 1;
    LL res = 0;
    int lim = fg ? num[pt] : 6;
    for(int i = 0; i <= lim; ++i)
        res += dfs(pt-1, fg&&(i==lim)) * (i+1);
    return f[pt][fg] = res;
}

LL Calc(int n) {
    int tot = 0;
    while(n) num[++tot] = n%7, n/=7;
    return dfs(tot,1);
}

namespace BF {
    const int maxn = 1000;
    int C[maxn+5][maxn+5];
    void BF(int n) {
        LL ans = 1;
        C[0][0] = 1;
        REP(i,1,n) {
            C[i][0] = C[i][i] = 1;
            ans += 2;
            REP(k,1,i-1) {
                C[i][k] = (C[i-1][k]+C[i-1][k-1]) % 7;
                ans += (C[i][k]!=0);
            }
        }
        printf("ans = %lld\n", ans);
    }
};

int main() {
    int n = int(1e9)-1;
    //int n = 1000;
    printf("%lld\n", Calc(n));
    //BF::BF(n);
    return 0;
}
