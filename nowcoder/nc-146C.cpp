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

const int maxn = 2e5;
const int P = 998244353;

inline LL PowMod(LL a, LL b) { LL r=1; while(b) { if(b&1) r=r*a%P; a=a*a%P, b>>=1; } return r; }

int n, sz[maxn + 5];
LL cnt[maxn + 5], ans[maxn + 5];
LL sum = 0;
vector<int> G[maxn + 5];

inline LL Two(LL a) {
    a = a*(a+1) / 2 % (P-1);
    return PowMod(2LL, a);
}

void dfs(int x, int p) {
    sz[x] = 1, cnt[x] = 1, ans[x] = 1;
    for(auto it : G[x]) {
        if(it == p) continue;
        dfs(it, x);
        sz[x] += sz[it];
        cnt[x] = cnt[x] * Two(sz[it]) % P;
        ans[x] = ans[x] * (cnt[it] + ans[it]) % P;
    }
    cnt[x] = (Two(sz[x]) - cnt[x] + P) % P;
}

void dfs2(int x, int p, LL val) {
    sum = (sum + ans[x] * val) % P;
    LL c = Two(n-sz[x]);
    for(auto it : G[x]) {
        if(it == p) continue;
        c = c * Two(sz[it]) % P;
    }
    for(auto it : G[x]) {
        if(it == p) continue;
        LL tmp = c * PowMod( Two(sz[it]), P-2 ) % P;
        tmp = (Two(n-sz[it]) - tmp + P) % P;
        dfs2(it, x, tmp);
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 1, u, v; i < n; ++i) {
        scanf("%d%d", &u, &v);
        G[u].PB(v), G[v].PB(u);
    }
    dfs(1, 0);
    dfs2(1, 0, 1LL);
    printf("%lld\n", sum);
    return 0;
}
