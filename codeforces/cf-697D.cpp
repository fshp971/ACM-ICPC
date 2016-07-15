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

const int maxn = 1e5;

int n, par[maxn+5], sum[maxn+5];
double res[maxn+5];

vector<int> G[maxn+5];

int dfs1(int x)
{
	sum[x] = 1;
	for(int i=0; i<G[x].size(); ++i)
		sum[x] += dfs1(G[x][i]);
	return sum[x];
}

void dfs2(int x)
{
	for(int i=0; i<G[x].size(); ++i)
	{
		int &nex = G[x][i];
		int tmp = sum[x] - sum[nex] - 1;
		res[nex] = res[x] + 1.0 + (double)tmp / 2.0;
		dfs2(nex);
	}
	return;
}

void init()
{
	cin >> n;
	REP(i,2,n)
	{
		sf("%d", par+i);
		G[par[i]].push_back(i);
	}
	dfs1(1);
	res[1] = 1.0;
	dfs2(1);
	REP(i,1,n)
	{
		if(i>1) pf(" ");
		pf("%.8f", res[i]);
	}
	pf("\n");
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	init();
	return 0;
}
