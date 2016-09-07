#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<queue>
#include<string>
#include<vector>
#include<utility>
#include<map>
#include<set>

using namespace std;

#define LL long long
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define pii pair<int,int>
#define MP(a,b) make_pair(a,b)
#define mem(a,b) memset(a,b,sizeof(a))
#define sf scanf
#define pf printf

const int maxn = 40;

int f[maxn+5][2];
int number[maxn+5];

void dfs(int poi, int rem)
{
	if(!poi) return;
	if(rem <= f[poi][0])
	{
		number[poi] = 0;
		dfs(poi-1, rem);
	}
	else
	{
		number[poi] = 1;
		rem -= f[poi][0];
		dfs(poi-1, rem);
	}
}

int main()
{
	f[1][0] = f[1][1] = 1;
	REP(i,2,maxn)
	{
		f[i][0] = f[i-1][1] + f[i-1][0];
		f[i][1] = f[i-1][0];
	}
	//REP(i,1,maxn) //pf("f[%d][%d] = %d\nf[%d][%d] = %d\n", i, 0, f[i][0], i, 1, f[i][1]);
	//	pf("f[%d][%d] = %d\n", i, 1, f[i][1]);

	int T, n, len;
	sf("%d", &T);
	while(T--)
	{
		sf("%d", &n);
		len = 1;
		while(n >= f[len][1])
			n -= f[len++][1];
		if(!n) n += f[--len][1];
		number[len] = 1;
		//pf("len = %d, n = %d\n", len, n);
		dfs(len-1, n);
		for(int i= len; i>=1; --i) pf("%d", number[i]);
		pf("\n");
	}
	return 0;
}
