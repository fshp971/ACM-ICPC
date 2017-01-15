#include<bits/stdc++.h>

using namespace std;

#define LL long long
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define mem(a,b) memset(a,b,sizeof(a))
#define MP make_pair
#define pii pair<int,int>
#define sf scanf
#define pf printf

const int maxnode = 200000;
const int c_size = 2;

int nx[maxnode+5], dist[maxnode+5];
bool vis[maxnode+5];

struct AC_Auto
{
	int top;
	int fail[maxnode+5];
	int nex[maxnode+5][c_size+2];
	bool match[maxnode+5];

	void clear() { top = match[0] = 0; mem(nex[0], 0); }
	int get_id(char c) { return c-48; }

	void insert(char *a)
	{
		int len = strlen(a), u = 0, c;
		for(int i=0; i<len; ++i)
		{
			c = get_id(a[i]);
			if(!nex[u][c])
			{
				nex[u][c] = ++top;
				match[top] = 0;
				mem(nex[top], 0);
			}
			u = nex[u][c];
		}
		match[u] = 1;
	}

	void build()
	{
		queue<int> q;
		for(int i=0; i<c_size; ++i) if(int &u = nex[0][i])
		{
			q.push(u);
			fail[u] = 0;
		}
		while(!q.empty())
		{
			int x = q.front(); q.pop();
			for(int i=0; i<c_size; ++i)
			{
				int &u = nex[x][i];
				if(!u) { u = nex[fail[x]][i]; continue; } //补上所有不存在的边
				q.push(u);
				int v = fail[x];
				while(v && !nex[v][i]) v = fail[v];
				fail[u] = nex[v][i];
				match[u] |= match[fail[u]]; //计算出所有终止结点
			}
		}
	}

	int dfs(int x)
	{
		if(match[x]) return 0;
		if(vis[x]) return -1;
		vis[x] = 1;
		int dd[2];
		for(int i=0; i<2; ++i)
		{
			dd[i] = dfs(nex[x][i]);
			if(dd[i] == -1) return -1;
		}
		if(dd[1] > dd[0])
			nx[x] = 1, dist[x] = dd[1];
		else nx[x] = 0, dist[x] = dd[0];
		vis[x] = 0;
		return dist[x]+1;
	}

	void output()
	{
		int now = 0;
		while(dist[now])
		{
			pf("%d", nx[now]);
			now = nex[now][nx[now]];
		}
		pf("\n");
	}
}AC;

int n;
char arr[maxnode+5];

int main()
{
	sf("%d", &n);
	AC.clear();
	REP(i,1,n)
	{
		sf("%s", arr);
		AC.insert(arr);
	}
	AC.build();
	mem(vis, 0); mem(nx, 0); mem(dist, 0);
	if(AC.dfs(0) == -1)
		pf("-1\n");
	else
		AC.output();
	return 0;
}
