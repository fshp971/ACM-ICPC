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

const int maxn = 2e5;

int n;
LL ww;
vector<vector<int>> G(maxn+5);
vector<vector<int>> f(maxn+5, vector<int>(2));
vector<int> cnt(maxn+5);

void dfs(int x, int p, int &c) {
    ++c;
    for(auto y : G[x]) {
        f[y][0] = c;
        ++cnt[c];
        dfs(y, x, c);
        f[y][1] = c;
        ++cnt[c];
    }
}

int main() {
    ios::sync_with_stdio(0);
    int _; cin >> _;
    while(_--) {
        cin >> n >> ww;
        for(int i = 1; i <= n; ++i) G[i].clear(), cnt[i] = 0;
        for(int i = 2, p; i <= n; ++i)
            cin >> p, G[p].push_back(i);
        int cc = 0, tot = n;
        LL sum = 0;
        dfs(1, 0, cc);
        for(int i = 1; i <= n-1; ++i) {
            int x;
            LL y;
            cin >> x >> y;
            sum += y;
            for(auto v : f[x]) {
                --cnt[v];
                if(cnt[v] == 0) --tot;
            }
            LL ans = ww * tot + sum * (2 - tot);
            cout << ans << ((i==n-1) ? '\n' : ' ');
        }
    }
    return 0;
}
