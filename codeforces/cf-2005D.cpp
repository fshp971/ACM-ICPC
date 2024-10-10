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
        vector<int> ai(n+5, 0), bi(n+5, 0), ssa(n+5, 0), ssb(n+5, 0);
        REP(i,1,n) cin >> ai[i], ssa[i] = gcd(ssa[i-1], ai[i]);
        REP(i,1,n) cin >> bi[i], ssb[i] = gcd(ssb[i-1], bi[i]);
        int fg = 0;
        int mx = 0;
        LL sum = 0;
        map<pair<int,int>, int> mp[2];
        mp[0][pair<int,int>(bi[n],ai[n])] = 1;
        for(int i = n-1, ta = ai[n], tb = bi[n]; i >= 0; --i) {
            mp[fg^1].clear();
            mp[fg^1][pair<int,int>(gcd(bi[i], ta), gcd(ai[i], tb))] = 1;
            ta = gcd(ta, ai[i]);
            tb = gcd(tb, bi[i]);
            for(auto it : mp[fg]) {
                if(it.first.first + it.first.second < mx) continue;
                int g1 = gcd(ssa[i], it.first.first);
                int g2 = gcd(ssb[i], it.first.second);
                if(g1+g2 > mx) mx = g1+g2, sum = it.second;
                else if(g1+g2 == mx) sum += it.second;
                pair<int,int> pp = {gcd(bi[i], it.first.first), gcd(ai[i], it.first.second)};
                if(mp[fg^1].find(pp) == mp[fg^1].end()) mp[fg^1][pp] = it.second;
                else mp[fg^1][pp] += it.second;
            }
            fg ^= 1;
        }
        cout << mx << ' ' << sum << '\n';
    }
    return 0;
}
