#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<iostream>
#include<algorithm>
#include<string>
#include<queue>
#include<vector>
#include<utility>
#include<map>
#include<set>

using namespace std;

#define LL long long
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define pii pair<int,int>
#define mem(a,b) memset(a,b,sizeof(a))
#define MP(a,b) make_pair(a,b)
#define sf scanf
#define pf printf

const int maxn = 31;

int number[maxn+5], top;
int f[maxn+5][maxn+5];

int dfs(int poi, int lim, int flag)
{
	if(poi == 0)
		return flag == 2 ? 0 : 1;
	if(!flag && f[poi][lim]!=-1) return f[poi][lim];
	int res = 0;
	int range = flag == 1 ? number[poi] : 1;
	if(!lim) range = 0;
	for(int i=0; i<=range; ++i)
	{
		if(flag == 0)
			res += dfs(poi-1, lim-i, 0);
		else if(flag == 1)
		{
			if(i < number[poi])
				res += dfs(poi-1, lim-i, 0);
			else res += dfs(poi-1, lim-i, 1);
		}
		else
		{
			if(!i)
				res += dfs(poi-1, (poi-1)/2, 2);
			else res += dfs(poi-1, lim-i, poi == top ? 1 : 0);
		}
	}
	if(!flag) f[poi][lim] = res;
	return res;
}

int calc(int x)
{
	if(x == 0) return 0;
	//int top = 0;
	top = 0;
	while(x) number[++top] = x%2, x /= 2;
	return dfs(top, top/2, 2);
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int l, r;
	mem(f, -1);
	sf("%d%d", &l, &r);
	pf("%d\n", calc(r) - calc(l-1));
	return 0;
}
