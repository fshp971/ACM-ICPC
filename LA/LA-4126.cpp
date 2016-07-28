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

const int maxnode = 100, c_size = 26;
const int max_dp = 1<<11, maxn = 25;

struct Tire
{
	int top, mask;
	int nex[maxnode+5][c_size+5], val[maxnode+5];
	int fail[maxnode+5], last[maxnode+5];

	void clear()
	{
		top = val[0] = mask = 0;
		mem(nex[0], 0);
	}

	inline int c_id(char c){ return c-'a'; }

	void insert(char *a, int vv)
	{
		int len = strlen(a), u = 0, t;
		for(int i=0; i<len; ++i)
		{
			t = c_id(a[i]);
			if(!nex[u][t])
			{
				nex[u][t] = (++top);
				mem(nex[top], 0);
				val[top] = 0;
			}
			u = nex[u][t];
		}
		if(!val[u])
		{
			val[u] = 1<<(vv-1);
			mask |= val[u];
		}
	}

	void get_fail()
	{
		fail[0] = last[0] = 0;
		queue<int> q;
		for(int i=0; i<c_size; ++i) if(int &t = nex[0][i])
		{
			fail[t] = last[t] = 0;
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
				last[u] = val[fail[u]] ? fail[u] : last[fail[u]];
			}
		}
	}

	void find(int x, int &msk)
	{
		if(x)
		{
			msk |= val[x];
			find(last[x], msk);
		}
	}
}AC;

int n, m;
LL dp[maxnode+5][maxn+5][max_dp+5];
bool vis[maxnode+5][maxn+5][max_dp+5];

LL dfs(int x, int len, int msk)
{
	AC.find(x, msk);
	if(vis[x][len][msk]) return dp[x][len][msk];
	vis[x][len][msk] = true;
	if(len == n) return dp[x][len][msk] = msk == AC.mask ? 1 : 0;
	dp[x][len][msk] = 0;
	for(int i=0; i<c_size; ++i)
	{
		int next = AC.nex[x][i];
		if(!next) next = AC.nex[0][i];
		dp[x][len][msk] += dfs(next, len+1, msk);
	}
	return dp[x][len][msk];
}

void dfs2(int x, char *arr, int top, int msk)
{
	if(top == n)
	{
		arr[top] = '\0';
		pf("%s\n", arr);
		return;
	}
	int u, t;
	for(int i=0; i<c_size; ++i)
	{
		u = AC.nex[x][i];
		if(!u) u = AC.nex[0][i];
		t = msk;
		AC.find(u, t);
		if(!dp[u][top+1][t]) continue;
		arr[top] = i+'a';
		dfs2(u, arr, top+1, t);
	}
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	char arr[30];
	LL ans;
	int cont = 0;
	while(sf("%d%d", &n, &m), n || m)
	{
		AC.clear();
		REP(i,1,m)
		{
			sf("%s", arr);
			AC.insert(arr, i);
		}
		AC.get_fail();
		mem(vis, 0);
		ans = dfs(0, 0, 0);
		pf("Case %d: %lld suspects\n", ++cont, ans);
		if(ans <= 42)
			dfs2(0, arr, 0, 0);
	}
	return 0;
}
