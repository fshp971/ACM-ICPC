#include<bits/stdc++.h>

using namespace std;

#define LL long long
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define pii pair<int,int>
#define mem(a,b) memset(a,b,sizeof(a))
#define MP(a,b) make_pair(a,b)
#define sf scanf
#define pf printf

const int maxn = 20;

int n;

struct Point
{
	double x, y;
	Point(): x(0), y(0){}
	Point(double _x, double _y){ x = _x, y = _y; }
	void input(){ sf("%lf%lf", &x, &y); }
	Point operator+(const Point &a){ return Point(x+a.x, y+a.y); }
	Point operator-(const Point &a){ return Point(x-a.x, y-a.y); }
	Point operator*(const double a){ return Point(x*a, y*a); }
	double dist(const Point &a)
	{
		return sqrt((x-a.x)*(x-a.x) + (y-a.y)*(y-a.y));
	}
}aa[maxn+5], g1, g2;

double calc(Point pt, Point a, Point b, double R)
{
	double l = 0, r = 1;
	Point c;
	while(r-l > 1e-10)
	{
		double mid = (l+r)/2;
		c = a + (b-a) * mid;
		if(pt.dist(c) <= R) l = mid;
		else r = mid;
	}
	return l;
}

bool check(double R)
{
	for(int i=0; i<n; ++i)
	{
		if(g1.dist(aa[i])<=R && g1.dist(aa[i+1])<=R) continue;
		if(g2.dist(aa[i])<=R && g2.dist(aa[i+1])<=R) continue;
		if(g1.dist(aa[i]) > R) swap(g1, g2);
		if(g1.dist(aa[i]) > R) return false;
		if(g2.dist(aa[i+1]) > R) return false;
		if(calc(g1, aa[i], aa[i+1], R) + calc(g2, aa[i+1], aa[i], R) < 1)
			return false;
	}
	return true;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	sf("%d", &n);
	REP(i,1,n) aa[i].input();
	aa[0] = aa[n];
	g1.input(); g2.input();
	double l = 0, r = 10000;
	while(r-l > 1e-5)
	{
		double mid = (l+r)/2;
		if(check(mid)) r = mid;
		else l = mid;
	}
	pf("%.3lf\n", l);
	return 0;
}
