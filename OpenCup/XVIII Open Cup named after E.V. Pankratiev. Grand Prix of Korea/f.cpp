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

const int maxn = 15, maxk = 1 << maxn;

int n, bt[maxk + 5], G[maxn + 5][maxn + 5];
LL f[maxn][maxk + 5];

LL dfs(int x, int msk) {
    if(f[x][msk] != -1) return f[x][msk];
    if(bt[msk] == 1) return f[x][msk] = 0;
    f[x][msk] = 1LL << 60;
    int tmd = msk ^ (1 << x);
    for(int i = tmd; i > 0; i = (i-1) & tmd) {
        int s1 = (tmd ^ i) | (1<<x), s2 = i;
        for(int rt = 0; rt < n; ++rt) {
            if(s2>>rt&1)
                f[x][msk] = min(f[x][msk], dfs(x,s1) + dfs(rt,s2) + LL(bt[s2]) * (n-bt[s2]) * G[x][rt]);
        }
    }
    return f[x][msk];
}

int main() {
    REP(i,1,maxk) bt[i] = bt[i>>1] + (i&1);
    scanf("%d", &n);
    FOR(i,0,n) FOR(k,i+1,n) scanf("%d", &G[i][k]), G[k][i] = G[i][k];
    mem(f, -1);
    printf("%lld\n", dfs(1, (1<<n)-1));
    return 0;
}
