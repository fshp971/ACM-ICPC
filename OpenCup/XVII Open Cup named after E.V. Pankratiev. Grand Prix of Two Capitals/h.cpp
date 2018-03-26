#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<cassert>
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

const int maxn = 100, md = 1e9 + 7;

int n, m, kk, cnt[maxn + 5][maxn + 5];
LL C[maxn + 5][maxn + 5];
bitset<maxn> bt[25];

void dfs(int ps, int msk, int fg, bitset<maxn> s1, bitset<maxn> s2) {
    // 以下为负优化
    // if(s1.count() < kk || s2.count() < kk) return;
    if(s1 == 0 || s2 == 0) return;
    if(ps < 0) {
        if(fg) ++cnt[s1.count()][s2.count()];
        else --cnt[s1.count()][s2.count()];
    }
    else if(msk>>ps&1) {
        dfs(ps-1, msk, fg, s1 & bt[ps], s2 & (~bt[ps]));
        dfs(ps-1, msk, fg, s1 & (~bt[ps]), s2 & bt[ps]);
    }
    else dfs(ps-1, msk, fg, s1, s2);
}

int main() {
    freopen("separating-sets.in", "r", stdin);
    freopen("separating-sets.out", "w", stdout);
    C[0][0] = 1;
    REP(i,1,maxn) REP(k,0,i) C[i][k] = (C[i-1][k-1] + C[i-1][k]) % md;
    scanf("%d%d%d", &n, &m, &kk);
    for(int i = 0, a, b; i < m; ++i) {
        scanf("%d", &a);
        while(a--) scanf("%d", &b), bt[i][b-1] = 1;
    }
    bitset<maxn> one;
    FOR(i,0,maxn) one[i] = (i<n);
    for(int i = 1; i < (1<<m); ++i)
        dfs(m-1, i, __builtin_popcountll(i)&1, one, one);
    LL ans = 0;
    REP(i,kk,n) REP(k,kk,n) {
        ans = (ans + C[i][kk] * C[k][kk] % md * cnt[i][k]) % md;
    }
    printf("%lld\n", ans);
    return 0;
}
