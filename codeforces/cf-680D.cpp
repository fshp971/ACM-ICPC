#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<queue>
#include<string>
#include<utility>
#include<map>
#include<set>
#include<vector>

using namespace std;

#define LL long long
#define MP(a,b) make_pair(a,b)
#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define pii pair<int,int>
#define sf scanf
#define pf printf

#define pll pair<long long, long long>

pll ans;
bool operator<(const pll &a, const pll &b)
{
	return a.first == b.first ? a.second < b.second : a.first < b.first;
}

LL tar3(LL x){ return x*x*x; }

void cal(LL n, pll dat)
{
	if(!n)
	{
		if(ans < dat) ans = dat;
		return;
	}
	LL x = 0, tt;
	while(tar3(x+1) <= n) ++x;
	tt = tar3(x);
	cal(n - tt, MP(dat.first+1, dat.second+tt));
	if(x>1)
	{
		cal( tar3(x)-1 - tar3(x-1), MP(dat.first+1, dat.second+tar3(x-1)) );
	}
	return;
}

void init()
{
	LL m;
	ans = MP((LL)0, (LL)0);
	cin >> m;
	cal(m, MP((LL)0, (LL)0));
	cout << ans.first << " " << ans.second << endl;
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	init();
	return 0;
}
