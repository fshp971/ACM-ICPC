// 我为什么要写主席树啊囧
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
const int maxnode = maxn << 6;

int n, m, num[maxn + 5];
LL ai[maxn + 5], bi[maxn + 5];
LL seg[maxn + 5];

int tot = 0, rot[maxn + 5], L[maxnode + 5], R[maxnode + 5], cnt[maxnode + 5];
LL sum[maxnode + 5];

int Upd(int prt, int l, int r, int p) {
    int rt = ++tot;
    L[rt] = L[prt], R[rt] = R[prt];
    cnt[rt] = cnt[prt] + 1;
    sum[rt] = sum[prt] + seg[p];
    if(l < r) {
        int mid = (l + r) >> 1;
        if(p <= mid) L[rt] = Upd(L[prt], l, mid, p);
        else R[rt] = Upd(R[prt], mid+1, r, p);
    }
    return rt;
}

pair<LL,int> Query(int rt, int l, int r, LL lim) {
    if(sum[rt] < lim) return MP(sum[rt], cnt[rt]);
    if(l == r) {
        int t = lim / seg[l];
        if(seg[l] * t < lim) ++t;
        return MP(seg[l]*t, t);
    }
    int mid = (l + r) >> 1;
    pair<LL,int> ret = Query(R[rt], mid + 1, r, lim);
    if(lim <= ret.fi) return ret;
    pair<LL,int> tmp = Query(L[rt], l, mid, lim - ret.fi);
    ret.fi += tmp.fi, ret.se += tmp.se;
    return ret;
}

bool cmp(const int &a, const int &b) {
    return ai[a]+bi[a] < ai[b]+bi[b];
}

int main() {
    freopen("artifact.in", "r", stdin);
    freopen("artifact.out", "w", stdout);
    scanf("%d", &n);
    REP(i,1,n) scanf("%lld%lld", ai + i, bi + i), num[i] = i, seg[i] = ai[i];
    sort(num + 1, num + 1 + n, cmp);
    sort(seg + 1, seg + 1 + n);
    m = unique(seg + 1, seg + 1 + n) - seg - 1;
    rot[0] = 0;
    int ans = n + 1;
    for(int i = 1; i <= n; ++i) {
        int rk = lower_bound(seg + 1, seg + 1 + m, ai[num[i]]) - seg;
        rot[i] = Upd(rot[i-1], 1, m, rk);
        pair<LL,int> tmp = Query(rot[i], 1, m, ai[num[i]] + bi[num[i]]);
        if(ai[num[i]] + bi[num[i]] <= tmp.fi)
            ans = min(ans, tmp.se);
    }
    printf("%d\n", (ans == n+1) ? -1 : ans);
    return 0;
}
