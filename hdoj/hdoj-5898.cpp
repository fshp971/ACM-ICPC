#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<queue>
#include<utility>
#include<map>
#include<set>
#include<bitset>

using namespace std;

#define LL long long
#define MP make_pair
#define mem(a,b) memset(a,b,sizeof(a))
#define pii pair<int,int>
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define sf scanf
#define pf printf

int n;
int number[25];
LL f[25][2][2];

LL dfs(int poi, int type1, int type2, int flag, int fg2)
{
	if(poi == 0)
	{
		if(!flag) return 0;
		if(type2) return 0;
		return 1;
	}
	if(flag==2 && f[poi][type1][type2] != -1) return f[poi][type1][type2];
	int range = (fg2 || flag==1) ? number[poi] : 9;
	LL res = 0;
	for(int i=0; i<=range; ++i)
	{
		if(i%2 == type1)
		{
			if(flag == 0)
			{
				if(!i)
					res += dfs(poi-1, type1, type2, 0, 0);
				else if(fg2)
					res += dfs(poi-1, type1, type2^1, i == number[poi] ? 1 : 2, 0);
				else res += dfs(poi-1, type1, type2^1, 2, 0);
			}
			else if(flag == 1)
				res += dfs(poi-1, type1, type2^1, i == number[poi] ? 1 : 2, 0);
			else res += dfs(poi-1, type1, type2^1, 2, 0);
		}
		else
		{
			if(flag == 0)
			{
				if(!i) res += dfs(poi-1, type1, type2, 0, 0);
				continue;
			}
			if(type2) continue;
			if(flag == 1)
				res += dfs(poi-1, type1^1, type1^1, i == number[poi] ? 1 : 2, 0);
			else
				res += dfs(poi-1, type1^1, type1^1, 2, 0);
		}
	}
	if(flag==2) f[poi][type1][type2] = res;
	return res;
}

LL calc(LL x)
{
	if(!x) return 0;
	int top = 0;
	while(x) number[++top] = x%10, x /= 10;
	return dfs(top, 0, 1, 0, 1) + dfs(top, 1, 0, 0, 1);
}

int main()
{
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	mem(f, -1);
	int T;
	LL l, r;
	sf("%d", &T);
	for(int t=1; t<=T; ++t)
	{
		sf("%lld%lld", &l, &r);
		pf("Case #%d: %lld\n", t, calc(r) - calc(l-1));
	}
	return 0;
}
