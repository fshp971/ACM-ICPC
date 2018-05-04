#include <bits/stdc++.h>

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

typedef long double DB; // 方便随时修改成long double

const DB eps = 1e-15;

// -1: a<b;  0: a==b;  1: a>b;
int Cmp(const DB &a, const DB &b) {
    if(fabs(a-b) < eps) return 0;
    return a<b ? -1 : 1;
}

struct Point {
    DB x, y;
    Point() {}
    Point(DB _x, DB _y) { x = _x, y = _y; }
    DB operator * (const Point &a) { return x*a.x + y*a.y; } // 点乘
    DB operator ^ (const Point &a) { return x*a.y - y*a.x; } // 叉乘
    Point operator + (const Point &a) { return Point(x+a.x, y+a.y); }
    Point operator - (const Point &a) { return Point(x-a.x, y-a.y); }
    Point operator * (const DB &a) { return Point(x*a, y*a); }
    Point operator / (const DB &a) { return Point(x/a, y/a); }
    DB Mod() { return sqrt(x*x + y*y); }
    bool operator<(const Point &a) const {
        if(Cmp(x, a.x) == 0) return Cmp(y, a.y) == -1;
        return Cmp(x, a.x) == -1;
    }
    bool operator==(const Point &a) const { return Cmp(x,a.x) == 0 && Cmp(y,a.y) == 0; }
    void Input() { double _x, _y; scanf("%lf%lf", &_x, &_y); x = _x, y = _y; }
};

bool Segment_Intersection(Point &a, Point &b, Point &c, Point &d) {
    Point v0 = b-a, v1 = c-a, v2 = d-a;
    if( Cmp(v0^v1, 0) * Cmp(v0^v2, 0) > 0) return false;
    v0 = d-c, v1 = a-c, v2 = b-c;
    if( Cmp(v0^v1, 0) * Cmp(v0^v2, 0) > 0) return false;
    if(((d-c) ^ (b-a)) == 0) {
        if(a == c || a == d || b == c || b == d) return true;
        return false;
    }
    return true;
}

const int maxn = 1000;

int n, m = 0, cnt = 0, eg = 0;
Point uu[maxn + 5], vv[maxn + 5];
int fa[maxn + 5], szz[maxn + 5], ccc[maxn + 5];

int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

int main() {
    scanf("%d", &n);
    FOR(i,0,n) uu[i].Input(), vv[i].Input(), fa[i] = i;
    FOR(i,0,n) FOR(k,i+1,n) {
        if(Segment_Intersection(uu[i],vv[i],uu[k],vv[k])) {
            ++m, ++ccc[i], ++ccc[k];
            int u = find(i), v = find(k);
            fa[v] = u, szz[u] += szz[v] + 1;
        }
    }
    for(int i = 0; i < n; ++i) {
        if(find(i) == i && szz[i]) ++cnt;
        if(ccc[i]) eg += ccc[i]-1;
    }
    printf("%d\n", cnt + eg - m);
    return 0;
}
