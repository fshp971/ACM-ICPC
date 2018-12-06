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
#define MP make_pair
#define PB push_back
#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define PER(i,a,b) for(int i = a; i >= b; --i)
#define fi first
#define se second
#define lson (x<<1)
#define rson (x<<1|1)
#define mid ((l+r)>>1)
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 1<<20;
const int maxnode = maxn<<1;

int n;
int lz[2][maxnode+5];
int cc[2][21];

void Build(int o, int x, int d, int l, int r) {
    ++cc[o][d];
    if(d>0) {
        Build(o, lson, d-1, l, mid);
        Build(o, rson, d-1, mid+1, r);
    }
}

void Upd(int o, int x, int d, int l, int r, int p) {
    if(d==0) lz[o][x]^=1;
    else {
        if(lz[o][x]!=-1) --cc[o][d];
        if(p<=mid) Upd(o, lson, d-1, l, mid, p);
        else Upd(o, rson, d-1, mid+1, r, p);
        if(lz[o][lson]!=-1 && lz[o][lson]==lz[o][rson]) {
            lz[o][x] = lz[o][lson];
            ++cc[o][d];
        }
        else lz[o][x] = -1;
    }
}

int main() {
    int _;
    scanf("%d%d", &n, &_);
    Build(0, 1, n, 1, (1<<n));
    Build(1, 1, n, 1, (1<<n));
    while(_--) {
        int o, p; scanf("%d%d", &o, &p);
        Upd(o, 1, n, 1, (1<<n), p);
        LL ans = 0, pcnt = 0;
        for(int i = n; i >= 0; --i) {
            ans += (1LL<<(n-i)) * (1LL<<(n-i)) - pcnt;
            pcnt = 4LL * cc[0][i] * cc[1][i];
        }
        printf("%lld\n", ans);
    }
    return 0;
}
