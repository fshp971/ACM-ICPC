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
typedef long double LD;

const int maxn = 500, maxm = 100*2;
const int INF = 2e9;

int n, m, tn;
int ti[maxn+5], f[2][maxm+5], g[maxm+5];

int main() {
    ios::sync_with_stdio(0);
    cin >> n >> m;
    REP(i,1,n) cin >> ti[i];
    sort(ti+1, ti+1+n);
    int fg = 0, len = m*2;
    REP(i,1,n) {
        REP(k,0,len) f[fg^1][k] = INF;
        REP(k,0,len) if(ti[i] <= ti[i-1]+k) {
            int dk = ti[i-1]+k - ti[i];
            f[fg^1][dk] = min(f[fg^1][dk], f[fg][k] + dk);
        }
        g[0] = f[fg][0];
        REP(k,1,len) g[k] = min(g[k-1], f[fg][k]);
        REP(k,0,len) {
            int dk = (ti[i]-ti[i-1]) + (k-m);
            if(dk < 0) continue;
            dk = min(dk, len);
            f[fg^1][k] = min(f[fg^1][k], g[dk]+k);
        }
        fg ^= 1;
    }
    int ans = INF;
    REP(k,0,len) ans = min(ans, f[fg][k]);
    cout << ans << "\n";
    return 0;
}
