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

typedef double DB; // 方便随时修改成long double

const DB eps = 1e-10;

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
    void Unit() { (*this) = (*this) / Mod(); }
    void Print() { printf("%.10f %.10f\n", double(x), double(y)); }
    Point Rotate(const Point &a) { return Point(x*a.x - y*a.y, x*a.y + y*a.x); }
};

const int maxn = 1e4;

int n, m;
bool chan = false;
Point sta[2];
int id[2];
Point poly[maxn + 5], vec[maxn + 5], cent, ac;
DB len[maxn + 5];

Point GetP() {
    poly[n] = poly[0];
    DB area = 0;
    Point ans = Point(0,0);
    for(int i = 0; i < n; ++i) {
        area += (poly[i+1] ^ poly[i]);
        ans = ans + (poly[i]+poly[i+1]) * ((poly[i+1]^poly[i]));
    }
    area /= 2.0;
    return ans / area / 6.;
}

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 0, x, y; i < n; ++i) {
        scanf("%d%d", &x, &y);
        poly[i] = Point(x,y);
        if(i == 0) ac = poly[0];
        poly[i] = poly[i] - ac;
    }
    id[0] = 0, sta[0] = poly[0];
    id[1] = 1, sta[1] = poly[1];
    cent = GetP();
    for(int i = 0; i < n; ++i) {
        vec[i] = poly[i] - cent;
        len[i] = vec[i].Mod();
        vec[i].Unit();
    }
    while(m--) {
        int o, f, t, v;
        scanf("%d", &o);
        if(o == 1) {
            scanf("%d%d", &f, &t), --f, --t;
            chan = true;
            if(id[1] != f) swap(id[0], id[1]), swap(sta[0], sta[1]);
            cent = sta[0] - (Point(0,1) * len[id[0]]);
            Point delta = Point(vec[id[0]] * vec[t], vec[id[0]] ^ vec[t]);
            sta[1] = Point(0,1);
            sta[1] = sta[1].Rotate(delta) * len[t];
            sta[1] = cent + sta[1];
            id[1] = t;
        }
        else {
            scanf("%d", &v), --v;
            if(!chan)
                (poly[v]+ac).Print();
            else {
                Point delta = Point(vec[id[0]] * vec[v], vec[id[0]] ^ vec[v]);
                Point p = Point(0,1);
                p = p.Rotate(delta) * len[v];
                p = cent + p;
                (p+ac).Print();
            }
        }
    }
    return 0;
}
