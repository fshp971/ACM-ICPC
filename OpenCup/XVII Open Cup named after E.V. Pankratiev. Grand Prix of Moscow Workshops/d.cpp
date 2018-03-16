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

#define lson (x << 1)
#define rson (x << 1 | 1)
#define mid ((l + r) >> 1)

const int maxn = 3e5, N = maxn << 1;
const int maxnode = N << 2;
const int INF = 1 << 30;

int tr[maxnode + 5];

void Build(int x, int l, int r) { 
    tr[x] = -INF;
    if(l < r) {
        Build(lson, l, mid);
        Build(rson, mid+1, r);
    }
}

int Query(int x, int l, int r, int ll, int rr) {
    if(ll <= l && r <= rr) return tr[x];
    int res = -INF;
    if(ll <= mid) res = max(res, Query(lson, l, mid, ll, rr));
    if(mid < rr) res = max(res, Query(rson, mid+1, r, ll, rr));
    return res;
}

void Alt(int x, int l, int r, int p, int v) {
    if(l == r) tr[x] = v;
    else {
        if(p <= mid) Alt(lson, l, mid, p, v);
        else Alt(rson, mid+1, r, p, v);
        tr[x] = max(tr[lson], tr[rson]);
    }
}

int seg[maxn + 5], ans[maxn + 5];
deque<pii> que[N + 5];

int Push(int x, int v, int d) {
    while(!que[x].empty() && que[x].back().fi < v) que[x].pop_back();
    que[x].push_back(MP(v,d));
    return que[x].front().fi;
}

int Pop(int x, int d) {
    if(!que[x].empty() && que[x].front().se == d) que[x].pop_front();
    return que[x].empty() ? -INF : que[x].front().fi;
}

int main() {
    //freopen("in.txt", "r", stdin);
    int n, l, r;
    scanf("%d%d%d", &n, &l, &r);
    Build(1,0,N);
    seg[0] = maxn, ans[0] = 0;
    REP(i,1,n) scanf("%d", seg + i), seg[i] += seg[i-1];
    for(int i = 1, ll = 0, rr = 0; i <= n; ++i) {
        if(i - rr == l) {
            int v = Push(seg[rr], ans[rr], rr);
            //printf("i = %d, rr = %d, v = %d\n", i, rr, v);
            Alt(1, 0, N, seg[rr], v);
            ++rr;
        }
        if(i - ll > r) {
            int v = Pop(seg[ll], ll);
            Alt(1, 0, N, seg[ll], v);
            ++ll;
        }
        ans[i] = -INF;
        if(seg[i]-1 >= 0) ans[i] = max(ans[i], Query(1,0,N,0,seg[i]-1) + 1);
        ans[i] = max(ans[i], Query(1,0,N,seg[i],seg[i]));
        if(seg[i]+1 <= N) ans[i] = max(ans[i], Query(1,0,N,seg[i]+1,N) - 1);
    }
    //REP(i,0,n) printf("ans[%d] = %d\n", i, ans[i]);
    if(ans[n] < -n) puts("Impossible");
    else printf("%d\n", ans[n]);
    return 0;
}
