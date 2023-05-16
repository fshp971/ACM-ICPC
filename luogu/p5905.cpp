#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<iostream>
#include<algorithm>
#include<vector>
#include<queue>

typedef long long LL;

using namespace std;

const int maxn = 3000, INF = 1e9;
const LL LLINF = 1e15;

int n, m, ene[maxn+5];
LL dis[maxn+5];
int tot, sta[maxn+5];
vector<pair<int,int>> G[maxn+5];

int main() {
    ios::sync_with_stdio(0);
    cin >> n >> m;
    for(int i = 1, u,v,w; i <= m; ++i) {
        cin >> u >> v >> w;
        G[u].push_back(pair<int,int>(v,w));
    }

    for(int i = 1; i <= n; ++i) ene[i] = 0;
    for(int i = 1; i <= n+1; ++i) {
        int fg = 0;
        for(int k = 1; k <= n; ++k) {
            for(auto it : G[k]) {
                if(ene[it.first] > ene[k] + it.second)
                    ene[it.first] = ene[k] + it.second, fg = 1;
            }
        }
        if(!fg) break;
        if(i == n+1) {
            cout << "-1" << "\n";
            return 0;
        }
    }

    priority_queue<pair<int,int>> q;
    for(int i = 1; i <= n; ++i) {
        for(int k = 1; k <= n; ++k) dis[k] = LLINF;
        dis[i] = 0;
        q.push(pair<int,int>(-0,i));
        while(!q.empty()) {
            pair<int,int> pp = q.top(); q.pop();
            int d = -pp.first, x = pp.second;
            if(dis[x] != d) continue;
            for(auto it : G[x]) {
                if(dis[it.first] > dis[x] + ene[x] - ene[it.first] + it.second) {
                    dis[it.first] = dis[x] + ene[x] - ene[it.first] + it.second;
                    q.push(pair<int,int>(-dis[it.first], it.first));
                }
            }
        }
        LL ans = 0;
        for(int k = 1; k <= n; ++k) {
            if(dis[k] == LLINF) dis[k] = INF;
            else dis[k] = dis[k] - ene[i] + ene[k];
            ans = ans + k * dis[k];
        }
        cout << ans << "\n";
    }
    return 0;
}
