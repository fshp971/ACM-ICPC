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
typedef double DB;

#define lson (x << 1)
#define rson (x << 1 | 1)
#define mid ((l + r) >> 1)

const DB eps = 1e-8;
int cmp(DB x) {
    if(fabs(x) < eps) return 0;
    return x > 0 ? 1 : -1;
}

const DB pi = acos(-1.0);
inline DB sqr(DB x) { return x*x; }

struct point {
    DB x, y;
    point() {}
    point(DB a, DB b) : x(a), y(b) {}
    friend point operator + (const point &a, const point &b) { return point(a.x+b.x, a.y+b.y); }
    friend point operator - (const point &a, const point &b) { return point(a.x-b.x, a.y-b.y); }
    friend bool operator == (const point &a, const point &b) { return cmp(a.x-b.x) == 0 && cmp(a.y-b.y) == 0; }
    friend point operator * (const point &a, const DB &b) { return point(a.x*b, a.y*b); }
    friend point operator * (const DB &a, const point &b) { return point(a*b.x, a*b.y); }
    friend point operator / (const point &a, const DB &b) { return point(a.x/b, a.y/b); }
    DB norm() { return sqrt(sqr(x) + sqr(y)); }
    DB det(const point &a, const point &b) { return a.x*b.y - a.y*b.x; }
    static DB dot(const point &a, const point &b) { return a.x*b.x + a.y*b.y; }
    static DB dist(const point &a, const point &b) { return (a-b).norm(); }
    point rotate_point(const point &p, DB A) {
        DB tx = p.x, ty = p.y;
        return point(tx*cos(A) - ty*sin(A), tx*sin(A) + ty*cos(A));
    }
};

point rotate(const point &p, DB cost ,DB sint) {
    DB x = p.x, y = p.y;
    return point(x*cost - y*sint, x*sint + y*cost);
}

pair<point, point> crosspoint(point ap, DB ar, point bp, DB br) {
    DB d = (ap - bp).norm();
    DB cost = (ar*ar + d*d - br*br) / (2*ar*d);
    DB sint = sqrt(1. - cost*cost);
    point v = (bp - ap) / (bp - ap).norm() * ar;
    return make_pair(ap+rotate(v,cost,-sint), ap+rotate(v,cost,sint));
}

const int maxn = 360000;
const int Hlf = 180000;
const int maxnode = (maxn + 10) << 2;

int tot = 0, las[maxn + 5];
int GetId(int x) {
    if(las[x] == 0) las[x] = ++tot;
    return las[x];
}

int n, m, Rad, rad;
int seg[maxn + 5];
int L[maxn + 5], R[maxn + 5], pos[maxn + 5];
vector<int> vec[maxnode + 5];
DB ans[maxn + 5];

void Upd(int x, int l, int r, int ll, int rr, int v) {
    if(ll <= l && r <= rr) vec[x].PB(v);
    else {
        if(ll <= mid) Upd(lson, l, mid, ll, rr, v);
        if(mid < rr) Upd(rson, mid+1, r, ll, rr, v);
    }
}

set<int> Set;
stack<pii> sta;

void Process(int x, int &now) {
    for(auto v : vec[x]) {
        if(Set.find(v) != Set.end()) continue;
        sta.push( MP(v,x) );
        Set.insert(v), Set.insert(v+Hlf*2);
        auto it = Set.upper_bound(v+Hlf); --it;
        now = max(now, *it - v);
        it = Set.lower_bound(v+Hlf);
        now = max(now, v+Hlf*2 - *it);
    }
}

void RollBack(int x) {
    while(!sta.empty()) {
        if(sta.top().se != x) break;
        int v = sta.top().fi; sta.pop();
        Set.erase(v), Set.erase(v+Hlf*2);
    }
}

inline DB F(point &a, point &b) {
    DB cost = point::dot(a,b) / (a.norm() * b.norm());
    // VERY IMPORTANT!!!
    // FUCKING EPS!!!
    cost = min(cost, (DB)(1.));
    cost = max(cost, (DB)(-1.));
    return acos(cost) * rad;
}

DB Calc(int del) {
    assert(del > 0);
    point p1 = point(Rad,0), p2 = point( cos(pi*del/Hlf), sin(pi*del/Hlf) ) * Rad;
    DB dis = point::dist(p1,p2), lim = sqrt(sqr(Rad)-sqr(rad));
    if(cmp(dis-lim*2) <= 0) return dis;
    pair<point,point> ret1 = crosspoint(p1, lim, point(0,0), rad);
    pair<point,point> ret2 = crosspoint(p2, lim, point(0,0), rad);
    DB res = min( F(ret1.fi, ret2.fi), F(ret1.fi, ret2.se) );
    res = min( res, min( F(ret1.se, ret2.fi), F(ret1.se, ret2.se) ) );
    return res + lim * 2;
}

void Solve(int x, int l, int r, int now) {
    Process(x, now);
    if(l == r) ans[l] = Calc(now);
    else {
        Solve(lson, l, mid, now);
        Solve(rson, mid+1, r, now);
    }
    RollBack(x);
}

int main() {
    scanf("%d%d", &Rad, &rad);
    scanf("%d", &n);
    REP(i,1,n) scanf("%d", seg + i);
    scanf("%d", &m);
    for(int i = 1; i <= n; ++i) {
        int id = GetId(seg[i]);
        L[id] = 0, R[id] = m, pos[id] = seg[i];
    }
    for(int i = 1, o, x; i <= m; ++i) {
        scanf("%d%d", &o, &x);
        if(o == 1) {
            int id = GetId(x);
            L[id] = i, R[id] = m, pos[id] = x;
        }
        else {
            int id = GetId(x);
            R[id] = i-1, las[x] = 0;
        }
    }
    for(int i = 1; i <= tot; ++i) Upd(1, 0, m, L[i], R[i], pos[i]);
    Solve(1, 0, m, 0);
    for(int i = 0; i <= m; ++i) printf("%.10f\n", (double)ans[i]);
    return 0;
}
