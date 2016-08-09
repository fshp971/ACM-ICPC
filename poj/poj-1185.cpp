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

int n, m;
int sta[65], top;
int f[105][65][65];

void dfs(int type, int col)
{
	if(col == 10){ sta[++top] = type; return; }
	dfs(type, col+1);
	if(!(type&(1<<(max(0,col-1)))) && !(type&(1<<( max(0,col-2)))))
		dfs(type+(1<<col), col+1);
}

int bitcnt(int x)
{
	int res = 0;
	while(x) res += x&1, x >>= 1;
	return res;
}

int main()
{
	top = 0;
	dfs(0, 0);
	sort(sta+1, sta+1+top);
	sf("%d%d", &n, &m);
	char aa[15];
	int tmp;
	mem(f,0);
	REP(i,1,n)
	{
		sf("%s", aa);
		tmp = 0;
		FOR(k,0,m) if(aa[k] == 'P') tmp += 1<<k;
		for(int k=1; k<=top && sta[k]<(1<<m); ++k)
		{
			if((~tmp) & sta[k]) continue;
			for(int j=1; j<=top && sta[j]<(1<<m); ++j)
			{
				if(sta[j] & sta[k]) continue;
				for(int l=1; l<=top && sta[l]<(1<<m); ++l)
				{
					if(sta[l]&sta[k] || sta[l]&sta[j]) continue;
					f[i][k][j] = max(f[i][k][j], f[i-1][j][l] + bitcnt(sta[k]));
				}
			}
		}
	}
	int ans = 0;
	for(int i=1; i<=top && sta[i]<(1<<m); ++i)
		for(int k=1; k<=top && sta[k]<(1<<m); ++k)
			ans = max(ans, f[n][i][k]);
	pf("%d\n", ans);
	return 0;
}
