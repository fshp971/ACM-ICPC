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

const int maxn = 1e4;

char str[maxn + 5];
int n, pp, mm;

int tot = 0, mx[maxn + 5][105], mi[maxn + 5][105];
bool vv[maxn + 5][105];

int dfs(int &pt, int &cc, bool fg) {
    int id = tot++;
    if('0' <= str[pt] && str[pt] <= '9') {
        vv[id][0] = 1, mx[id][0] = mi[id][0] = str[pt] - '0';
        return id;
    }
    ++pt;
    int mc1 = 0, mc2 = 0;
    int id1 = dfs(pt, mc1, fg);
    pt += 2;
    int id2 = dfs(pt, mc2, fg);
    ++pt;
    cc = mc1 + mc2 + 1;
    int li = fg ? pp : mm;
    for(int i = 0; i <= li; ++i) {
        if(!vv[id1][i]) continue;
        for(int k = 0; k <= li; ++k) {
            if(!vv[id2][k]) continue;
            if(fg) {
                if(cc-i-k <= mm && i+k <= cc) {
                    mx[id][i+k] = max(mx[id][i+k], mx[id1][i] - mi[id2][k]);
                    mi[id][i+k] = min(mi[id][i+k], mi[id1][i] - mx[id2][k]);
                    vv[id][i+k] = 1;
                }

                if(i+k+1 <= pp && i+k+1 <= cc) {
                    mx[id][i+k+1] = max(mx[id][i+k+1], mx[id1][i] + mx[id2][k]);
                    mi[id][i+k+1] = min(mi[id][i+k+1], mi[id1][i] + mi[id2][k]);
                    vv[id][i+k+1] = 1;
                }
            }
            else {
                if(cc-i-k <= pp && i+k <= cc) {
                    mx[id][i+k] = max(mx[id][i+k], mx[id1][i] + mx[id2][k]);
                    mi[id][i+k] = min(mi[id][i+k], mi[id1][i] + mi[id2][k]);
                    vv[id][i+k] = 1;
                }

                if(i+k+1 <= mm && i+k+1 <= cc) {
                    mx[id][i+k+1] = max(mx[id][i+k+1], mx[id1][i] - mi[id2][k]);
                    mi[id][i+k+1] = min(mi[id][i+k+1], mi[id1][i] - mx[id2][k]);
                    vv[id][i+k+1] = 1;
                }
            }
        }
    }
    return id;
}

int main() {
    mem(mx, 0x80), mem(mi, 0x7f);
    scanf("%s", str + 1);
    scanf("%d%d", &pp, &mm);
    int pt = 1, cc = 0;
    int id = dfs(pt, cc, pp <= mm);
    printf("%d\n", mx[id][min(pp,mm)]);
    return 0;
}
