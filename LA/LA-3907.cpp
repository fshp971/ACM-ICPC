#include<bits/stdc++.h>

using namespace std;

#define LL long long
#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define MP(a,b) make_pair(a,b)
#define pii pair<int,int>
#define sf scanf
#define pf printf

const int maxnode = 1000 * 50, C_Size = 26;

int c_size;

struct Tire
{
	int top;
	int nex[maxnode+5][C_Size+5], fail[maxnode+5];
	int val[maxnode+5];
	bool match[maxnode+5];

	void clear()
	{
		top = 0, match[0] = false, val[0] = -1;
		mem(nex[0], 0);
	}
	
	int c_id(char c){ return c - 'A'; }

	void insert(char *a)
	{
		int len = strlen(a), u = 0;
		for(int i=0; i<len; ++i)
		{
			int t = c_id(a[i]);
			if(!nex[u][t])
			{
				nex[u][t] = (++top);
				match[top] = false;
				val[top] = t;
				mem(nex[top], 0);
			}
			u = nex[u][t];
		}
		match[u] = true;
	}

	void get_fail()
	{
		fail[0] = 0;
		queue<int> q;
		for(int i=0; i<c_size; ++i) if(int &t = nex[0][i])
		{
			fail[t] = 0;
			q.push(t);
		}
		while(!q.empty())
		{
			int x = q.front(); q.pop();
			for(int i=0; i<c_size; ++i)
			{
				int u = nex[x][i];
				if(!u){ nex[x][i] = nex[fail[x]][i]; continue; }
				q.push(u);
				int v = fail[x];
				while(v && !nex[v][i]) v = fail[v];
				fail[u] = nex[v][i];
				match[u] |= match[fail[u]];
			}
		}
	}
}AC;

int n;
char arr[1010];
int dp[maxnode+5], nex_node[maxnode+5];
int vis[maxnode+5];

int dfs(int x, bool &NO)
{
	if(vis[x] == 2) return dp[x];
	if(vis[x] == 1){ NO = true; return 0; }
	vis[x] = 1;
	int t, u;
	dp[x] = 0; nex_node[x] = -1;
	for(int i=c_size-1; i>=0; --i)
	{
		u = AC.nex[x][i];
		if(AC.match[u]) continue;
		t = dfs(u, NO);
		if(NO) return 0;
		if(dp[x] < t)
		{
			dp[x] = t;
			nex_node[x] = u;
		}
	}
	vis[x] = 2;
	return dp[x] = dp[x]+1;
}

void init()
{
	sf("%d%d", &c_size, &n);
	AC.clear();
	REP(i,1,n)
	{
		sf("%s", arr);
		AC.insert(arr);
	}
	AC.get_fail();
	bool NO = false;
	mem(vis, 0);
	dfs(0, NO);
	if(NO || nex_node[0] == -1) printf("No\n");
	else
	{
		for(int i=nex_node[0]; i!=-1; i=nex_node[i])
		{
			pf("%c", AC.val[i]+'A');
		}
		pf("\n");
	}
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int t;
	cin >> t;
	while(t--)
		init();
	return 0;
}
