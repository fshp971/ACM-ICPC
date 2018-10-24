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
#define lson (x<<1)
#define rson (x<<1|1)
#define mid ((l+r)>>1)
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 1e5;
const int Step = 16;
const int maxnode = maxn<<2;

int n, L, wi[maxn+5];
LL S, dep[maxn+5];
int f[maxn+5];
vector<int> G[maxn+5], R[maxn+5];
int st[maxn+5][Step+2];
int DFN, in[maxn+5];

int tr[maxnode+5], lz[maxnode+5];
void PushDown(int x) {
    tr[lson] += lz[x], lz[lson] += lz[x];
    tr[rson] += lz[x], lz[rson] += lz[x];
    lz[x] = 0;
}
void Upd(int x, int l, int r, int p, int v) {
    if(l==r) tr[x] = v, lz[x] = 0;
    else {
        PushDown(x);
        if(p<=mid) Upd(lson, l, mid, p, v);
        else Upd(rson, mid+1, r, p, v);
        tr[x] = min(tr[lson], tr[rson]);
    }
}
void Add(int x, int l, int r, int ll, int rr, int v) {
    if(ll<=l && r<=rr) tr[x] += v, lz[x] += v;
    else {
        PushDown(x);
        if(ll<=mid) Add(lson, l, mid, ll, rr, v);
        if(mid<rr) Add(rson, mid+1, r, ll, rr, v);
        tr[x] = min(tr[lson], tr[rson]);
    }
}
int Que(int x, int l, int r, int ll, int rr) {
    if(ll<=l && r<=rr) return tr[x];
    int ret = 1e9;
    PushDown(x);
    if(ll<=mid) ret = min(ret, Que(lson, l, mid, ll, rr));
    if(mid<rr) ret = min(ret, Que(rson, mid+1, r, ll, rr));
    return ret;
}

void dfs(int x, int p) {
    in[x] = ++DFN;
    st[x][0] = p;
    dep[x] = dep[p] + wi[x];
    for(int i = 0; st[x][i]; ++i)
        st[x][i+1] = st[st[x][i]][i];
    int u = x, c = 1;
    for(int i = Step; i >= 0; --i) {
        if(st[u][i] == 0) continue;
        if(c+(1<<i) > L) continue;
        if(dep[x]-dep[st[u][i]]+wi[st[u][i]] > S) continue;
        c += (1<<i), u = st[u][i];
    }
    R[u].PB(x);
    int gg = 0;
    for(auto y : G[x]) if(y!=p) {
        dfs(y,x);
        gg += f[y];
    }
    f[x] = Que(1, 1, n, in[x], DFN) + gg + 1;
    Add(1, 1, n, in[x], DFN, gg-f[x]);
    for(auto y : R[x]) Upd(1, 1, n, in[y], 1e9);
}

int main() {
    scanf("%d%d%lld", &n, &L, &S);
    REP(i,1,n) {
        scanf("%d", wi+i);
        if(wi[i] > S) exit( puts("-1")*0 );
    }
    for(int i = 2, p; i <= n; ++i)
        scanf("%d", &p), G[p].PB(i);
    dfs(1,0);
    printf("%d\n", f[1]);
    return 0;
}
