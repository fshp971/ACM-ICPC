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
#define lson (x<<1)
#define rson (x<<1|1)
#define mid ((l+r)>>1)
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 2e5;
const int maxnode = maxn<<2;

int tr[maxnode+5];
void Upd(int x, int l, int r, int p, int v) {
    if(l==r) tr[x] = v;
    else {
        if(p<=mid) Upd(lson, l, mid, p, v);
        else Upd(rson, mid+1, r, p, v);
        tr[x] = max(tr[lson], tr[rson]);
    }
}
int Que(int x, int l, int r, int ll, int rr) {
    if(ll<=l && r<=rr) return tr[x];
    int res = 0;
    if(ll<=mid) res = max(res, Que(lson, l, mid, ll, rr));
    if(mid<rr) res = max(res, Que(rson, mid+1, r, ll, rr));
    return res;
}

int n;
int fa[maxn+5], dep[maxn+5];
int dfn, L[maxn+5], R[maxn+5];
vector<int> G[maxn+5];
int fp[maxn+5], ui[maxn+5], ci[maxn+5];
int cnt[maxn+5], ans[maxn+5];

void dfs(int x, int p) {
    fp[x] = 1, L[x] = ++dfn;
    for(auto y : G[x]) if(y!=p) {
        fa[y] = x, dep[y] = dep[x]+1;
        dfs(y,x);
    }
    R[x] = dfn;
}

int main() {
    int C, __; scanf("%d%d%d", &n, &C, &__);
    for(int i = 1, u,v; i < n; ++i) {
        scanf("%d%d", &u, &v);
        G[u].PB(v), G[v].PB(u);
    }
    dfs(1,0);
    ans[0] = C;
    for(int _ = 1; _ <= __; ++_) {
        int u,c,m; scanf("%d%d%d", &u, &c, &m);
        if(u==1) { printf("%d\n", ans[m]); continue; }
        ui[_] = u, ci[_] = c;
        while(u!=1) {
            int x = Que(1, 1, n, L[u], R[u]);
            if(x==0) { u = fa[u]; continue; }
            --ans[ cnt[ci[x]] ];
            cnt[ci[x]] -= dep[u] - dep[ fp[ui[x]] ];
            ++ans[ cnt[ci[x]] ];
            swap(fp[ui[x]], u);
        }
        fp[ui[_]] = 1;
        --ans[ cnt[ci[_]] ];
        cnt[ci[_]] += dep[ui[_]];
        ++ans[ cnt[ci[_]] ];
        Upd(1, 1, n, L[ui[_]], _);
        printf("%d\n", ans[m]);
    }
    return 0;
}
