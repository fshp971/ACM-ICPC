#include<bits/stdc++.h>

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

const int maxn = 50;

int md;
inline void Upd(int &a, int b) { a += b; if(a >= md) a -= md; }

int f[2][maxn + 5][maxn + 5], ans[maxn*maxn + 5];

int main() {
    int T, n, m, par;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d%d", &n, &m, &md);
        par = 0;
        REP(i,0,n) REP(k,0,n) f[par][i][k] = 0;
        f[par][0][n] = 1;
        for(int j = 1; j <= m; ++j) {
            par ^= 1;
            REP(i,0,n) REP(k,0,n) f[par][i][k] = 0;
            REP(i,0,n) REP(k,0,n) {
                if(!f[par^1][i][k]) continue;
                for(int t = 1; t <= i; ++t) Upd(f[par][i-t][k-t], f[par^1][i][k]);
                int tmp_sum = (n-k+1)*(n-k) + (n-k+1)*i + i*(i-1)/2;
                if(i+1 < k) Upd(f[par][i+1][k], f[par^1][i][k]);
                else if(j <= tmp_sum) Upd(f[par][i][k], f[par^1][i][k]);
            }
            ans[j] = 0;
            REP(i,0,n) REP(k,0,n) Upd(ans[j], f[par][i][k]);
        }
        for(int i = 1; i <= m; ++i) {
            if(i > 1) printf(" ");
            printf("%d", ans[i]);
        }
        printf("\n");
    }
    return 0;
}
