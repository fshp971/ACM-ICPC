#include<bits/stdc++.h>

using namespace std;

#define LL long long
#define MP(a,b) make_pair(a,b)
#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define pii pair<int,int>
#define pLL pair<LL, LL>
#define sf scanf
#define pf printf

LL two[65];

multimap< pLL, LL > road;

int cal_dep(LL x)
{
	int dep = 0;
	while(two[dep+1] <= x) ++dep;
	return dep;
}

void divd(pLL &aa, pLL &bb, LL x, LL y)
{
	if(x < y) swap(x, y);
	int depx = cal_dep(x), depy = cal_dep(y);
	//pf("x = %lld, depx = %d, y = %lld, depy = %d\n", x, depx, y, depy);
	LL tx = x, ty = y;
	while(depx > depy)
	{
		 tx /= 2;
		 --depx;
	}
	while(tx != ty)
		tx /= 2, ty /= 2;
	aa.first = x; aa.second = tx;
	bb.first = y; bb.second = ty;
	return;
}

LL sta[100];

LL check(pLL aa)
{
	LL res = 0;
	int top = 0;
	map< pLL, LL >::iterator it;
	for(it = road.begin(); it != road.end(); ++it)
	{
		pLL bb = it->first;
		LL tax = aa.first, tay = aa.second, tbx = bb.first, tby = bb.second;
		int dpax = cal_dep(aa.first), dpay = cal_dep(aa.second);
		int dpbx = cal_dep(bb.first), dpby = cal_dep(bb.second);
		if(dpax <= dpby || dpbx <= dpay)
			continue;
		//pf("flag\n");
		//pf("flag0: dpax = %d, dpay = %d, dpbx = %d, dpby = %d\n", dpax, dpay, dpbx, dpby);
		if(dpax > dpbx){ swap(dpax, dpbx); swap(tax, tbx); }
		//pf("flag1: tax = %lld, tbx = %lld\n", tax, tbx);
		//if(dpay > dpby){ swap(dpay, dpby); swap(tay, tby); }
		int limy = max(dpby, dpay);
		while(dpbx > dpax)
		{
			tbx /= 2;
			--dpbx;
		}
		//pf("flag2: tax = %lld, tbx = %lld\n", tax, tbx);
		bool fg = (tbx == tax);
		while(dpbx > limy)
		{
			if(fg) res += it->second;
			tbx /= 2, tax /= 2;
			--dpax, --dpbx;
			if(tbx == tax) fg = true;
			//pf("tax = %lld, tbx = %lld\n", tax, tbx);
			
		}
		//pf("res = %lld\n", res);
	}
	//pf("\n");
	return res;
}

void init()
{
	two[1] = 1;
	REP(i,2,61) two[i] = two[i-1] * 2;
	//cout << two[61] << endl;
	int que, ord;
	LL u, v, w;
	pLL aa, bb;
	cin >> que;
	REP(i,1,que)
	{
		sf("%d", &ord);
		if(ord == 1)
		{
			cin >> u >> v >> w;
			divd(aa, bb, u, v);
			//pf("aa.first = %lld, aa.second = %lld, bb.first = %lld, bb.second = %lld\n", aa.first, aa.second, bb.first, bb.second);
			road.insert( MP(aa, w) );
			road.insert( MP(bb, w) );
		}
		else
		{
			cin >> u >> v;
			divd(aa, bb, u, v);
			LL ans = check(aa) + check(bb);
			cout << ans << "\n";
		}
	}
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	init();
	return 0;
}
