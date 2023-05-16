#include<cmath>
#include<iostream>
#include<iomanip>
#include<algorithm>

using namespace std;

const int maxn = 1e4, maxm = 1e3, INF = 1e9;

int n, m, kk, f[2][maxm+5];
int xx[maxn+5], yy[maxn+5];
int ll[maxn+5], hh[maxn+5], cc[maxn+5];

int main() {
    ios::sync_with_stdio(0);
    cin >> n >> m >> kk;
    for(int i = 0; i <= n-1; ++i)
        cin >> xx[i] >> yy[i];
    for(int i = 0; i <= n; ++i)
        ll[i] = 1, hh[i] = m;
    for(int i = 1, p,l,h; i <= kk; ++i) {
        cin >> p >> l >> h;
        ll[p] = l+1, hh[p] = h-1, cc[p] = 1;
    }
    int fg = 0, cnt = 0;
    for(int i = 1; i <= n; ++i) {
        for(int k = 1; k <= m; ++k) f[fg^1][k] = INF;
        for(int k = ll[i-1]; k <= hh[i-1]; ++k) {
            int p = min(k+xx[i-1], m);
            f[fg^1][p] = min(f[fg^1][p], f[fg][k]+1);
        }
        for(int k = 1; k <= m; ++k) {
            int p = min(k+xx[i-1], m);
            f[fg^1][p] = min(f[fg^1][p], f[fg^1][k]+1);
        }
        for(int k = 1; k <= ll[i]-1; ++k) f[fg^1][k] = INF;
        for(int k = hh[i]+1; k <= m; ++k) f[fg^1][k] = INF;
        for(int k = ll[i-1]; k <= hh[i-1]; ++k) {
            int p = k-yy[i-1];
            if(ll[i]<=p && p<=hh[i])
                f[fg^1][p] = min(f[fg^1][p], f[fg][k]);
        }
        fg ^= 1;
        int ok = 0;
        for(int k = ll[i]; k <= hh[i] && !ok; ++k) ok |= (f[fg][k] < INF);
        if(!ok) {
            cout << "0\n" << cnt << "\n";
            return 0;
        }
        cnt += cc[i];
    }
    int ans = INF;
    for(int i = ll[n]; i <= hh[n]; ++i) ans = min(ans, f[fg][i]);
    cout << "1\n" << ans << "\n";
    return 0;
}
