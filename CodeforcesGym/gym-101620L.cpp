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

const int maxn = 3000;
int mmp[5][maxn + 5][maxn + 5];

int main() {
    int n;
    scanf("%d", &n);
    char ord[5];
    int x, y, d;
    for(int i = 1; i <= n; ++i) {
        scanf("%s%d%d%d", ord, &x, &y, &d), x += maxn>>1, y += maxn>>1, d >>= 1;
        if(ord[0] == 'A') {
            ++mmp[0][x-d+1][y-d+1], --mmp[0][x+d+1][y-d+1];
            --mmp[0][x-d+1][y+d+1], ++mmp[0][x+d+1][y+d+1];
        }
        else {
            ++mmp[1][x][y-d+1], --mmp[1][x-d][y+1];
            ++mmp[2][x+1][y-d+1], --mmp[2][x+d+1][y+1];
            ++mmp[3][x-d+1][y+1], --mmp[3][x+1][y+d+1];
            ++mmp[4][x+d][y+1], --mmp[4][x][y+d+1];
        }
    }
    int ans = 0;
    for(int k = 1; k <= maxn; ++k) {
        int c[3]; mem(c, 0);
        for(int i = 1; i <= maxn; ++i) {
            c[0] += mmp[0][i][k];
            c[1] -= mmp[2][i][k];
            c[2] -= mmp[4][i][k];
            if(c[0] || c[1] || c[2]) ans += 4;
            else {
                int msk = 0;
                if(mmp[1][i][k]) msk |= (1<<0) | (1<<1);
                if(mmp[2][i][k]) msk |= (1<<0) | (1<<3);
                if(mmp[3][i][k]) msk |= (1<<1) | (1<<2);
                if(mmp[4][i][k]) msk |= (1<<2) | (1<<3);
                for(int t = 0; t <= 3; ++t) ans += (msk>>t)&1;
            }
            c[1] += mmp[1][i][k];
            c[2] += mmp[3][i][k];
            mmp[0][i][k+1] += mmp[0][i][k];
            mmp[1][i-1][k+1] += mmp[1][i][k];
            mmp[2][i+1][k+1] += mmp[2][i][k];
            mmp[3][i+1][k+1] += mmp[3][i][k];
            mmp[4][i-1][k+1] += mmp[4][i][k];
        }
    }
    printf("%.2f\n", (double)ans / 4.0);
    return 0;
}
