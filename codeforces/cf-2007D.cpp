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

const int maxn = 1e5;

int n, one, zero, ud, rtud;
vector<vector<int>> G(maxn+5);
char ss[maxn+5];

void dfs(int x, int p) {
    bool leaf = 1;
    for(auto y : G[x]) if(y != p) {
        leaf = 0;
        dfs(y, x);
    }
    if(leaf) {
        if(ss[x] == '0') ++zero;
        else if(ss[x] == '1') ++one;
        else ++ud;
    }
    else if(ss[x] == '?') ++rtud;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(nullptr);
    int _; cin >> _;
    while(_--) {
        cin >> n;
        one = 0, zero = 0, ud = 0, rtud = 0;
        REP(i,1,n) G[i].clear();
        for(int i = 1, u,v; i < n; ++i) {
            cin >> u >> v;
            G[u].push_back(v);
            G[v].push_back(u);
        }
        cin >> (ss+1);
        dfs(1, 0);
        int ans = -1;
        if(ss[1] != '?') {
            if(ss[1] == '0') ans = one;
            else ans = zero;
            ans += (ud+1) >> 1;
        }
        else {
            --rtud;
            if(one != zero) ans = max(one, zero) + (ud >> 1);
            else {
                if(rtud & 1) ans = one + ((ud+1) >> 1);
                else ans = one + (ud >> 1);
            }
        }
        cout << ans << '\n';
    }
    return 0;
}
