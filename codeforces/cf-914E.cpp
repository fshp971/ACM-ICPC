#include <bits/stdc++.h>

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

const int maxn = 2e5, Mask = 1 << 20;

int n, col[maxn + 5], size[maxn + 5];
LL ans[maxn + 5], cnt[Mask + 5];
bool vist[maxn + 5];
vector<int> G[maxn + 5];

void FindRoot(int x, int par, int sz, int &rt) {
    bool fg = 1;
    size[x] = 1;
    for(auto it : G[x]) {
        if(!vist[it] && it != par) {
            FindRoot(it, x, sz, rt);
            size[x] += size[it];
            fg &= (size[it] <= (sz>>1));
        }
    }
    fg &= (size[x] >= (sz>>1));
    if(fg) rt = x;
}

LL dfs1(int x, int par, int msk) {
    msk ^= (1<<col[x]);
    LL sum = cnt[msk];
    for(int i = 0; i < 20; ++i)
        sum += cnt[msk ^ (1<<i)];
    for(auto it : G[x])
        if(!vist[it] && it != par)
            sum += dfs1(it,x,msk);
    ans[x] += sum;
    return sum;
}

void dfs2(int x, int par, int msk, int val) {
    msk ^= (1<<col[x]);
    cnt[msk] += val;
    for(auto it : G[x])
        if(!vist[it] && it != par)
            dfs2(it, x, msk, val);
}

void Run(int x, int sz) {
    int rt;
    FindRoot(x, 0, sz, rt);
    vist[x = rt] = 1;
    ++ans[x];
    cnt[1<<col[x]] = 1;
    for(int i = 0; i < G[x].size(); ++i)
        if(!vist[G[x][i]]) {
            ans[x] += dfs1(G[x][i], 0, 0);
            dfs2(G[x][i], 0, 1<<col[x], 1);
        }
    for(int i = 0; i < G[x].size(); ++i)
        if(!vist[G[x][i]])
            dfs2(G[x][i], 0, 1<<col[x], -1);

    cnt[1<<col[x]] = 0;
    for(int i = int(G[x].size())-1; i >= 0; --i)
        if(!vist[G[x][i]]) {
            dfs1(G[x][i], 0, 0);
            dfs2(G[x][i], 0, 1<<col[x], 1);
        }
    for(int i = 0; i < G[x].size(); ++i)
        if(!vist[G[x][i]])
            dfs2(G[x][i], 0, 1<<col[x], -1);

    FindRoot(x, 0, sz, rt);
    for(auto it : G[x])
        if(!vist[it])
            Run(it, size[it]);
}

char str[maxn + 5];
int main() {
    int u, v;
    scanf("%d", &n);
    for(int i = 1; i < n; ++i) {
        scanf("%d%d", &u, &v);
        G[u].PB(v), G[v].PB(u);
    }
    scanf("%s", str);
    for(int i = 1; i <= n; ++i) col[i] = str[i-1] - 'a';
    Run(1,n);
    for(int i = 1; i <= n; ++i)
        printf("%lld%c", ans[i], (i < n) ? ' ' : '\n');
    return 0;
}
