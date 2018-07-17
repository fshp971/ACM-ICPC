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

const int maxn = 1e5, MaxStep = 17;
const int maxA = 1e7;
const int md = 1e9 + 7;

inline LL PowMod(LL a, LL b) { LL r=1; while(b) { if(b&1) r=r*a%md; a=a*a%md, b>>=1; } return r; }
LL Gcd(LL a, LL b) { return b ? Gcd(b,a%b) : a; }

vector<pii> deco[maxn*2 + 5];
void Deco(int id, int x) {
    int a = x;
    for(int i = 2; i*i <= a; ++i) {
        int c = 0;
        while(a%i == 0) a/=i, ++c;
        if(c) deco[id].PB( MP(i,c) );
    }
    if(a) deco[id].PB( MP(a,1) );
}

int n, m, ai[maxn + 5];
int st[maxn + 5][MaxStep + 2], dep[maxn + 5];
vector<int> G[maxn + 5];
vector<pii> add[maxn + 5], sub[maxn + 5];
LL ans[maxn + 5];
int cnt[maxA + 5];

void dfs(int x, int p, int d) {
    st[x][0] = p, dep[x] = d;
    for(int i = 0; st[x][i]; ++i)
        st[x][i+1] = st[st[x][i]][i];
    for(auto it : G[x])
        if(it != p) dfs(it, x, d+1);
}

int LCA(int u, int v) {
    if(u == v) return u;
    if(dep[u] < dep[v]) swap(u, v);
    int del = dep[u] - dep[v];
    for(int i = MaxStep; i >= 0; --i)
        if(del>>i&1) u = st[u][i];
    if(u == v) return u;
    for(int i = MaxStep; i >= 0; --i) {
        if(st[u][i] != st[v][i])
            u = st[u][i], v = st[v][i];
    }
    return st[u][0];
}

void dfs2(int x, int p) {
    for(auto it : deco[x]) {
        for(int i = 1, a = it.fi; i <= it.se; ++i, a*=it.fi)
            ++cnt[a];
    }
    for(auto it : add[x]) {
        for(auto it2 : deco[it.fi+n]) {
            int c = 0;
            for(int i = 1, a = it2.fi; i <= it2.se; ++i, a*=it2.fi)
                c += cnt[a];
            ans[it.fi] = ans[it.fi] * PowMod(it2.fi, c) % md;
        }
    }
    for(auto it : sub[x]) {
        LL tmp = 1;
        for(auto it2 : deco[it.fi+n]) {
            int c = 0;
            for(int i = 1, a = it2.fi; i <= it2.se; ++i, a*=it2.fi)
                c += cnt[a];
            tmp = tmp * PowMod(it2.fi, c) % md;
        }
        ans[it.fi] = ans[it.fi] * PowMod(tmp, md-3) % md * Gcd(it.se, ai[x]) % md;
    }
    for(auto it : G[x])  {
        if(it != p) dfs2(it, x);
    }
    for(auto it : deco[x]) {
        for(int i = 1, a = it.fi; i <= it.se; ++i, a*=it.fi)
            --cnt[a];
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 1, u, v; i < n; ++i) {
        scanf("%d%d", &u, &v);
        G[u].PB(v), G[v].PB(u);
    }
    for(int i = 1; i <= n; ++i)
        scanf("%d", ai + i), Deco(i, ai[i]);
    dfs(1, 0, 0);
    scanf("%d", &m);
    for(int i = 1, u, v, w; i <= m; ++i) {
        scanf("%d%d%d", &u, &v, &w), Deco(n+i, w);
        int lca = LCA(u, v);
        add[u].PB( MP(i,w) );
        add[v].PB( MP(i,w) );
        sub[lca].PB( MP(i,w) );
        ans[i] = 1;
    }
    dfs2(1, 0);
    for(int i = 1; i <= m; ++i) printf("%lld\n", ans[i]);
    return 0;
}
