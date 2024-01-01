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

const int maxn = 2000, maxk = 1e5;

int n, kk, dd;
int aa[maxn+5], vv[maxk+5];

int run() {
    int lim = min(n<<1, dd);
    int ans = 0, pt = 0;
    for(int i = 1; i <= lim; ++i) {
        int tmp = 0;
        for(int k = 1; k <= n; ++k) tmp += (aa[k]==k);
        tmp += (dd - i) >> 1;
        ans = max(ans, tmp);
        ++pt;
        if(pt > kk) pt = 1;
        for(int k = 1; k <= vv[pt]; ++k) ++aa[k];
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(0);
    int _; cin >> _;
    while(_--) {
        cin >> n >> kk >> dd;
        REP(i,1,n) cin >> aa[i];
        REP(i,1,kk) cin >> vv[i];
        cout << run() << '\n';
    }
    return 0;
}
