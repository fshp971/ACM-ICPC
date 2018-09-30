// cf上只有弱数据
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
typedef double DB;
typedef pair<int,int> pii;

const int maxn = 50;

DB f[2][maxn+5][maxn+5];

int main() {
    freopen("assessment.in", "r", stdin);
    int __; scanf("%d", &__);
    for(int _ = 1; _ <= __; ++_) {
        int n, x, y, kk;
        DB p, np;
        scanf("%d%lf%d%d%d", &n, &p, &x, &y, &kk);
        if(n == 1) p = np = 0.0;
        else np = p/(n-1);
        int par = 0;
        REP(i,1,n) REP(k,1,n) f[par][i][k] = 0;
        f[par][x+1][y+1] = 1.0;
        while(kk--) {
            REP(i,1,n) REP(k,1,n) f[par^1][i][k] = 0;
            REP(i,1,n) REP(k,1,n) {
                f[par^1][i][k] += f[par][i][k]*(1-p);
                DB prob = f[par][i][k]*np;
                if(i==k) {
                    int tt = 0;
                    if(i+1<=n) f[par^1][i+1][k+1] += prob, ++tt;
                    if(i-1>=1) f[par^1][i-1][k-1] += prob, ++tt;

                    f[par^1][i][k] += prob*(n-1-tt);
                }
                else {
                    int tt = 0;
                    if(i+1<=n) {
                        if(i+1!=k) f[par^1][i+1][k] += prob, ++tt;
                        else f[par^1][i+1][k-1] += prob, ++tt;
                    }
                    if(i-1>=1) {
                        if(i-1!=k) f[par^1][i-1][k] += prob, ++tt;
                        else f[par^1][i-1][k+1] += prob, ++tt;
                    }
                    if(k+1<=n && k+1!=i)
                        f[par^1][i][k+1] += prob, ++tt;
                    if(k-1>=1 && k-1!=i)
                        f[par^1][i][k-1] += prob, ++tt;

                    f[par^1][i][k] += prob*(n-1-tt);
                }
            }
            par ^= 1;
        }
        DB ans = 0;
        printf("Case %d: %.5f\n", _, f[par][y+1][x+1]);
    }
    return 0;
}
