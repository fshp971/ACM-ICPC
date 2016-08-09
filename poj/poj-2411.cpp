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
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define pii pair<int,int>
#define mem(a,b) memset(a,b,sizeof(a))
#define MP(a,b) make_pair(a,b)
#define sf scanf
#define pf printf

int n, m;
LL f[15][1<<12];

void dfs(int tn, int msk1, int msk2, int col)
{
	if(col == m)
	{
		f[tn][msk1] += f[tn-1][msk2];
		return;
	}
	if(col+1<m)
	{
		int t = (1<<col) + (1<<(col+1));
		dfs(tn, msk1+t, msk2+t, col+2);
	}
	dfs(tn, msk1+(1<<col), msk2, col+1);
	dfs(tn, msk1, msk2+(1<<col), col+1);
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	while(sf("%d%d", &n, &m), n)
	{
		mem(f, 0);
		f[0][(1<<m)-1] = 1;
		REP(i,1,n) dfs(i,0,0,0);
		pf("%lld\n", f[n][(1<<m)-1]);
	}
	return 0;
}
