#include<bits/stdc++.h>

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
typedef double DB;

const int maxn = 200;
const double INF = 1e10;

const DB eps = 1e-8;
inline int Cmp(DB a, DB b) {
    if(fabs(a-b) < eps) return 0;
    return a<b ? -1 : 1;
}

struct Point {
    DB x, y;
    Point() {}
    Point(DB _x, DB _y) : x(_x), y(_y) {}
    Point operator+(const Point &a) { return Point(x+a.x, y+a.y); }
    Point operator-(const Point &a) { return Point(x-a.x, y-a.y); }
    double operator*(const Point &a) { return x*a.x + y*a.y; }
    double operator^(const Point &a) { return x*a.y - a.x*y; }
    Point operator*(const DB &a) { return Point(x*a, y*a); }
    Point operator/(const DB &a) { return Point(x/a, y/a); }
    double Mod() { return sqrt(x*x + y*y); }
    void Input() { int _x, _y; scanf("%d%d", &_x, &_y); x = _x, y = _y; }
};

DB Inter(Point &a, Point &b, Point &c, Point &d) {
    DB d1 = (a-c) ^ (d-c);
    DB d2 = (d-c) ^ (b-a);
    if(Cmp(d2,0) == 0) return INF;
    return d1 / d2;
}

int n, m;
Point A[maxn + 5], B[maxn + 5];
DB L[maxn + 5], R[maxn + 5];

DB f[maxn + 5][maxn + 5];
bool vist[maxn + 5][maxn + 5];

DB dfs(int l, int r) {
    if(vist[l][r]) return f[l][r];
    vist[l][r] = 1, f[l][r] = INF;
    int ll = (l-1+m) % m, rr = (r+1) % m;
    for(int i = l;; i = (i+1)%m) {
        double ld = L[i], rd = R[i];

        double tmp = Inter(B[i], B[(i+1)%m], B[ll], B[(ll+1)%m]);
        if(Cmp(tmp,0) <= 0) ld = max(ld, tmp);
        else rd = min(rd, tmp);

        tmp = Inter(B[i], B[(i+1)%m], B[rr], B[(rr+1)%m]);
        if(Cmp(tmp,0) <= 0) ld = max(ld, tmp);
        else rd = min(rd, tmp);

        tmp = (rd - ld) * (B[(i+1)%m] - B[i]).Mod();
        if(i != l) tmp += dfs(l, (i-1+m)%m);
        if(i != r) tmp += dfs((i+1)%m, r);

        f[l][r] = min(f[l][r], tmp);

        if(i == r) break;
    }
    return f[l][r];
}

int main() {
    scanf("%d", &n);
    FOR(i,0,n) A[i].Input();
    scanf("%d", &m);
    FOR(i,0,m) B[i].Input();
    for(int i = 0; i < m; ++i) {
        L[i] = -INF, R[i] = INF;
        for(int k = 0; k < n; ++k) {
            DB t = Inter(B[i], B[(i+1)%m], A[k], A[(k+1)%n]);
            if(Cmp(t,0) <= 0) L[i] = max(L[i], t);
            else R[i] = min(R[i], t);
        }
    }
    DB ans = INF;
    for(int i = 0; i < m; ++i) {
        DB tmp = (B[(i+1)%m] - B[i]).Mod() * (R[i] - L[i]);
        tmp += dfs((i+1)%m, (i-1+m)%m);
        ans = min(ans, tmp);
    }
    printf("%.10f\n", (double)ans);
    return 0;
}
