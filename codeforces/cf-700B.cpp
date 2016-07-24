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

const int maxn = 2e5;

vector<int> G[maxn+5];

int n, kk;
bool mark[maxn+5], vis[maxn+5];

int dfs(int x, LL &ans)
{
	vis[x] = true;
	int nd = 0;
	for(int i=0; i<G[x].size(); ++i)
	{
		if(vis[G[x][i]]) continue;
		nd += dfs(G[x][i], ans);
	}
	ans += nd;
	if(mark[x])
		++nd;
	int rem = kk*2 - nd;
	if(nd > rem)
	{
		int t = (nd-rem) / 2;
		nd -= t*2;
		if(nd > rem) nd -= 2, ++t;
		kk -= t;
	}
	return nd;
}

void init()
{
	int u,v;
	sf("%d%d", &n, &kk);
	REP(i,1,kk*2)
	{
		sf("%d", &u);
		mark[u] = true;
	}
	FOR(i,1,n)
	{
		sf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	LL ans = 0;
	dfs(1, ans);
	cout << ans << "\n";
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	init();
	return 0;
}
