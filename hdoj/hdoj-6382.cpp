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
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
typedef long long LL;
typedef pair<int,int> pii;

const int P = 1e9 + 7;
const int maxn = 2e5;
const int maxnode = maxn * 10;

inline LL PowMod(LL a, LL b) { LL r=1; while(b) { if(b&1) r=r*a%P; a=a*a%P, b>>=1; } return r; }

struct Frac {
    LL a, b; // a/b
    Frac() {}
    Frac(int _a, int _b) : a(_a), b(_b) {}
    bool operator<(const Frac &f) const {
        return a*f.b < b*f.a;
    }
};

struct node {
    int l, r;
    Frac v;
    LL mul;
} heap[maxnode + 5];
int tot = 0;

int Merge(int x, int y) {
    if(!x || !y) return x|y;
    if(heap[y].v < heap[x].v) swap(x,y);
    int t = ++tot;
    heap[t] = heap[x];
    (rand()&1) ? (heap[t].l = Merge(heap[t].l,y)) : (heap[t].r = Merge(heap[t].r,y));
    return t;
}

int n, m, inv[maxn + 5], tr[maxn + 5];
int val[maxn + 5], mx[maxn + 5], res[maxn + 5];
vector<int> G[maxn + 5];

int all = 0;
pii ans[maxn + 5];

void dfs(int x, int p, int di) {
    if(x == 0) res[x] = 1, tr[x] = 0;
    else {
        tr[x] = tr[p];
        res[x] = res[p];
        Frac vv = Frac(mx[p], val[x]);
        LL mul = LL(val[x]) * inv[mx[p]] % P;
        if(di <= m) {
            res[x] = LL(res[x]) * mx[p] % P * inv[int(2e5)] % P;

            ++tot; assert(tot <= maxnode);
            heap[tot].l = heap[tot].r = 0;
            heap[tot].v = vv;
            heap[tot].mul = mul;
            tr[x] = Merge(tr[x], tot);
        }
        else if(tr[x] && heap[ tr[x] ].v < vv) {
            res[x] = LL(res[x]) * heap[ tr[x] ].mul % P;
            res[x] = LL(res[x]) * mx[p] % P * inv[int(2e5)] % P;
            tr[x] = Merge(heap[ tr[x] ].l, heap[ tr[x] ].r);

            ++tot; assert(tot <= maxnode);
            heap[tot].l = heap[tot].r = 0;
            heap[tot].v = vv;
            heap[tot].mul = mul;
            tr[x] = Merge(tr[x], tot);
        }
        else res[x] = LL(res[x]) * val[x] % P * inv[int(2e5)] % P;
    }
    mx[x] = -1;
    for(auto it : G[x]) mx[x] = max(mx[x], val[it]);
    if(mx[x] == -1) {
        ans[++all] = MP(x, res[x]);
        return;
    }
    for(auto it : G[x])
        dfs(it, x, di+1);
}

int main() {
    srand(time(NULL));
    inv[1] = 1;
    for(int i = 2; i <= maxn; ++i) inv[i] = LL(P-P/i) * inv[P%i] % P;
    int _; scanf("%d", &_);
    while(_--) {
        tot = 0;
        scanf("%d%d", &n, &m);
        FOR(i,0,n) G[i].clear();
        for(int i = 1, a, b, v; i < n; ++i) {
            scanf("%d%d%d", &a, &b, &v);
            G[a].PB(b), val[b] = v;
        }
        all = 0;
        dfs(0, -1, 0);
        sort(ans + 1, ans + 1 + all);
        for(int i = 1; i <= all; ++i)
            printf("%d\n", ans[i].se);
    }
    return 0;
}
