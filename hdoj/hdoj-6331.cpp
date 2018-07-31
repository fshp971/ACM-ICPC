#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<cassert>
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<queue>
#include<utility>
#include<bitset>
#include<complex>
#include<map>
#include<set>
#include<unordered_map>
#include<unordered_set>
#include<stack>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 50;
const int INF = 1LL << 29;

int n;
int mmp[maxn + 5][maxn + 5];
int A[105][maxn + 5][maxn + 5], B[105][maxn + 5][maxn + 5];

void Upd(int a[][maxn + 5], int b[][maxn + 5], int c[][maxn + 5]) {
    for(int i = 1; i <= n; ++i) {
        for(int k = 1; k <= n; ++k) {
            c[i][k] = INF;
            for(int j = 1; j <= n; ++j) {
                c[i][k] = min(c[i][k], a[i][j] + b[j][k]);
            }
        }
    }
}

priority_queue<pii> que;
void Dij(int *dis) {
    for(int i = 1; i <= n; ++i) {
        if(dis[i] != INF)
            que.push( MP(-dis[i], i) );
    }
    while(!que.empty()) {
        int x = que.top().se, d = -que.top().fi;
        que.pop();
        if(dis[x] != d) continue;
        for(int i = 1; i <= n; ++i) {
            if(d + mmp[x][i] < dis[i]) {
                dis[i] = d + mmp[x][i];
                que.push( MP(-dis[i], i) );
            }
        }
    }
}

int main() {
    int _; scanf("%d", &_);
    while(_--) {
        scanf("%d", &n);
        REP(i,1,n) REP(k,1,n) mmp[i][k] = INF;
        int T; scanf("%d", &T);
        for(int u, v, w; T; --T) {
            scanf("%d%d%d", &u, &v, &w);
            mmp[u][v] = min(mmp[u][v], w);
        }

        REP(i,1,n) REP(k,1,n)
            A[0][i][k] = B[0][i][k] = (i==k) ? 0 : INF;
        for(int i = 1; i <= 100; ++i)
            Upd(B[i-1], mmp, B[i]);
        for(int i = 1; i <= 100; ++i)
            Upd(A[i-1], B[100], A[i]);

        for(int i = 0; i <= 100; ++i) {
            for(int k = 1; k <= n; ++k)
                Dij(B[i][k]);
        }

        scanf("%d", &T);
        while(T--) {
            int ss, tt, kk;
            scanf("%d%d%d", &ss, &tt, &kk);
            int aa = kk / 100, bb = kk % 100, ans = INF;
            for(int i = 1; i <= n; ++i)
                ans = min(ans, A[aa][ss][i] + B[bb][i][tt]);
            printf("%d\n", (ans==INF) ? -1 : ans);
        }
    }
    return 0;
}
