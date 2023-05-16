#include<iostream>
#include<algorithm>
#include<queue>

using namespace std;
typedef long long LL;

const int maxn = 2000;

int n, m, T = 0, vis[maxn+5];
int go[maxn+5][maxn+5], deg[maxn+5], cnt[maxn+5];

int main() {
    ios::sync_with_stdio(0);
    cin >> n >> m;
    for(int i = 1; i <= m; ++i) {
        ++T;
        int s, l, r; cin >> s;
        for(int k = 1, a; k <= s; ++k) {
            cin >> a, vis[a] = T;
            if(k == 1) l = a;
            if(k == s) r = a;
        }
        for(int k = l; k <= r; ++k) {
            if(vis[k] == T) go[k][n+i] = 1, ++deg[n+i];
            else go[n+i][k] = 1, ++deg[k];
        }
    }
    queue<int> q;
    for(int i = 1; i <= n+m; ++i)
        if(!deg[i]) q.push(i);
    while(!q.empty()) {
        int x = q.front(); q.pop();
        if(x <= n) ++cnt[x];
        for(int i = 1; i <= n+m; ++i) if(go[x][i]) {
            --deg[i], cnt[i] = max(cnt[i], cnt[x]);
            if(!deg[i]) q.push(i);
        }
    }
    int ans = 0;
    for(int i = 1; i <= n+m; ++i) ans = max(ans, cnt[i]);
    cout << ans << "\n";
    return 0;
}
