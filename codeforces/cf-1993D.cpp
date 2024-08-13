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
 
const int maxn = 5e5;
 
int n, kk;
vector<int> ai(maxn+5), f(maxn+5);
 
bool check(int x) {
    f[0] = 0;
    REP(i,1,n) {
        int c = (ai[i] >= x ? 1 : -1);
        if((i-1) % kk == 0) {
            f[i] = c;
            if(i > 1) f[i] = max(f[i], f[i-kk]);
        }
        else {
            f[i] = f[i-1] + c;
            if(i >= kk) f[i] = max(f[i], f[i-kk]);
        }
    }
    return f[n] > 0;
}
 
int main() {
    ios::sync_with_stdio(0);
    int _; cin >> _;
    while(_--) {
        cin >> n >> kk;
        REP(i,1,n) cin >> ai[i];
        int ll = 1, rr = 1e9, ans = 0;
        while(ll <= rr) {
            int mid = (ll+rr) >> 1;
            if(check(mid)) ans = mid, ll = mid+1;
            else rr = mid-1;
        }
        cout << ans << "\n";
    }
    return 0;
}
