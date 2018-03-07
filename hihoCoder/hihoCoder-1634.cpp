#include<bits/stdc++.h>

using namespace std;

#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define FOR(i,a,b) for(int i = a; i < b; ++i)
#define mem(a,b) memset(a,b,sizeof(a))
#define MP make_pair
#define PB push_back
#define fi first
#define se second
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 150;
const int INF = 150*150*1000;

int n, m, P;
int mmp[maxn + 5][maxn + 5];
int sv[maxn + 5][maxn + 5], sh[maxn + 5][maxn + 5];
int L[maxn + 5], R[maxn + 5], U[maxn + 5], D[maxn + 5];

int main() {
    while(~scanf("%d%d%d", &n, &m, &P)) {
        REP(i,1,n) REP(k,1,m) scanf("%d", &mmp[i][k]);
        for(int i = 1; i <= n; ++i)
            for(int k = 1; k <= m; ++k) {
                sv[i][k] = mmp[i][k] + sv[i-1][k];
                sh[i][k] = mmp[i][k] + sh[i][k-1];
            }
        for(int i = 1; i <= m; ++i) L[i] = R[i] = -INF;
        for(int i = 1; i <= n; ++i) U[i] = D[i] = -INF;
        int ans = -INF;
        for(int i = 1; i <= n; ++i)
            for(int k = i; k <= n; ++k) {
                int tmp = 0;
                for(int j = 1; j <= m; ++j) {
                    tmp += sv[k][j] - sv[i-1][j];
                    ans = max(ans, tmp);
                    L[j] = max(L[j], tmp);
                    if(tmp < 0) tmp = 0;
                }
                tmp = 0;
                for(int j = m; j >= 1; --j) {
                    tmp += sv[k][j] - sv[i-1][j];
                    R[j] = max(R[j], tmp);
                    if(tmp < 0) tmp = 0;
                }
            }
        for(int i = 1; i <= m; ++i)
            for(int k = i; k <= m; ++k) {
                int tmp = 0;
                for(int j = 1; j <= n; ++j) {
                    tmp += sh[j][k] - sh[j][i-1];
                    U[j] = max(U[j], tmp);
                    if(tmp < 0) tmp = 0;
                }
                tmp = 0;
                for(int j = n; j >= 1; --j) {
                    tmp += sh[j][k] - sh[j][i-1];
                    D[j] = max(D[j], tmp);
                    if(tmp < 0) tmp = 0;
                }
            }
        for(int i = 2; i <= m; ++i) L[i] = max(L[i], L[i-1]);
        for(int i = m-1; i >= 1; --i) R[i] = max(R[i], R[i+1]);
        for(int i = 2; i <= n; ++i) U[i] = max(U[i], U[i-1]);
        for(int i = n-1; i >= 1; --i) D[i] = max(D[i], D[i+1]);
        int mx = ans;
        for(int i = 1; i <= n; ++i)
            for(int k = 1; k <= m; ++k) {
                int tmp = mx - mmp[i][k] + P;
                if(k>1) tmp = max(tmp, L[k-1]);
                if(k<m) tmp = max(tmp, R[k+1]);
                if(i>1) tmp = max(tmp, U[i-1]);
                if(i<n) tmp = max(tmp, D[i+1]);
                ans = min(ans, tmp);
            }
        printf("%d\n", ans);
    }
    return 0;
}
