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

const int maxn = 20;
const int walk[8][2] = {{1,0}, {0,1}, {-1,0}, {0,-1}, {1,1}, {1,-1}, {-1,1}, {-1,-1}};

struct Point {
    LL x, y;
    Point() {}
    Point(LL _x, LL _y) { x = _x, y = _y; }
    Point operator-(const Point &a) { return Point(x-a.x, y-a.y); }
    Point operator*(const LL a) { return Point(x*a, y*a); }
    LL operator*(const Point &a) { return x*a.x + y*a.y; }
    LL operator^(const Point &a) { return x*a.y - y*a.x; }
    bool operator!=(const Point &a) { return x!=a.x || y!=a.y; }
    bool operator==(const Point &a) { return x==a.x && y==a.y; }
};
typedef pair<Point, Point> LSG;

char mmp[maxn + 5][maxn + 5];
int dist[maxn + 5][maxn + 5];
bool inq[maxn + 5][maxn + 5];
queue<int> que;

bool In(LSG& l0, Point p0) {
    Point v1 = l0.se - l0.fi, v2 = p0 - l0.fi;
    return (v1^v2) > 0;
}

bool OnSeg(LSG& l0, Point& p0) {
    Point v1 = l0.fi - p0, v2 = l0.se - p0;
    return (v1^v2) == 0 && (v1*v2) < 0;
}

bool Inter(LSG &l1, LSG &l2) {
    Point v0, v1, v2;

    v0 = l2.se - l2.fi, v1 = l1.se - l2.fi, v2 = l1.fi - l2.fi;
    LL res1 = v0^v1, res2 = v0^v2;
    if( (res1<=0 && res2<=0) || (res1>=0 && res2>=0) )
        return false;

    v0 = l1.se - l1.fi, v1 = l2.se - l1.fi, v2 = l2.fi - l1.fi;
    res1 = v0^v1, res2 = v0^v2;
    if( (res1<=0 && res2<=0) || (res1>=0 && res2>=0) )
        return false;

    return true;
}

bool Spj(LSG &l0, LSG &l1, LSG &l2) {
    if(!OnSeg(l2, l0.se)) return false;
    return OnSeg(l1, l0.fi) || OnSeg(l0, l1.fi) || (l0.fi == l1.fi);
}

int main() {
    int n;
    char str[50];
    while(~scanf("%d", &n)) {
        double x1, y1, x2, y2, x3, y3;
        scanf("%lf%lf%lf%lf%lf%lf", &x1, &y1, &x2, &y2, &x3, &y3);
        x1*=100, y1*=100, x2*=100, y2*=100, x3*=100, y3*=100;
        Point v1 = Point(x2,y2) - Point(x1,y1), v2 = Point(x3,y3) - Point(x1,y1);
        if((v1^v2) < 0) swap(x2,x3), swap(y2,y3);
        LSG l1 = MP( Point(x1,y1), Point(x2,y2) );
        LSG l2 = MP( Point(x2,y2), Point(x3,y3) );
        LSG l3 = MP( Point(x3,y3), Point(x1,y1) );
        for(int k = n-1; k >= 0; --k) {
            scanf("%s", str);
            for(int i = 0; i < n; ++i)
                mmp[i][k] = str[i];
        }
        if(mmp[0][0] == '#') { puts("-1"); continue; }
        mem(dist, 0x7f);
        que.push(0), dist[0][0] = 0, inq[0][0] = 1;
        while(!que.empty()) {
            int val = que.front(); que.pop();
            int x = val/100, y = val%100; inq[x][y] = 0;
            for(int i = 0; i < 8; ++i) {
                int xx = x + walk[i][0];
                int yy = y + walk[i][1];
                if(xx < 0 || xx >= n || yy < 0 || yy >= n) continue;
                if(mmp[xx][yy] == '#' || dist[x][y]+1 >= dist[xx][yy]) continue;
                if( In(l1,Point(xx,yy)*100) && In(l2,Point(xx,yy)*100) && In(l3,Point(xx,yy)*100) ) continue;

                LSG l0 = MP( Point(x,y)*100, Point(xx,yy)*100 );
                if(Inter(l0,l1) || Inter(l0,l2) || Inter(l0,l3)) continue;

                if(Spj(l0,l1,l2) || Spj(l0,l2,l3) || Spj(l0,l3,l1)) continue;
                swap(l0.fi, l0.se);
                if(Spj(l0,l1,l2) || Spj(l0,l2,l3) || Spj(l0,l3,l1)) continue;

                dist[xx][yy] = dist[x][y] + 1;
                if(!inq[xx][yy]) inq[xx][yy] = 1, que.push(xx*100+yy);
            }
        }
        printf("%d\n", dist[n-1][n-1]>100000 ? -1 : dist[n-1][n-1]);
    }
    return 0;
}
