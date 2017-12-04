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

int n, dis[maxn + 5];
vector<LL> tree[maxn + 5];

int BinSearch(vector<LL> &seg, LL dd) {
    if(seg.size() <= 1) return 0;
    int l = 1, r = seg.size() - 1, res = 0;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(seg[mid] - seg[mid-1] <= dd)
            res = mid, l = mid + 1;
        else r = mid - 1;
    }
    return res;
}

LL Calc(int u, LL dd) {
    static LL sta[30];
    static int cnt[30];
    int tot = 0, all = 0, rk;
    LL res = 0, od = dd;
    rk = BinSearch(tree[u], dd), all += rk;
    res += tree[u][rk];
    while(u > 1) {
        int p = u >> 1, s = u^1;
        if(s <= n) {
            rk = BinSearch(tree[s], dd-dis[u]-dis[s]);
            res += tree[s][rk] + LL(dis[s]) * rk;
        }
        else rk = 0;
        all += rk;
        ++tot, sta[tot] = dis[u], cnt[tot] = rk;
        dd -= dis[u], u = p;
        if(dd >= 0) ++cnt[tot], ++all;
    }
    for(int i = tot; i >= 1; --i)
        res += sta[i] * cnt[i], cnt[i-1] += cnt[i];
    res = od * all - res;
    return res;
}

int main() {
    int T, ss, dd;
    scanf("%d%d", &n, &T);
    for(int i = 1; i < n; ++i)
        scanf("%d", &dis[i+1]);
    for(int i = n; i >= 1; --i) {
        tree[i].PB(0), tree[i].PB(0);
        int l = i<<1, r = i<<1|1;
        if(l <= n)
            for(int k = 1; k < tree[l].size(); ++k)
                tree[i].PB(tree[l][k] + dis[l]);
        if(r <= n)
            for(int k = 1; k < tree[r].size(); ++k)
                tree[i].PB(tree[r][k] + dis[r]);
        sort(tree[i].begin(), tree[i].end());
    }
    for(int i = 1; i <= n; ++i)
        for(int k = 1; k < tree[i].size(); ++k)
            tree[i][k] += tree[i][k-1];
    while(T--) {
        scanf("%d%d", &ss, &dd);
        printf("%lld\n", Calc(ss, dd));
    }
    return 0;
}
