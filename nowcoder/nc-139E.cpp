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
const int md = 1e9 + 7;

int n, m, kk, seg[maxn + 5];
LL f[2][15][15];

void Add(LL &a, LL b) { a+=b; if(a>=md) a-=md; }

int main() {
    while(~scanf("%d%d%d", &n, &m, &kk)) {
        REP(i,1,n) scanf("%d", seg + i);
        int par = 0;
        mem(f[par], 0);
        f[par][0][0] = 1;
        for(int i = 1; i <= n; ++i) {
            mem(f[par^1], 0);
            for(int k = 0; k <= m; ++k) {
                for(int j = 0; j <= kk; ++j) {
                    if(k<m && j!=seg[i])
                        Add(f[par^1][k+1][j], f[par][k][j]);
                    Add(f[par^1][k][seg[i]], f[par][k][j]);
                }
            }
            par ^= 1;
        }
        LL ans = 0;
        for(int i = 0; i <= kk; ++i) Add(ans, f[par][m][i]);
        printf("%lld\n", ans);
    }
    return 0;
}
