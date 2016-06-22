#include<bits/stdc++.h>

using namespace std;

#define LL long long
#define MP(a,b) make_pair(a,b)
#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define pii pair<int,int>
#define sf scanf
#define pf printf
#define pdd pair<double,double>

const double PI = acos(-1.0);
const int maxn = 1000000;

struct Line
{
	LL A, B, C;
	void init(LL x1, LL y1, LL x2, LL y2)
	{
		A = y1 - y2;
		B = -(x1 - x2);
		C = x1*y2 - x2*y1;
	}
	double dist(double x, double y)
	{
		return fabs(x*A + y*B + C) / sqrt(pow(A, 2.0) + pow(B, 2.0));
	}
	int type(LL x, LL y)
	{
		LL tmp = x*A + y*B + C;
		if(tmp > 0) return 1;
		else if(tmp < 0) return -1;
		return 0;
	}
};

int n;
pii point[maxn+5], p0;

double p_dis(pdd a, pdd b)
{
	return sqrt( pow(a.first-b.first, 2.0) + pow(a.second-b.second, 2.0) );
}

void init()
{
	cin >> n >> p0.first >> p0.second;
	double r1 = 100000000.0, r2 = -r1;
	REP(i,1,n)
	{
		int a, b;
		sf("%d%d", &a, &b);
		point[i] = MP(a, b);
		//point[i] = MP((double)a, (double)b);
		double dis = p_dis(p0, point[i]);
		r1 = min(r1, dis); r2 = max(r2, dis);
	}
	point[0] = point[n];
	REP(i,1,n)
	{
		Line tl, tl2;
		tl.init(point[i-1].first, point[i-1].second, point[i].first, point[i].second);
		tl2.A = tl.B; tl2.B = -tl.A;
		tl2.C = -(tl2.A * p0.first + tl2.B * p0.second);
		double dis = tl.dist(p0.first, p0.second);
		int tp1 = tl2.type(point[i-1].first, point[i-1].second);
		int tp2 = tl2.type(point[i].first, point[i].second);
		if((tp1==1 && tp2==1) || (tp1==-1 && tp2==-1)) continue;
		r1 = min(r1, dis);
	}
	double ans = PI * (pow(r2, 2.0) - pow(r1, 2.0));
	pf("%.18f\n", ans);
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	init();
	return 0;
}
