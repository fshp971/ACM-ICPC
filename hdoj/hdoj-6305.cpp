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
const int md = 1e9 + 7;

LL inv[maxn + 5];
int n, L[maxn + 5], R[maxn + 5];
pii seg[maxn + 5], sta[maxn + 5];
LL ans = 1;

int Build() {
    int top = 0;
    for(int i = 1; i <= n; ++i) {
        L[seg[i].se] = R[seg[i].se] = 0;
        int x = top;
        while(x && sta[x] > seg[i]) --x;
        if(x) R[sta[x].se] = seg[i].se;
        if(x<top) L[seg[i].se] = sta[x+1].se;
        sta[++x] = seg[i]; top = x;
    }
    return sta[1].se;
}

int dfs(int x) {
    int szx = 1;
    if(L[x]) szx += dfs(L[x]);
    if(R[x]) szx += dfs(R[x]);
    ans = ans * inv[szx] % md;
    return szx;
}

int main() {
    inv[1] = 1;
    for(int i = 2; i <= maxn; ++i) inv[i] = (md - md/i) * inv[md%i] % md;
    int T; scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 1, a; i <= n; ++i) {
            scanf("%d", &a);
            seg[i] = MP(-a, i);
        }
        int rt = Build();
        ans = n * inv[2] % md;
        dfs(rt);
        printf("%lld\n", ans);
    }
    return 0;
}
