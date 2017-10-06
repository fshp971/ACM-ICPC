#include<bits/stdc++.h>

using namespace std;

#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define FOR(i,a,b) for(int i = a; i < b; ++i)
#define mem(a,b) memset(a,b,sizeof(a))
#define MP make_pair
#define PB push_back
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 200, maxt = 500;
const int Inv[13] = {0, 1, 7, 9, 10, 8, 11, 2, 5, 3, 4, 6, 12};

int A[maxt + 5][maxn + 5];
void Gauss(int n, int m) {
    for(int i = 0; i < m; ++i) {
        if(A[i][i] == 0) {
            int r = i;
            for(int j = i + 1; j < n; ++j)
                if(A[j][i]) { r = j; break; }
            for(int j = 0; j <= m; ++j)
                swap(A[i][j], A[r][j]);
        }
        for(int j = i + 1; j < n; ++j) {
            for(int k = m; k >= i; --k)
                A[j][k] = (A[j][k] - A[i][k] * Inv[A[i][i]] * A[j][i] % 13 + 13) % 13;
        }
    }
    for(int i = m - 1; i >= 0; --i) {
        for(int j = i + 1; j < m; ++j)
            A[i][m] = (A[i][m] - A[j][m] * A[i][j] % 13 + 13) % 13;
        A[i][m] = A[i][m] * Inv[A[i][i]] % 13;
    }
}

int mmp[maxn + 5][maxn + 5], dd[maxt + 5];
vector<pii> G[maxn + 5];

int dist[maxn + 5];
bool inq[maxn + 5];
int SPFA(int ss, int tt) {
    mem(dist, 0x7f);
    queue<int> que;
    que.push(ss), dist[ss] = 0, inq[ss] = 1;
    while(!que.empty()) {
        int x = que.front();
        que.pop(), inq[x] = 0;
        for(auto it : G[x]) {
            if(dist[x] + it.second < dist[it.first]) {
                dist[it.first] = dist[x] + it.second;
                if(!inq[it.first])
                    inq[it.first] = 1, que.push(it.first);
            }
        }
    }
    return dist[tt];
}

int main() {
    mem(mmp, -1), mem(A, 0);
    int n, ss, tt, m, tot = 0;
    int p, u, v;
    scanf("%d%d%d%d", &n, &ss, &tt, &m);
    for(int i = 0; i < m; ++i) {
        scanf("%d%d%d", dd + i, &p, &u);
        for(int k = 2; k <= p; ++k) {
            scanf("%d", &v);
            if(mmp[u][v] == -1) mmp[u][v] = mmp[v][u] = tot++;
            A[i][mmp[u][v]] = (A[i][mmp[u][v]] + 1) % 13;
            u = v;
        }
    }
    for(int i = 0; i < m; ++i) A[i][tot] = dd[i];
    Gauss(m, tot);
    for(int i = 1; i <= n; ++i)  {
        for(int k = i + 1; k <= n; ++k) {
            int &e = mmp[i][k];
            if(e != -1) {
                G[i].PB(MP(k,A[e][tot]));
                G[k].PB(MP(i,A[e][tot]));
            }
        }
    }
    printf("%d\n", SPFA(ss, tt));
    return 0;
}
