#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<cassert>
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

#define mid ((l + r) >> 1)

const int maxn = 2e5;
const int maxnode = maxn << 2;

int tot = 0, L[maxnode + 5], R[maxnode + 5];
int n, pos[maxn + 5], num[maxn + 5];
int rad[maxn + 5], cost[maxn + 5], Rank[maxn + 5];
vector<int> G[maxnode + 5];

int scc = 0, top = 0, Index = 0;
int sta[maxnode + 5], DFN[maxnode + 5], Low[maxnode + 5], Belong[maxnode + 5];
bool Insta[maxnode + 5];
multiset<int> Set[maxnode + 5];
bool bomb[maxnode + 5], deg[maxnode + 5];

void Tarjan(int u) {
    DFN[u] = Low[u] = ++Index;
    sta[++top] = u, Insta[u] = 1;
    for(auto it : G[u]) {
        if(!DFN[it]) {
            Tarjan(it);
            Low[u] = min(Low[u], Low[it]);
        }
        else if(Insta[it])
            Low[u] = min(Low[u], Low[it]);
    }
    int t;
    if(DFN[u] == Low[u]) {
        ++scc;
        do {
            t = sta[top--];
            Insta[t] = 0;
            Belong[t] = scc;
        } while(t != u);
    }
}

int Build(int l, int r) {
    if(l == r) return l;
    int x = ++tot;
    L[x] = Build(l, mid), G[x].PB(L[x]);
    R[x] = Build(mid + 1, r), G[x].PB(R[x]);
    return x;
}

void Upd(int x, int l, int r, int ll, int rr, int v) {
    if(ll <= l && r <= rr) { G[v].PB(x); return; }
    if(ll <= mid) Upd(L[x], l, mid, ll, rr, v);
    if(mid < rr) Upd(R[x], mid+1, r, ll, rr, v);
}

int maxr(int x) {
    int l = x, r = n, res = x;
    while(l <= r) {
        if(pos[num[mid]] <= pos[num[x]] + rad[num[x]])
            res = mid, l = mid + 1;
        else r = mid - 1;
    }
    return res;
}

int minl(int x) {
    int l = 1, r = x, res = x;
    while(l <= r) {
        if(pos[num[x]] - rad[num[x]] <= pos[num[mid]])
            res = mid, r = mid - 1;
        else l = mid + 1;
    }
    return res;
}

bool vist[maxnode + 5];
void dfs(int x) {
    if(vist[x]) return;
    vist[x] = 1;
    for(auto it : G[x]) dfs(it);
}

bool cmp(const int &a, const int &b) { return pos[a] < pos[b]; }

int main() {
    //freopen("in.txt", "r", stdin);
    int T, mm, cc;
    scanf("%d%d", &n, &T);
    for(int i = 1; i <= n; ++i)
        scanf("%d%d%d", pos + i, rad + i, cost + i), num[i] = i;
    sort(num + 1, num + 1 + n, cmp);
    REP(i,1,n) Rank[num[i]] = i;
    tot = n;
    int rt = Build(1,n);
    for(int i = 1; i <= n; ++i)
        Upd(rt, 1, n, minl(i), maxr(i), i);
    for(int i = 1; i <= tot; ++i) if(!DFN[i]) Tarjan(i);
    for(int i = 1; i <= n; ++i) dfs(i), Set[Belong[i]].insert(cost[num[i]]);
    for(int i = 1; i <= tot; ++i) if(vist[i]) bomb[Belong[i]] = 1;
    for(int i = 1; i <= tot; ++i) {
        if(!bomb[Belong[i]]) continue;
        for(auto it : G[i])
            if(Belong[i] != Belong[it])
                deg[Belong[it]] = 1;
    }
    LL ans = 0;
    for(int i = 1; i <= scc; ++i) {
        if(deg[i] || !Set[i].size()) continue;
        ans += *Set[i].begin();
    }
    while(T--) {
        scanf("%d%d", &mm, &cc);
        int be = Belong[Rank[mm]];
        if(!deg[be]) {
            ans -= *Set[be].begin();
            Set[be].erase( Set[be].find(cost[mm]) );
            Set[be].insert(cc);
            ans += *Set[be].begin(), cost[mm] = cc;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
