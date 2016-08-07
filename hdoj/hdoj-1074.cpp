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

int n, ddl[20], cost[20];
char name[20][105];

int Mask;
int f[1<<16], nex[1<<16];
bool vis[1<<16];

int dfs(int msk, int day)
{
	if(vis[msk]) return f[msk];
	vis[msk] = true;
	if(msk == Mask) return f[msk] = 0;
	int tmp;
	f[msk] = 1<<30;
	for(int i=0; i<n; ++i)
	{
		if(msk & (1<<i)) continue;
		tmp = max(0, cost[i]+day-ddl[i]) + dfs(msk+(1<<i), cost[i]+day);
		if(tmp < f[msk])
		{
			f[msk] = tmp;
			nex[msk] = i;
		}
	}
	return f[msk];
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int T;
	sf("%d", &T);
	while(T--)
	{
		sf("%d", &n);
		Mask = (1<<n) - 1;
		for(int i=0; i<n; ++i)
			sf("%s%d%d", name[i], ddl+i, cost+i);
		mem(vis, 0);
		dfs(0, 0);
		pf("%d\n", f[0]);
		for(int msk=0; msk!=Mask; msk += 1<<nex[msk])
			pf("%s\n", name[nex[msk]]);
	}
	return 0;
}
