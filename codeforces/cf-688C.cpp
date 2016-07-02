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

const int maxn = 100000;

vector<int> G[maxn+10], res[2];

int n, m;
int fa[maxn+10];

bool dfs(int x, int type)
{
	if(!G[x].size()) return true;
	fa[x] = type;
	res[type].push_back(x);
	FOR(i,0,G[x].size())
	{
		int &nex = G[x][i];
		if(fa[nex] == -1)
		{
			if(!dfs(nex, (type+1)%2))
				return false;
		}
		else if(fa[x] == fa[nex])
			return false;
	}
	return true;
}

void init()
{
	int u, v;
	cin >> n >> m;
	mem(fa,-1);
	REP(i,1,m)
	{
		sf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	REP(i,1,n)
		if(fa[i]==-1 && !dfs(i,0))
		{
			pf("-1\n");
			return;
		}
	/*REP(i,1,n) if(!vis[i])
		res1[++top1] = i;*/
	cout << res[0].size() << "\n";
	FOR(i,0,res[0].size())
	{
		if(i) pf(" ");
		pf("%d", res[0][i]);
	}
	pf("\n");
	cout << res[1].size() << "\n";
	FOR(i,0,res[1].size())
	{
		if(i) pf(" ");
		pf("%d", res[1][i]);
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
