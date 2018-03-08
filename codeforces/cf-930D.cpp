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

const int N = 1e5, N2 = N<<1;

vector<pii> vec1, vec2;

int f[4][N2+5];
LL Calc(vector<pii>& seg) {
    for(int i = 0; i <= N2; ++i)
        f[0][i] = f[2][i] = 3*N2, f[1][i] = f[3][i] = -3*N2;
    for(auto it : seg) {
        f[0][it.fi] = f[2][it.fi] = min(f[0][it.fi], it.se);
        f[1][it.fi] = f[3][it.fi] = max(f[1][it.fi], it.se);
    }
    for(int i = 1; i <= N2; ++i) {
        f[0][i] = min(f[0][i], f[0][i-1]);
        f[1][i] = max(f[1][i], f[1][i-1]);
    }
    for(int i = N2-1; i >= 0; --i) {
        f[2][i] = min(f[2][i], f[2][i+1]);
        f[3][i] = max(f[3][i], f[3][i+1]);
    }
    LL ret = 0;
    for(int i = 0; i < N2; ++i)
        ret += max(0, min(f[1][i], f[3][i+1]) - max(f[0][i], f[2][i+1]));
    return ret;
}

int main() {
    int n;
    scanf("%d", &n);
    for(int i = 1, x, y; i <= n; ++i) {
        scanf("%d%d", &x, &y), x += N, y += N;
        if((x+y)&1) vec1.PB( MP((x+y)/2, (x-y-1)/2) );
        else vec2.PB( MP((x+y)/2, (x-y)/2) );
    }
    printf("%lld\n", Calc(vec1) + Calc(vec2));
    return 0;
}
