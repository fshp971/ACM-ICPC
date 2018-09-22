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
#include<stack>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define PER(i,a,b) for(int i=a; i>=b; --i)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
#define lson (x<<1)
#define rson (x<<1|1)
#define mid ((l+r)>>1)
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 1e5 + 5;
const int maxnode = maxn << 2;

inline LL S1(LL n) { return (n*(n+1)) >> 1; }

LL tr[maxnode+5], lz[maxnode+5];

void PushDown(int x, int l, int r) {
    lz[lson] += lz[x], tr[lson] += lz[x]*(mid-l+1);
    lz[rson] += lz[x], tr[rson] += lz[x]*(r-mid);
    lz[x] = 0;
}

void Add(int x, int l, int r, int ll, int rr, LL v) {
    if(ll <= l && r <= rr) {
        lz[x] += v, tr[x] += v*(r-l+1);
    }
    else {
        PushDown(x,l,r);
        if(ll <= mid) Add(lson, l, mid, ll, rr, v);
        if(mid < rr) Add(rson, mid+1, r, ll, rr, v);
        tr[x] = tr[lson] + tr[rson];
    }
}

LL Query(int x, int l, int r, int ll, int rr) {
    if(ll <= l && r <= rr) return tr[x];
    PushDown(x,l,r);
    LL ret = 0;
    if(ll <= mid) ret += Query(lson, l, mid, ll, rr);
    if(mid < rr) ret += Query(rson, mid+1, r, ll, rr);
    return ret;
}

struct Node {
    int l, r, x, fg, id;
    Node() {}
    Node(int _l, int _r, int _x, int _fg, int _id) : l(_l), r(_r), x(_x), fg(_fg), id(_id) {}
    bool operator<(const Node &a) const { return x < a.x; }
} seg[maxn*2+5];
int tot = 0;

int n, m, ai[maxn+5], sta[maxn+5];
LL ans[maxn+5];
int main() {
    scanf("%d%d", &n, &m);
    REP(i,1,n) scanf("%d", ai+i);
    REP(i,1,m) {
        int l, r;
        scanf("%d%d", &l, &r);
        seg[++tot] = Node(l, r, r, 1, i);
        if(l-1>=1) seg[++tot] = Node(l, r, l-1, -1, i);
    }
    sort(seg+1, seg+1+tot);
    int top = 0, pt = 1;
    for(int i = 1; i <= n && pt <= tot; ++i) {
        while(top>0 && ai[i]<=ai[sta[top]]) --top;
        sta[++top] = i;
        REP(k,1,top) Add(1, 1, n, sta[k-1]+1, sta[k], ai[sta[k]]);
        while(pt<=tot && seg[pt].x==i) {
            ans[seg[pt].id] += Query(1,1,n,seg[pt].l,seg[pt].r) * seg[pt].fg;
            ++pt;
        }
    }
    REP(i,1,m) printf("%lld\n", ans[i]);
    return 0;
}
