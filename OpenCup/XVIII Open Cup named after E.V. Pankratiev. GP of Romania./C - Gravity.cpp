#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define PF push_front
#define PB push_back
#define fi first
#define se second
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 2000;

int n, m, mov[maxn + 5][maxn + 5];
char mmp[maxn + 5][maxn + 5];
char ans[maxn + 5][maxn + 5];
const int walk[4][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};

deque<int> que;

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 0; i < n; ++i) scanf("%s", mmp[i]);
    mem(mov, 0x7f);
    for(int i = 0; i < m; ++i) {
        que.PB((n-1)*10000 + i);
        mov[n-1][i] = mmp[n-1][i] == '#' ? 0 : 1;
    }
    while(!que.empty()) {
        int x = que.front()/10000, y = que.front()%10000;
        que.pop_front();
        for(int i = 0; i < 4; ++i) {
            int xx = x + walk[i][0], yy = y + walk[i][1];
            if(xx < 0 || xx >= n || yy < 0 || yy >= m) continue;
            if(mmp[xx][yy] == '#' && mmp[x][y] == '#') {
                if(mov[xx][yy] > mov[x][y]) {
                    mov[xx][yy] = mov[x][y];
                    que.PF(xx*10000 + yy);
                }
            }
            else if(i == 1) {
                if(mmp[xx][yy] == '#') {
                    if(mov[xx][yy] > mov[x][y]) {
                        mov[xx][yy] = mov[x][y];
                        que.PB(xx*10000 + yy);
                    }
                }
                else {
                    if(mov[xx][yy] > mov[x][y] + 1) {
                        mov[xx][yy] = mov[x][y] + 1;
                        que.PB(xx*10000 + yy);
                    }
                }
            }
        }
    }
    FOR(i,0,n) FOR(k,0,m) ans[i][k] = '.';
    for(int i = 0; i < n; ++i)
        for(int k = 0; k < m; ++k)
            if(mmp[i][k] == '#') ans[i+mov[i][k]][k] = '#';
    for(int i = 0; i < n; ++i) {
        ans[i][m] = '\0';
        printf("%s\n", ans[i]);
    }
    return 0;
}
