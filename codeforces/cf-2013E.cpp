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
 
int gcd(int a, int b) { return b ? gcd(b, a%b) : a; }
 
int main() {
    ios::sync_with_stdio(0);
    int _; cin >> _;
    while(_--) {
        int n; cin >> n;
        vector<int> ai(n+5), vis(n+5, 0);
        int g = 0;
        REP(i,1,n) cin >> ai[i], g = gcd(g, ai[i]);
        REP(i,1,n) ai[i] /= g;
        LL ans = 0;
        for(int i = 1, ng = 0; i <= n; ++i) {
            int tg = 1e9, ps = 0;
            REP(k,1,n) if(!vis[k]) {
                int tmp = gcd(ng, ai[k]);
                if(tmp < tg) tg = tmp, ps = k;
            }
            ng = tg, vis[ps] = 1;
            ans += ng;
            if(ng == 1) { ans += n-i; break; }
        }
        ans *= g;
        cout << ans << '\n';
    }
    return 0;
}
