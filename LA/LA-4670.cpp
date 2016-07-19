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

const int maxn = 150, max_len = 70;
const int c_size = 26;

int vis[maxn+5];

struct Tire
{
	int top;
	vector<int> cnt[maxn*max_len + 5];
	int nex[maxn*max_len + 5][c_size+5];
	int fail[maxn*max_len+5], last[maxn*max_len+5];

	void clear()
	{
		top = 0;
		cnt[0].clear(); mem(nex[0], 0);
	}

	void insert(int x, char *a, int val)
	{
		if(*a == '\0')
			cnt[x].push_back(val);
		else
		{
			int t = *a - 97;
			if(!nex[x][t])
			{
				nex[x][t] = ++top;
				cnt[top].clear();
				mem(nex[top], 0);
			}
			insert(nex[x][t], a+1, val);
		}
	}

	void AC_build()
	{
		fail[0] = last[0] = 0;
		queue<int> q;
		for(int i=0; i<c_size; ++i) if(int& u = nex[0][i])
		{
			//pf("u = %d\n", u);
			fail[u] = last[u] = 0;
			q.push(u);
		}
		while(!q.empty())
		{
			//pf("adsfasdf\n");
			int x = q.front(); q.pop();
			for(int i=0; i<c_size; ++i) if(int& u = nex[x][i])
			{
				//pf("uu = %d\n", u);
				q.push(u);
				int now = fail[x];
				while(now && !nex[now][i]) now = fail[now];
				fail[u] = nex[now][i];
				/*if(fail[u])
				{
					pf("u = %d, fail[u] = %d\n", u, fail[u]);
				}*/
				last[u] = cnt[fail[u]].size() ? fail[u] : last[fail[u]];
			}
		}
	}

	void find(char *a)
	{
		int len = strlen(a), now = 0;
		for(int i=0; i<len; ++i)
		{
			int t = a[i] - 97;
			while(now && !nex[now][t]) now = fail[now];
			now = nex[now][t];
			if(cnt[now].size()) check(now);
			else if(last[now]) check(last[now]);
			//pf("i = %d, now = %d, t = %d\n", i, now, t);
		}
	}

	void check(int x)
	{
		if(x)
		{
			//pf("fuck\n");
			for(int i=0; i<cnt[x].size(); ++i)
				++vis[cnt[x][i]];
			if(last[x]) check(last[x]);
		}
	}
}AC;

int n;
char arr[maxn+5][max_len+5];
char tar[int(1e6)+5];

void init()
{
	mem(vis, 0); AC.clear();
	REP(i,1,n)
	{
		sf("%s", arr[i]);
		AC.insert(0, arr[i], i);
	}
	AC.AC_build();
	sf("%s", tar);
	AC.find(tar);
	int tot = 0;
	REP(i,1,n) tot = max(tot, vis[i]);
	pf("%d\n", tot);
	REP(i,1,n) if(tot == vis[i])
		pf("%s\n", arr[i]);
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	while(sf("%d", &n), n)
		init();
	return 0;
}
