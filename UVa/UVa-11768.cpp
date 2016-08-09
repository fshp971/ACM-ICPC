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

void ex_gcd(LL a, LL b, LL &d, LL &x, LL &y)
{
	if(!b) d = a, x = 1, y = 0;
	else{ ex_gcd(b, a%b, d, y, x); y -= x*(a/b); }
}

int cal(double x1, double y1, double x2, double y2)
{
	LL tx1 = x1*10, ty1 = y1*10, tx2 = x2*10, ty2 = y2*10;
	if(tx1 == tx2)
	{
		if(tx1%10) return 0;
		int tl = ceil(min(y1, y2)), tr = floor(max(y1, y2));
		return max(0, tr-tl+1);
	}
	if(ty1 == ty2)
	{
		if(ty1%10) return 0;
		int tl = ceil(min(x1, x2)), tr = floor(max(x1, x2));
		return max(0, tr-tl+1);
	}
	LL aa = (ty1-ty2)*10, bb = (tx2-tx1)*10, cc = (tx2*ty1 - tx1*ty2);
	LL gg, xx, yy;
	ex_gcd(aa, bb, gg, xx, yy);
	if(cc%gg) return 0;
	aa /= gg, bb /= gg, cc /= gg;
	xx *= cc, yy *= cc;
	if(bb<0) bb = -bb;
	xx = xx - bb * ((LL)(xx - x1) / bb);
	while(xx >= x1) xx -= bb;
	while(xx < x1) xx += bb;
	int ans = 0;
	while(xx <= x2)
	{
		++ans;
		xx += bb;
	}
	return ans;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int T;
	double x1, x2, y1, y2;
	sf("%d", &T);
	while(T--)
	{
		sf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
		if(x1>x2){ swap(x1,x2); swap(y1,y2); }
		pf("%d\n", cal(x1, y1, x2, y2));
	}
	return 0;
}
