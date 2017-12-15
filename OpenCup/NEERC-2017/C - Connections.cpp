// Presentation error in case 1 ...
// Exactly the same idea as in tutorial
// Seems something wrong with the SPJ in opencup.ru
#include<bits/stdc++.h>

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

const int maxn = 1e5;

int n, m;
bool vist[maxn + 5];
vector<pii> G[2][maxn + 5];
int from[maxn + 5], to[maxn + 5];

queue<int> que;
bool vv[maxn + 5];
void Run(vector<pii> *GG) {
    for(int i = 1; i <= n; ++i) vv[i] = 0;
    que.push(1); vv[1] = 1;
    while(!que.empty()) {
        int x = que.front(); que.pop();
        for(auto it : GG[x]) {
            if(vv[it.fi]) continue;
            vv[it.fi] = 1, que.push(it.fi), vist[it.se] = 1;
        }
    }
}

int main() {
    int T, u, v;
    int bb = 1;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m);
        for(int i = 1; i <= n; ++i) G[0][i].clear(), G[1][i].clear();
        for(int i = 1; i <= m; ++i) {
            scanf("%d%d", &u, &v);
            vist[i] = 0, from[i] = u, to[i] = v;
            G[0][u].PB(MP(v,i)), G[1][v].PB(MP(u,i));
        }
        Run(G[0]);
        Run(G[1]);
        int rem = m - n*2;
        for(int i = 1; i <= m && rem > 0; ++i) {
            while(i <= m && vist[i]) ++i;
            if(!bb) printf("\n");
            bb = 0;
            printf("%d %d", from[i], to[i]);
            --rem;
        }
    }
    return 0;
}
