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

const double eps = 1e-10;

struct Point {
    double x, y;
    Point() {}
    Point(double _x, double _y) { x = _x, y = _y; }
    double operator * (const Point &a) { return x*a.x + y*a.y; } // 点乘
    double operator ^ (const Point &a) { return x*a.y - y*a.x; } // 叉乘
    Point operator + (const Point &a) { return Point(x+a.x, y+a.y); }
    Point operator - (const Point &a) { return Point(x-a.x, y-a.y); }
    Point operator * (const double &a) { return Point(x*a, y*a); }
    Point operator / (const double &a) { return Point(x/a, y/a); }
};

double Dist(Point &a, Point & b) { return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y)); }

// 返回三角形外心
Point Circumcenter(Point &a, Point &b, Point &c) {
    double a1 = b.x - a.x, b1 = b.y - a.y, c1 = (a1 * a1 + b1 * b1) / 2.0;
    double a2 = c.x - a.x, b2 = c.y - a.y, c2 = (a2 * a2 + b2 * b2) / 2.0;
    double d = a1 * b2 - a2 * b1;
    return Point(a.x + (c1*b2 - c2*b1) / d, a.y + (a1*c2 - a2*c1) / d);
}

// 点的最小圆覆盖
void MinCoverCircle(vector<Point> &seg, Point &O, double &R) {
    // 将点随机排序, 这样能保证总算法期望复杂度O(n)
    random_shuffle(seg.begin(), seg.end());
    int i, k, j, n = seg.size();
    for(O = seg[0], R = 0, i = 1; i < n; ++i) if(Dist(O,seg[i]) > R+eps) {
        for(O = seg[i], R = 0, k = 0; k < i; ++k) if(Dist(O,seg[k]) > R+eps) {
            O = (seg[i] + seg[k]) / 2, R = Dist(O, seg[i]);
            for(j = 0; j < k; ++j) if(Dist(O,seg[j]) > R+eps)
                O = Circumcenter(seg[i], seg[k], seg[j]), R = Dist(O,seg[i]);
        }
    }
}

int main() {
    int T, n, a, b;
    vector<Point> seg;
    scanf("%d%d", &T, &n);
    for(int i = 1; i <= n; ++i) {
        scanf("%d%d", &a, &b);
        seg.PB( Point(a*T + b, b) );
    }
    Point O; double R;
    MinCoverCircle(seg, O, R);
    printf("%.15f\n", R*R);
    return 0;
}
