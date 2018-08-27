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
typedef long long LL;
typedef double DB;
typedef pair<int,int> pii;

const int maxn = 600;

const DB eps = 1e-10;
int cmp(DB a) {
    if(fabs(a) < eps) return 0;
    return a<0 ? -1 : 1;
}

struct Point {
    DB x, y;
    Point() {}
    Point(DB _x, DB _y) { x = _x, y = _y; }
    DB operator^(const Point &a) const { return x*a.y - y*a.x; } // 叉乘
    bool operator==(const Point &a) const { return cmp((*this)^a) == 0; }
    bool operator<(const Point &a) const { return cmp((*this)^a) < 0; }
} seg[maxn+5];

int n, m;
int hi[maxn+5], li[maxn+5], ri[maxn+5], wi[maxn+5];
LL f[maxn+5][maxn+5];
int main() {
    int _; scanf("%d", &_);
    while(_--) {
        scanf("%d", &n);
        m = 0;
        REP(i,1,n) {
            scanf("%d%d%d%d", hi+i, li+i, ri+i, wi+i);
            seg[++m] = Point(li[i], hi[i]);
            seg[++m] = Point(ri[i], hi[i]);
        }
        sort(seg+1, seg+1+m);
        m = unique(seg+1, seg+1+m) - seg - 1;
        REP(i,1,n) {
            li[i] = lower_bound(seg+1, seg+1+m, Point(li[i],hi[i])) - seg;
            ri[i] = lower_bound(seg+1, seg+1+m, Point(ri[i],hi[i])) - seg;
        }
        REP(t,1,m) {
            for(int l = 1, r = l+t-1; r <= m; ++l, ++r) {
                int pt = 0;
                for(int i = 1; i <= n; ++i)
                    if(l<=li[i] && ri[i]<=r) {
                        if(pt == 0) pt = i;
                        else if(wi[pt] < wi[i]) pt = i;
                    }
                if(pt == 0) { f[l][r] = 0; continue; }
                f[l][r] = 1LL << 50;
                for(int i = li[pt]; i <= ri[pt]; ++i)
                    f[l][r] = min(f[l][r], f[l][i-1]+f[i+1][r]+wi[pt]);
            }
        }
        printf("%lld\n", f[1][m]);
    }
    return 0;
}
