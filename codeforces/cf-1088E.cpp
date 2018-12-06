#include <bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define MP make_pair
#define PB push_back
#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define PER(i,a,b) for(int i = a; i >= b; --i)
#define fi first
#define se second
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 3e5;

int n, ai[maxn+5];
vector<int> G[maxn+5];
LL ans = -LL(1e9)*maxn;
int cnt = 0;
LL f[maxn+5];

void dfs(int x, int p) {
    f[x] = ai[x];
    for(auto y : G[x]) if(y!=p) {
        dfs(y,x);
        if(f[y]>0) f[x]+=f[y];
    }
    ans = max(ans, f[x]);
}

void dfs2(int x, int p) {
    f[x] = ai[x];
    for(auto y : G[x]) if(y!=p) {
        dfs2(y,x);
        if(f[y]>0) f[x]+=f[y];
    }
    if(f[x]==ans) ++cnt, f[x] = 0;
}

int main() {
    scanf("%d", &n);
    REP(i,1,n) scanf("%d", ai+i);
    for(int i = 1, u,v; i < n; ++i) {
        scanf("%d%d", &u, &v);
        G[u].PB(v), G[v].PB(u);
    }
    dfs(1,0);
    dfs2(1,0);
    printf("%lld %d\n", ans*cnt, cnt);
    return 0;
}
