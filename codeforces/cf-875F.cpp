#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define PB push_back
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 2e5;

int n, m, fa[maxn + 5];
int seg[maxn + 5], ai[maxn + 5], bi[maxn + 5], wi[maxn + 5];
bool vis[maxn + 5];

int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }
bool cmp(const int a, const int b) { return wi[a] > wi[b]; }

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1; i <= m; ++i)
        scanf("%d%d%d", ai + i, bi + i, wi + i), seg[i] = i;
    sort(seg + 1, seg + 1 + m, cmp);
    int ans = 0;
    for(int i = 1; i <= n; ++i) fa[i] = i;
    for(int i = 1; i <= m; ++i) {
        int &x = seg[i];
        int u = find(ai[x]), v = find(bi[x]);
        if(vis[u]) swap(u, v);
        if(u != v && !vis[u] && !vis[v])
            ans += wi[x], fa[u] = v;
        else if(!vis[u])
            ans += wi[x], vis[u] = 1;
    }
    printf("%d\n", ans);
    return 0;
}
