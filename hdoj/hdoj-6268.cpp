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
typedef pair<int,int> pii;
typedef bitset<100001> BIT;

const int maxn = 3000;

int n, m, wi[maxn+5];
vector<int> G[maxn+5];
BIT f[maxn+5], ans;

int que[maxn+5], fa[maxn+5], sz[maxn+5], msz[maxn+5];
bool ban[maxn+5];
int FindRoot(int x) {
    int s = 1, t = 1;
    que[1] = x, fa[x] = 0;
    while(s <= t) {
        x = que[s++], sz[x] = 1, msz[x] = 0;
        for(auto y : G[x])
            if(!ban[y] && y!=fa[x])
                que[++t] = y, fa[y] = x;
    }
    for(int i = t; i >= 1; --i) {
        x = que[i], msz[x] = max(msz[x], t-sz[x]);
        if((msz[x]<<1) <= t) return x;
        sz[fa[x]] += sz[x], msz[fa[x]] = max(msz[fa[x]], sz[x]);
    }
    assert(false);
    return 0;
}

void dfs(int x, int p) {
    f[x] = f[p] << wi[x];
    for(auto y : G[x]) if(!ban[y] && y!=p) {
        dfs(y,x);
        f[x] |= f[y];
    }
}

void Solve(int x) {
    x = FindRoot(x);
    dfs(x,0);
    ans |= f[x];
    ban[x] = 1;
    for(auto y : G[x]) if(!ban[y]) Solve(y);
}

int main() {
    f[0][0] = 1;
    int _; scanf("%d", &_);
    while(_--) {
        scanf("%d%d", &n, &m);
        REP(i,1,n) G[i].clear(), ban[i] = 0;
        for(int i = 1, u,v; i < n; ++i) {
            scanf("%d%d", &u, &v);
            G[u].PB(v), G[v].PB(u);
        }
        REP(i,1,n) scanf("%d", wi+i);
        ans.reset();
        Solve(1);
        REP(i,1,m) printf("%d", int(ans[i]));
        puts("");
    }
    return 0;
}
