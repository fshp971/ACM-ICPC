#include<iostream>
#include<queue>
#include<utility>

using namespace std;

const int INF = 1e9;
const int walk[4][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};

int n, m, mp[35][35];
int dis[4][35][35][35][35], dis2[4][35][35];

void bfs(int sd, int sx, int sy) {
    queue<pair<int,int>> q;
    for(int i = 1; i <= n; ++i)
        for(int k = 1; k <= m; ++k)
            dis[sd][sx][sy][i][k] = INF;

    int xx = sx + walk[sd][0];
    int yy = sy + walk[sd][1];
    if(xx<1 || xx>n || yy<1 || yy>m || !mp[xx][yy])
        return;

    dis[sd][sx][sy][xx][yy] = 0;
    q.push(pair<int,int>(xx, yy));
    while(!q.empty()) {
        pair<int,int> pp = q.front();
        q.pop();
        int &x = pp.first, &y = pp.second;
        for(int i = 0; i < 4; ++i) {
            xx = x + walk[i][0];
            yy = y + walk[i][1];
            if(xx<1 || xx>n || yy<1 || yy>m || !mp[xx][yy])
                continue;
            if(dis[sd][sx][sy][x][y]+1 < dis[sd][sx][sy][xx][yy]) {
                dis[sd][sx][sy][xx][yy] = dis[sd][sx][sy][x][y]+1;
                q.push(pair<int,int>(xx, yy));
            }
        }
    }
}

int dij(int sd, int sx, int sy, int tx, int ty) {
    for(int d = 0; d < 4; ++d)
        for(int i = 1; i <= n; ++i)
            for(int k = 1; k <= m; ++k)
                dis2[d][i][k] = INF;
    priority_queue<pair<int,int>> q;
    dis2[sd][sx][sy] = 0;
    q.push(pair<int,int>(-0, (sd<<10) + (sx<<5) + sy));
    while(!q.empty()) {
        pair<int,int> pp = q.top(); q.pop();
        int l = -pp.first;
        int d = pp.second >> 10;
        int x = (pp.second >> 5) - (d << 5);
        int y = pp.second - (d << 10) - (x << 5);
        if(dis2[d][x][y] != l) continue;

        int xx = x + walk[d][0];
        int yy = y + walk[d][1];
        if(l+1 < dis2[d^1][xx][yy]) {
            dis2[d^1][xx][yy] = l+1;
            q.push(pair<int,int>(-dis2[d^1][xx][yy], ((d^1)<<10)+(xx<<5)+yy));
        }

        for(int i = 0; i < 4; ++i) {
            if(l + dis[i][x][y][xx][yy] < dis2[i][x][y]) {
                dis2[i][x][y] = l + dis[i][x][y][xx][yy];
                q.push(pair<int,int>(-dis2[i][x][y], (i<<10)+(x<<5)+y));
            }
        }
    }
    int res = INF;
    for(int i = 0; i < 4; ++i)
        res = min(res, dis2[i][tx][ty]);
    return res;
}

int main() {
    ios::sync_with_stdio(0);
    int _;
    cin >> n >> m >> _;
    for(int i = 1; i <= n; ++i)
        for(int k = 1; k <= m; ++k)
            cin >> mp[i][k];

    for(int i = 1; i <= n; ++i)
        for(int k = 1; k <= m; ++k) {
            if(mp[i][k] == 0) continue;
            mp[i][k] = 0;
            for(int j = 0; j < 4; ++j)
                bfs(j, i, k);
            mp[i][k] = 1;
        }

    while(_--) {
        int ex, ey, sx, sy, tx, ty, ans = INF;
        cin >> ex >> ey >> sx >> sy >> tx >> ty;
        if(sx==tx && sy==ty) { cout << "0\n"; continue; }
        for(int d = 0; d < 4; ++d) {
            if(dis[d][sx][sy][ex][ey] == INF) continue;
            int tmp = dis[d][sx][sy][ex][ey] + dij(d, sx, sy, tx, ty);
            ans = min(ans, tmp);
        }
        if(ans == INF) cout << "-1\n";
        else cout << ans << "\n";
    }
    return 0;
}
