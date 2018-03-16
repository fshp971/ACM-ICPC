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

int tr[maxn + 5], tot = 0;
void Upd(int x, int d) { for(;x<=tot;x+=x&(-x)) tr[x]+=d; }
int Sum(int x) { int r=0; for(;x;x-=x&(-x)) r+=tr[x]; return r; }

int n, m, fa[maxn + 5], dep[maxn + 5], gg[maxn + 5], bt[maxn + 5];
int in[maxn + 5], out[maxn + 5], dfn[maxn + 5], id = 0;
vector<int> G[maxn + 5], G2[maxn + 5];

int find(int *a, int x) { return a[x] == x ? x : a[x] = find(a, a[x]); }

void dfs1(int x, int p) {
    fa[x] = p, dep[x] = dep[p] + 1, gg[x] = x, bt[x] = bt[p] ^ 1;
    in[x] = ++tot;
    for(auto it : G[x])
        if(!in[it]) dfs1(it, x);
    out[x] = tot;
}

void Up(int x, int p) {
    while(dep[x = find(gg,x)] > dep[p]) {
        Upd(in[x], 1), Upd(out[x]+1, -1);
        gg[x] = fa[x];
    }
}

void dfs2(int x, int p) {
    dfn[x] = ++id;
    for(auto it : G[x]) {
        if(it == p) continue;
        if(!dfn[it]) dfs2(it, x);
        else if(dfn[it] < dfn[x]) {
            if(bt[it] == bt[x]) Up(x, it);
            else G2[it].PB(x);
        }
    }
    for(auto it : G2[x]) {
        if(Sum(in[it]) - Sum(in[x]) > 0)
            Up(it, x);
    }
}

int ff[maxn + 5], cc[2][maxn + 5];

int main() {
    //freopen("in.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    for(int i = 1, u, v; i <= m; ++i) {
        scanf("%d%d", &u, &v);
        G[u].PB(v), G[v].PB(u);
    }
    dfs1(1,0);
    dfs2(1,0);
    REP(i,1,n) ff[i] = i, cc[bt[i]][i] = 1;
    LL ans0 = 0, ans1 = 0;
    for(int i = 2; i <= n; ++i)
        if(gg[i] == i) {
            int y = find(ff, fa[i]);
            ans0 += LL(cc[0][i]) * cc[0][y] + LL(cc[1][i]) * cc[1][y];
            ans1 += LL(cc[1][i]) * cc[0][y] + LL(cc[0][i]) * cc[1][y];
            ff[i] = y, cc[0][y] += cc[0][i], cc[1][y] += cc[1][i];
        }
    printf("%lld %lld\n", ans0, ans1);
    return 0;
}
