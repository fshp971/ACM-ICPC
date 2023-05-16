#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define PER(i,a,b) for(int i = a; i >= b; --i)
#define PB push_back
#define MP make_pair
#define fi first
#define se second
typedef long long LL;
typedef double DB;

const int maxn = 100;
const int maxM = 2000;
const int P = 998244353;

int n, m;
int ai[maxn+5][maxM+5], S[maxn+5];
int f[maxM+5][maxn+5][maxn*2+5];

void Add(int &a, int b) { a+=b; if(a>=P) a-=P; }

int main() {
    scanf("%d%d", &n, &m);
    REP(i,1,n) REP(k,1,m)
        scanf("%d", ai[i]+k), Add(S[i], ai[i][k]);
    int sum = 0;
    for(int i = 1; i <= m; ++i) {
        f[i][0][0+maxn] = 1;
        for(int k = 1; k <= n; ++k) {
            for(int d = maxn-k; d <= maxn+k; ++d) {
                f[i][k][d] = f[i][k-1][d];
                if(d-1>=0) Add(f[i][k][d], f[i][k-1][d-1] * LL(ai[k][i]) % P);
                if(d+1<=maxn*2) Add(f[i][k][d], f[i][k-1][d+1] * (LL(S[k])-ai[k][i]+P) % P);
            }
        }
        for(int d = maxn+1; d <= maxn+n; ++d) Add(sum, f[i][n][d]);
    }
    int ans = P-1;
    for(int d = maxn-n; d <= maxn+n; ++d) Add(ans, f[1][n][d]);
    ans = (LL(ans) - sum + P) % P;
    printf("%d\n", ans);
    return 0;
}
