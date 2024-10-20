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
    const int P = 998244353;
    auto Add = [&](int &a, int b) -> void { a+=b; if(a>=P) a-=P; };
    int n, m; cin >> n >> m;
 
    int fg1 = 0;
    vector<vector<int>> g(2, vector<int>(m+5, 0));
    g[fg1][0] = 1;
    for(int i = 1; i <= m; ++i) {
        REP(k,0,i) g[fg1^1][k] = 0;
        for(int k = 0; k <= i-1; ++k) {
            if(k) Add(g[fg1^1][k-1], g[fg1][k]);
            Add(g[fg1^1][k+1], g[fg1][k]);
        }
        fg1 ^= 1;
    }
 
    int hf = m>>1, fg2 = 0;
    vector<vector<int>> f(2, vector<int>(hf+5, 0));
    f[fg2][0] = 1;
    for(int i = 2; i <= n; ++i) {
        REP(k,0,hf) f[fg2^1][k] = 0;
        REP(k,0,hf) {
            REP(j,0,hf-k)
                Add(f[fg2^1][j+k], LL(f[fg2][j]) * g[fg1][k<<1] % P);
        }
        fg2 ^= 1;
    }
    int ans = 0;
    REP(k,0,hf) Add(ans, f[fg2][k] * 1LL * g[fg1][k<<1] % P);
    cout << ans << '\n';
    return 0;
}
