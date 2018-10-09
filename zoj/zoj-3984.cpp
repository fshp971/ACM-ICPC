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

const int maxn = 1e5;

int n, m, deg[maxn+5], num[maxn+5], rk[maxn+5];
int fa[maxn+5], sz[maxn+5];
int uu[maxn+5], vv[maxn+5];
vector<int> G[maxn+5];

bool cmp(const int &a, const int &b) { return deg[a] < deg[b]; }
int find(int x) { return fa[x]==x ? x : fa[x] = find(fa[x]); }

int T = 0, vis[maxn+5];
int sta[maxn+5];
vector<int> ans[maxn+5];
void Run() {
    int top, sum;
    for(int i = 1; i <= n; ++i) {
        ++T;
        top = 0, sum = 0;
        ans[i].clear();
        for(auto y : G[num[i]]) {
            if(find(y) == find(num[i])) { puts("No"); return; }
            if(vis[find(y)] != T) vis[find(y)] = T, sum += sz[find(y)], ans[i].PB(find(y));
        }
        if(sum != G[num[i]].size()) { puts("No"); return; }
        for(auto y : ans[i]) {
            sz[find(num[i])] += sz[find(y)];
            fa[find(y)] = find(num[i]);
        }
    }
    puts("Yes");
    for(int i = 1; i <= n; ++i) {
        printf("%d %d", num[i], int(ans[i].size()));
        for(auto u : ans[i]) printf(" %d", u);
        puts("");
    }
}

int main() {
    int _; scanf("%d", &_);
    while(_--) {
        scanf("%d%d", &n, &m);
        REP(i,1,n) deg[i] = 0, sz[i] = 1, num[i] = fa[i] = i, G[i].clear();
        REP(i,1,m) {
            scanf("%d%d", uu+i, vv+i);
            ++deg[uu[i]], ++deg[vv[i]];
        }
        sort(num+1, num+1+n, cmp);
        REP(i,1,n) rk[num[i]] = i;
        REP(i,1,m) {
            if(rk[uu[i]] < rk[vv[i]]) G[vv[i]].PB(uu[i]);
            else G[uu[i]].PB(vv[i]);
        }
        Run();
    }
    return 0;
}
