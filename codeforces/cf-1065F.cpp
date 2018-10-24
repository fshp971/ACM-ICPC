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

const int maxn = 1e6;

int n, kk, bk[maxn+5], nd[maxn+5], dep[maxn+5], f[maxn+5];
vector<int> G[maxn+5];

void dfs(int x, int p, int d) {
    bk[x] = x, dep[x] = d, nd[d] = x;
    bool fg = 0;
    for(auto y : G[x]) if(y!=p) {
        dfs(y,x,d+1), fg = 1;
        if(dep[bk[x]] > dep[bk[y]]) bk[x] = bk[y];
    }
    if(!fg) bk[x] = nd[max(d-kk,0)];
}

void dfs2(int x, int p) {
    bk[x] = bk[bk[x]];
    bool fg = 0;
    for(auto y : G[x]) if(y!=p) {
        dfs2(y,x), fg = 1;
    }
    if(!fg) ++f[bk[x]];
}

void dfs3(int x, int p) {
    int mx = 0;
    for(auto y : G[x]) if(y!=p) {
        dfs3(y,x);
        mx = max(mx, f[y]);
    }
    f[x] += mx;
}

int main() {
    scanf("%d%d", &n, &kk);
    for(int i = 2, p; i <= n; ++i)
        scanf("%d", &p), G[p].PB(i);
    dfs(1,0,0);
    dfs2(1,0);
    dfs3(1,0);
    printf("%d\n", f[1]);
    return 0;
}
