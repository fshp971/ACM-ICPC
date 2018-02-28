#include<bits/stdc++.h>

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

const int maxn = 1e6;

int n, seg[maxn + 5], num[maxn + 5];
int fa[maxn + 5], sz[maxn + 5];
bool vist[maxn + 5];
vector<int> G[maxn + 5];

int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

bool cmp(const int &a, const int &b) { return seg[a] < seg[b]; }

LL Calc() {
    LL ret = 0;
    REP(i,1,n) fa[i] = i, sz[i] = 1, vist[i] = 0;
    for(int i = 1; i <= n; ++i) {
        int x = num[i]; vist[x] = 1;
        LL tmp = 0, sum = 1;
        for(auto it : G[x]) {
            if(!vist[it]) continue;
            sum += sz[find(it)] * (tmp + 1);
            tmp += sz[find(it)], sz[x] += sz[find(it)];
            fa[find(it)] = x;
        }
        ret += sum * seg[x];
    }
    return ret;
}

int main() {
    scanf("%d", &n);
    REP(i,1,n) scanf("%d", seg + i), num[i] = i;
    for(int i = 1, u, v; i < n; ++i) {
        scanf("%d%d", &u, &v);
        G[u].PB(v), G[v].PB(u);
    }
    sort(num + 1, num + 1 + n, cmp);
    LL ans1 = Calc();
    reverse(num + 1, num + 1 + n);
    LL ans2 = Calc();
    printf("%lld\n", ans1 - ans2);
    return 0;
}
