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

const int maxn = 1e5;

int n, m, sq, seg[maxn + 5], mx[maxn + 5], arr[maxn + 5];
int que[maxn + 5], ed[maxn + 5], be[maxn + 5];
LL val[maxn + 5], vdel[maxn + 5], cdel[maxn + 5];

double Slope(int a, int b) { return double(val[b]-val[a]) / (arr[b]-arr[a]); }

void Build(int rk) {
    int l = rk * sq, r = min(l+sq, m) - 1;
    ed[rk] = l - 1;
    for(int i = l; i <= r; ++i) {
        while(l < ed[rk] && Slope(que[ed[rk]-1], que[ed[rk]]) > Slope(que[ed[rk]], i)) --ed[rk];
        que[++ed[rk]] = i;
    }
}

LL Query(int r) {
    LL res = 1LL << 60;
    for(int rk = 0; rk < be[r]; ++rk) {
        int l = rk * sq;
        while(l < ed[rk] && val[que[ed[rk]-1]] + vdel[rk] * arr[que[ed[rk]-1]] < val[que[ed[rk]]] + vdel[rk] * arr[que[ed[rk]]])
            --ed[rk];
        res = min(res, val[que[ed[rk]]] + vdel[rk] * arr[que[ed[rk]]] + cdel[rk]);
    }
    for(int i = be[r] * sq; i <= r; ++i)
        res = min(res, val[i] + vdel[ be[r] ] * arr[i] + cdel[ be[r] ]);
    return res;
}

void AddC(int r, LL d) {
    for(int rk = 0; rk < be[r]; ++rk) cdel[rk] += d;
    for(int i = be[r] * sq; i <= r; ++i) val[i] += d;
}

void AddV(int l) {
    for(int rk = be[l]+1; rk <= be[m-1]; ++rk) ++vdel[rk];
    for(int i = min((be[l]+1)*sq, m) - 1; i >= l; --i) val[i] += arr[i];
    Build(be[l]);
}

int main() {
    LL ans = 0;
    scanf("%d", &n);
    REP(i,1,n) scanf("%d", seg + i), arr[i] = seg[i], ans -= seg[i];
    sort(arr + 1, arr + 1 + n);
    m = unique(arr + 1, arr + 1 + n) - arr;
    REP(i,1,n) seg[i] = lower_bound(arr, arr + m, seg[i]) - arr, mx[i] = max(mx[i-1], seg[i]);
    sq = sqrt(m) + 1;
    for(int i = 0; i < m; ++i) be[i] = i/sq;
    for(int i = 0; i <= be[m-1]; ++i) Build(i);
    for(int i = 1; i <= n; ++i) {
        if(mx[i] == seg[i]) ans += arr[seg[i]];
        else {
            LL tmp = Query(seg[i]) + arr[seg[i]];
            AddC(seg[i]-1, arr[mx[i]]);
            AddV(seg[i]);
            val[seg[i]] = min(val[seg[i]], tmp - vdel[ be[seg[i]] ] * arr[seg[i]] - cdel[ be[seg[i]] ]);
            Build( be[seg[i]] );
        }
    }
    ans += Query(m-1);
    printf("%lld\n", ans);
    return 0;
}
