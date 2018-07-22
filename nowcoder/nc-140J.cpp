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

const int maxn = 1e6;

int n, m, T;
int X1[maxn + 5], Y1[maxn + 5], X2[maxn + 5], Y2[maxn + 5], col[maxn + 5];
int seg[maxn + 5], f[maxn + 5], g[maxn + 5];
bool vist[maxn + 5];

void Run(int *a) {
    for(int i = 0; i < n; ++i) {
        for(int k = 0; k < m; ++k) {
            if(i>0) a[i*m+k] += a[(i-1)*m+k];
            if(k>0) a[i*m+k] += a[i*m+(k-1)];
            if(i>0 && k>0)
                a[i*m+k] -= a[(i-1)*m+(k-1)];
        }
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &T);
    for(int i = 0; i < n*m; ++i) scanf("%d", seg + i);
    for(int i = 1; i <= T; ++i) {
        scanf("%d%d%d%d%d", X1+i, Y1+i, X2+i, Y2+i, col+i);
        --X1[i], --Y1[i], --X2[i], --Y2[i];
        ++f[ X1[i]*m+Y1[i] ];
        if(X2[i]+1<n) --f[ (X2[i]+1)*m+Y1[i] ];
        if(Y2[i]+1<m) --f[ X1[i]*m+(Y2[i]+1) ];
        if(X2[i]+1<n && Y2[i]+1<m)
            ++f[ (X2[i]+1)*m+(Y2[i]+1) ];
    }
    Run(f);

    for(int t = 0; t < 20; ++t) {
        for(int i = 0; i < n*m; ++i) g[i] = 0;
        for(int i = 1; i <= T; ++i) {
            if( !(col[i]>>t&1) ) continue;
            ++g[ X1[i]*m+Y1[i] ];
            if(X2[i]+1<n) --g[ (X2[i]+1)*m+Y1[i] ];
            if(Y2[i]+1<m) --g[ X1[i]*m+(Y2[i]+1) ];
            if(X2[i]+1<n && Y2[i]+1<m)
                ++g[ (X2[i]+1)*m+(Y2[i]+1) ];
        }
        Run(g);
        for(int i = 0; i < n*m; ++i) {
            if(seg[i]>>t&1) {
                if(g[i] < f[i]) vist[i] = 1;
            }
            else {
                if(g[i]) vist[i] = 1;
            }
        }
    }
    int ans = 0;
    for(int i = 0; i < n*m; ++i) ans += vist[i];
    printf("%d\n", ans);
    return 0;
}
