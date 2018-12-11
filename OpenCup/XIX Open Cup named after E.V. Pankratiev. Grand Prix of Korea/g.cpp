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
typedef pair<int,int> pii;

const int maxn = 250000;

int n, kk;
int wi[maxn+5];
LL f[2][10][19][3];
// 0: has been light;
// 1: no light;
// 2: is light.

inline void Min(LL &a, LL b) { a = min(a,b); }

int main() {
    scanf("%d%d", &n, &kk);
    REP(i,1,n) scanf("%d", wi+i);
    int par = 0;
    mem(f[par], 0x7f);
    f[par][0][0+kk][0] = 0;
    for(int i = 1; i <= n; ++i) {
        mem(f[par^1], 0x7f);
        REP(k,0,kk) REP(j,-kk,kk) {
            Min(f[par^1][k][j+kk][1], f[par][k][j+kk][0]);
            Min(f[par^1][k][j+kk][2], f[par][k][j+kk][0]+wi[i]);
            Min(f[par^1][k][j+kk][2], f[par][k][j+kk][1]+wi[i]);
            Min(f[par^1][k][j+kk][0], f[par][k][j+kk][2]);
            Min(f[par^1][k][j+kk][2], f[par][k][j+kk][2]+wi[i]);

            if(j>-kk) {
                Min(f[par^1][k][j-1+kk][2], f[par][k][j+kk][0]);
                Min(f[par^1][k][j-1+kk][2], f[par][k][j+kk][1]);
                Min(f[par^1][k][j-1+kk][2], f[par][k][j+kk][2]);
            }
            if(k<kk && j<kk) {
                Min(f[par^1][k+1][j+1+kk][1], f[par][k][j+kk][0]+wi[i]);
                Min(f[par^1][k+1][j+1+kk][0], f[par][k][j+kk][2]+wi[i]);
            }
        }
        par^=1;
    }
    LL ans = 1LL<<60;
    REP(k,0,kk) {
        Min(ans, f[par][k][0+kk][0]);
        Min(ans, f[par][k][0+kk][2]);
    }
    printf("%lld\n", ans);
    return 0;
}
