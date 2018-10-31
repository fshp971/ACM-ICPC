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
typedef double DB;

const int maxn = 1e5;
const int maxnode = maxn<<2;

int n, m;

int tr[maxnode+5];
DB mx[maxnode+5];

void Build(int x, int l, int r) {
    tr[x] = 0, mx[x] = 0.0;
    if(l<r) {
        Build(lson, l, mid);
        Build(rson, mid+1, r);
    }
}

int Que(int x, int l, int r, DB v) {
    if(v>=mx[x]) return 0;
    if(l==r) return 1;
    if(v >= mx[lson]) return Que(rson, mid+1, r, v);
    else return tr[x]-tr[lson] + Que(lson, l, mid, v);
}

void Upd(int x, int l, int r, int p, DB v) {
    if(l==r) { tr[x] = 1, mx[x] = v; return; }
    if(p<=mid) Upd(lson, l, mid, p, v);
    else Upd(rson, mid+1, r, p, v);
    mx[x] = max(mx[lson], mx[rson]);
    tr[x] = tr[lson] + Que(rson, mid+1, r, mx[lson]);
}

int main() {
    scanf("%d%d", &n, &m);
    Build(1,1,n);
    while(m--) {
        int x, y; scanf("%d%d", &x, &y);
        Upd(1, 1, n, x, DB(y)/x);
        printf("%d\n", tr[1]);
    }
    return 0;
}
