#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 1 << 6;

int mmp[maxn + 5][maxn + 5];
double f[maxn + 5][maxn + 5], g[maxn + 5][maxn + 5];

void dfs(int ii, int l, int r, int val) {
    if(l == r) { g[ii][l] = 1; return; }
    int mid = (l + r) >> 1;
    dfs(ii - 1, l, mid, val >> 1);
    dfs(ii - 1, mid + 1, r, val >> 1);
    for(int i = l; i <= mid; ++i) {
        for(int k = mid + 1; k <= r; ++k)
            g[ii][i] += mmp[i][k] / 100.0 * g[ii-1][k];
        g[ii][i] *= g[ii-1][i];
        for(int k = mid + 1; k <= r; ++k)
            f[ii][i] = max(f[ii][i], f[ii-1][i] + f[ii-1][k] + g[ii][i] * val);
    }
    for(int i = mid + 1; i <= r; ++i) {
        for(int k = l; k <= mid; ++k)
            g[ii][i] += mmp[i][k] / 100.0 * g[ii-1][k];
        g[ii][i] *= g[ii-1][i];
        for(int k = l; k <= mid; ++k)
            f[ii][i] = max(f[ii][i], f[ii-1][i] + f[ii-1][k] + g[ii][i] * val);
    }
}

int main() {
    int n, m;
    scanf("%d", &m);
    n = 1 << m;
    for(int i = 1; i <= n; ++i)
        for(int k = 1; k <= n; ++k)
            scanf("%d", &mmp[i][k]);
    dfs(m, 1, n, n >> 1);
    double ans = 0;
    for(int i = 1; i <= n; ++i)
        ans = max(ans, f[m][i]);
    printf("%.14f\n", ans);
	return 0;
}
