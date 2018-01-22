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

const int maxn = 1 << 6, maxm = 180;

int n, m;
double pp[maxn + 5][maxm + 5], f[maxn + 5][maxm + 5];

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= n; ++i)
        for(int k = 1; k <= m; ++k)
            scanf("%lf", &pp[i][k]);
    for(int i = 0; i < (1 << n); ++i) {
        for(int k = 1; k <= m; ++k) {
            for(int j = 0; j < n; ++j)
                if(i >> j & 1) {
                    double tmp = 0;
                    fo(int t = 1; t <= k; ++t)
                        tmp += (f[i^(1<<j)][k-t] + 1.0) * pp[j+1][t];
                    f[i][k] = max(f[i][k], tmp);
                }
        }
    }
    printf("%.5f\n", f[(1<<n)-1][m]);
    return 0;
}
