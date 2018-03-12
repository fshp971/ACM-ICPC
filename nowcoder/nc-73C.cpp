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

const int maxn = 15, maxk = 1<<15;
const int md = 1e9 + 7;

int n, m, kk;
int xx[maxn*2 + 5], yy[maxn*2 + 5], mmp[maxn + 5][maxn + 5];
int f[maxn + 5][maxn + 5][maxk + 5];

inline void Add(int &a, int b) { a += b; if(a>=md) a -= md; }

int main() {
    scanf("%d%d%d", &n, &m, &kk);
    REP(i,1,n) REP(k,1,m) scanf("%d", mmp[i] + k), mmp[i][k] ^= 1, mmp[i][k] += mmp[i][k-1];
    REP(i,1,kk) scanf("%d%d", xx + i, yy + i);
    f[0][m][(1<<m)-1] = 1;
    for(int i = 1; i <= n; ++i) {
        memcpy(f[i][0], f[i-1][m], (1<<m) * sizeof(LL));
        for(int k = 1; k <= m; ++k) {
            for(int j = 0; j < (1<<m); ++j) {
                int msk = (j | (1<<(k-1))) ^ (1<<(k-1));
                if(mmp[i][k] - mmp[i][k-1]) msk |= 1<<(k-1);
                Add(f[i][k][msk], f[i][k-1][j]);
            }
            if(mmp[i][k] - mmp[i][k-1]) continue;
            for(int t = 1; t <= kk; ++t) {
                if(yy[t] > k) continue;
                if(mmp[i][k] - mmp[i][k-yy[t]]) continue;
                int msk = ((1<<yy[t])-1) << (k-yy[t]);
                if(xx[t] == 1) {
                    for(int j = 0; j < (1<<m); ++j)
                        Add(f[i][k][j|msk], f[i][k-yy[t]][j]);
                }
                else {
                    if(i < 2 || mmp[i-1][k] - mmp[i-1][k-yy[t]]) continue;
                    int mk2 = ((1<<m)-1) ^ msk;
                    for(int j = mk2; j > 0; j = (j-1) & mk2)
                        Add(f[i][k][j|msk], f[i][k-yy[t]][j]);
                    Add(f[i][k][msk], f[i][k-yy[t]][0]);
                }
            }
        }
    }
    int ans = 0;
    for(int i = 0; i < (1<<m); ++i) Add(ans, f[n][m][i]);
    printf("%d\n", ans);
    return 0;
}
