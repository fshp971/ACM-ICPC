// ans = 52852124
// hint: brute force
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
#define PER(i,a,b) for(int i=a; i>=b; --i)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
typedef long long LL;

const int maxn = 2000;

int n;
int f[maxn+5][maxn+5];
LL s[maxn*maxn+5];

LL Go(int x, int y, int dx, int dy) {
    LL res = 0, now = 0;
    int px = x, py = y;
    while(1<=x&&x<=n && 1<=y&&y<=n) {
        now += f[x][y];
        while(now<=0 && (px!=x+dx || py!=y+dy))
            now -= f[px][py], px+=dx, py+=dy;
        res = max(res, now);
        x += dx, y += dy;
    }
    return res;
}

int main() {
    n = maxn;
    REP(i,1,55)
        s[i] = (100003 - 200003LL*i + 300007LL*i*i*i) % 1000000 - 500000;
    REP(i,56,n*n)
        s[i] = (s[i-24] + s[i-55] + 1000000) % 1000000 - 500000;
    //printf("s[100] = %lld\n", s[100]);
    int top = 0;
    REP(i,1,n) REP(k,1,n) f[i][k] = s[++top];
    LL ans = -(1LL<<60);
    REP(i,1,n) {
        ans = max(ans, Go(1,i,1,0));
        ans = max(ans, Go(1,i,1,1));
        ans = max(ans, Go(1,i,1,-1));

        ans = max(ans, Go(i,1,0,1));
        ans = max(ans, Go(i,1,1,1));
        ans = max(ans, Go(i,1,-1,1));
    }
    printf("%lld\n", ans);
    return 0;
}
