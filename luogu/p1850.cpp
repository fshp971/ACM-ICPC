#include<iostream>
#include<iomanip>
#include<algorithm>

using namespace std;

const int maxn = 2000, maxv = 300, INF = 1e9;

int n, m, vv, ee, ci[maxn+5], di[maxn+5];
double ki[maxn+5];
double f[2][2][maxn+5];
int dis[maxv+5][maxv+5];

int main() {
    ios::sync_with_stdio(0);
    cin >> n >> m >> vv >> ee;
    for(int i = 1; i <= n; ++i) cin >> ci[i];
    for(int i = 1; i <= n; ++i) cin >> di[i];
    for(int i = 1; i <= n; ++i) cin >> ki[i];

    for(int i = 1; i <= vv; ++i)
        for(int k = 1; k <= vv; ++k)
            dis[i][k] = (i!=k) * INF;

    for(int i = 1, u,v,w; i <= ee; ++i) {
        cin >> u >> v >> w;
        dis[u][v] = dis[v][u] = min(dis[u][v], w);
    }

    for(int j = 1; j <= vv; ++j)
        for(int i = 1; i <= vv; ++i)
            for(int k = 1; k <= vv; ++k)
                if(dis[i][k] > dis[i][j] + dis[j][k])
                    dis[i][k] = dis[i][j] + dis[j][k];

    int fg = 0;
    f[fg][1][0] = 1e10;
    for(int i = 2; i <= n; ++i) {
        for(int t = 0; t <= 1; ++t)
            for(int k = 0; k <= m; ++k)
                f[fg^1][t][k] = 1e10;

        for(int t1 = 0; t1 <= 1; ++t1) {
            double p1 = ((t1) ? ki[i-1] : 0);
            for(int t2 = 0; t2 <= 1; ++t2) {
                double p2 = ((t2) ? ki[i] : 0);

                double cost = dis[ci[i-1]][ci[i]] * (1-p1) * (1-p2);
                cost += dis[ci[i-1]][di[i]] * (1-p1) * p2;
                cost += dis[di[i-1]][ci[i]] * p1 * (1-p2);
                cost += dis[di[i-1]][di[i]] * p1 * p2;

                for(int k = t2; k <= m; ++k)
                    f[fg^1][t2][k] = min(f[fg^1][t2][k], f[fg][t1][k-t2] + cost);
            }
        }
        fg ^= 1;
    }

    cout << fixed << setprecision(2) << min(f[fg][0][m], f[fg][1][m]) << "\n";
    return 0;
}
