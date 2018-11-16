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
const int maxnode = maxn<<2;

bool tr[maxnode+5][4];
void Build(int x, int l, int r) {
    mem(tr[x],0);
    if(l<r) {
        Build(lson, l, mid);
        Build(rson, mid+1, r);
    }
}

void PushUp(int x) {
    tr[x][0] = (tr[lson][1]&tr[rson][2]) | (tr[lson][0]&tr[rson][0]);
    tr[x][1] = (tr[lson][1]&tr[rson][3]) | (tr[lson][0]&tr[rson][1]);
    tr[x][2] = (tr[lson][2]&tr[rson][0]) | (tr[lson][3]&tr[rson][2]);
    tr[x][3] = (tr[lson][2]&tr[rson][1]) | (tr[lson][3]&tr[rson][3]);
}

void Upd(int x, int l, int r, int p, int v) {
    if(l==r) tr[x][v]^=1;
    else {
        if(p<=mid) Upd(lson, l, mid, p, v);
        else Upd(rson, mid+1, r, p, v);
        PushUp(x);
    }
}

struct Node {
    int p1, p2;
    LL v;
    Node() {}
    Node(int _p1, int _p2, LL _v) : p1(_p1), p2(_p2), v(_v) {}
    bool operator<(const Node &a) const { return v < a.v; }
} seg[maxn*2+5];
int tot;

int n, ai[maxn+5];

int main() {
    int _; scanf("%d", &_);
    while(_--) {
        scanf("%d", &n);
        REP(i,1,n) scanf("%d", ai+i);
        tot = 0;
        REP(i,1,n) {
            seg[++tot] = Node(i,i,ai[i]);
            if(i+1<=n) seg[++tot] = Node(i,i+1,ai[i]+ai[i+1]);
        }
        sort(seg+1, seg+1+tot);
        LL ans = 1LL << 60;
        Build(1,1,n);
        for(int i = 1, k = 0; i <= tot; ++i) {
            while(!tr[1][0] && k+1<=tot) {
                ++k;
                if(seg[k].p1 == seg[k].p2) {
                    Upd(1, 1, n, seg[k].p1, 0);
                }
                else {
                    Upd(1, 1, n, seg[k].p1, 1);
                    Upd(1, 1, n, seg[k].p2, 2);
                }
            }
            if(tr[1][0]) ans = min(ans, seg[k].v-seg[i].v);
            if(seg[i].p1 == seg[i].p2) {
                Upd(1, 1, n, seg[i].p1, 0);
            }
            else {
                Upd(1, 1, n, seg[i].p1, 1);
                Upd(1, 1, n, seg[i].p2, 2);
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
