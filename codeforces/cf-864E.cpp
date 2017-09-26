#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 100;
const int maxd = 2000;

int n, ni[maxn + 5];
int ti[maxn + 5], di[maxn + 5], pi[maxn + 5];
int f[maxn + 5][maxd + 5], val[maxn + 5][maxd + 5];
pii pre[maxn + 5][maxd + 5];

bool cmp(int a, int b) { return di[a] < di[b]; }

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i)
        scanf("%d%d%d", ti + i, di + i, pi + i), ni[i] = i;
    sort(ni + 1, ni + 1 + n, cmp);
    for(int i = 1; i <= n; ++i) {
        for(int k = 1; k <= maxd; ++k) {
            if(f[i][k-1] < f[i-1][k])
                f[i][k] = f[i-1][k], pre[i][k] = MP(i-1,k);
            else f[i][k] = f[i][k-1], pre[i][k] = MP(i,k-1);
            if(k - ti[ni[i]] >= 0 && k < di[ni[i]] && f[i][k] < f[i-1][k-ti[ni[i]]] + pi[ni[i]]) {
                f[i][k] = f[i-1][k-ti[ni[i]]] + pi[ni[i]];
                val[i][k] = ni[i], pre[i][k] = MP(i-1, k-ti[ni[i]]);
            }
        }
    }
    int ans = 0, top = 0, sta[maxn + 5];
    pii pos = MP(n,0);
    for(int i = 1; i <= maxd; ++i)
        if(ans < f[n][i])
            ans = f[n][i], pos = MP(n,i);
    while(pos.first != 0) {
        if(val[pos.first][pos.second])
            sta[++top] = val[pos.first][pos.second];
        pos = pre[pos.first][pos.second];
    }
    printf("%d\n%d\n", ans, top);
    for(int i = top; i >= 1; --i) {
        if(i != top) printf(" ");
        printf("%d", sta[i]);
    }
    printf("\n");
    return 0;
}
