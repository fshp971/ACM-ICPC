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

const int maxn = 1e5, maxk = 2000;

int n, kk;
int B[maxk+5][maxk+5], W[maxk+5][maxk+5];

int S(int x, int y, int c) {
    int x1 = max(x-kk+1,1), y1 = max(y,1);
    int x2 = min(x,kk*2), y2 = min(y+kk-1, kk*2);
    if(x1 > x2 || y1 > y2) return 0;
    if(c == 0) return B[x2][y2] - B[x1-1][y2] - B[x2][y1-1] + B[x1-1][y1-1];
    return W[x2][y2] - W[x1-1][y2] - W[x2][y1-1] + W[x1-1][y1-1];
}

int main() {
    scanf("%d%d", &n, &kk);
    char str[5];
    for(int i = 1, x, y; i <= n; ++i) {
        scanf("%d%d%s", &x, &y, str);
        ++x, ++y;
        x %= kk*2, y %= kk*2;
        if(x == 0) x += kk*2;
        if(y == 0) y += kk*2;
        if(str[0] == 'B') ++B[x][y];
        else ++W[x][y];
    }
    for(int i = 1; i <= kk*2; ++i)
        for(int k = 1; k <= kk*2; ++k) {
            W[i][k] += W[i-1][k] + W[i][k-1] - W[i-1][k-1];
            B[i][k] += B[i-1][k] + B[i][k-1] - B[i-1][k-1];
        }
    int ans = 0;
    for(int i = 1; i <= kk+1; ++i) {
        for(int k = 1; k <= kk+1; ++k) {
            int tmp1 = 0, tmp2 = 0;
            int ti = i-kk, tj = k-kk*2;
            for(int ii = 0; ii < 4; ++ii)
                for(int jj = 0; jj < 4; ++jj) {
                    tmp1 += S(ti + kk * ii, tj + kk * jj, (ii+jj)&1);
                    tmp2 += S(ti + kk * ii, tj + kk * jj, ((ii+jj)&1) ^ 1);
                }
            ans = max(ans, max(tmp1, tmp2));
        }
    }
    printf("%d\n", ans);
    return 0;
}
