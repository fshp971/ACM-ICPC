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
 
int main() {
    ios::sync_with_stdio(0);
    int _; cin >> _;
    while(_--) {
        int n, xx; cin >> n >> xx;
        LL ans = 0, sum = 0, avg = 0, mx = 0;
        for(int i = 1, a; i <= n; ++i)
            cin >> a, sum += a, mx = max(mx, LL(a));
        avg = sum / xx;
        if(avg * xx < sum) ++avg;
        ans = max(avg, mx);
        cout << ans << '\n';
    }
    return 0;
}
