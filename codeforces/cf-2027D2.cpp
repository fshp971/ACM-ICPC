#include<bits/stdc++.h>
 
using namespace std;
typedef long long LL;
 
int main() {
    ios::sync_with_stdio(0);
    const LL INF = 1e16;
    const int P = 1e9 + 7;
    auto Add = [&](int &a, int b) { a += b; if(a >= P) a -= P; };
    auto Sub = [&](int &a, int b) { a -= b; if(a < 0) a += P; };
    int _; cin >> _;
    while(_--) {
        int n, m; cin >> n >> m;
        vector<LL> ai(n+5, 0);
        vector<int> bi(m+5);
        for(int i = 1; i <= n; ++i) cin >> ai[i], ai[i] += ai[i-1];
        for(int i = 1; i <= m; ++i) cin >> bi[i];
 
        vector<pair<LL,int>> f(n+5, pair<LL,int>(INF, 0));
        f[0] = pair<LL,int>(0, 1);
 
        for(int k = 1; k <= m; ++k) {
            int j = 0, l = 1, c = f[0].second;
            for(int i = 1; i <= n; ++i) {
                while(j < i && ai[i] - ai[j] > bi[k])
                    Sub(c, f[j].second), ++j;
 
                if(l < j)
                    l = j, c = 0;
 
                while(l < i && f[j].first == f[l].first)
                    Add(c, f[l].second), ++l;
 
                if(j < i) {
                    if(f[j].first + (m-k) < f[i].first)
                        f[i].first = f[j].first + (m-k), f[i].second = c;
                    else if(f[j].first + (m-k) == f[i].first)
                        Add(f[i].second, c);
                }
 
                while(l <= i && f[j].first == f[l].first)
                    Add(c, f[l].second), ++l;
            }
        }
        if(f[n].first == INF)
            cout << "-1\n";
        else
            cout << f[n].first << ' ' << f[n].second << '\n';
    }
    return 0;
}
