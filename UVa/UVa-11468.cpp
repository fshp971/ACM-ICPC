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

const int maxk = 20, max_len = 20, c_size = 62;
const int max_L = 100;

struct Tire
{
	int top;
	int nex[maxk*max_len+5][c_size+5];
	int fail[maxk*max_len+5];
	bool cnt[maxk*max_len+5];
	double prob[c_size+5];
	bool vis[maxk*max_len+5][max_L+5];
	double dis[maxk*max_len+5][max_L+5];


	void clear()
	{
		top = 0;
		mem(cnt, 0);
		mem(nex[0], 0);
		mem(vis, 0);
	}

	int c_id(char a)
	{
		if('a'<=a && a<='z') return a-97;
		if('A'<=a && a<='Z') return a-65+26;
		return a-48+26+26;
	}

	void insert(int x, char *a)
	{
		if(*a == '\0')
			cnt[x] = true;
		else
		{
			int t = c_id(*a);
			if(!nex[x][t])
			{
				nex[x][t] = ++top;
				mem(nex[top], 0); cnt[top] = false;
			}
			insert(nex[x][t], a+1);
		}
	}

	void AC_build()
	{
		queue<int> q;
		fail[0] = 0;
		for(int i=0;i<c_size;++i) if(int &u = nex[0][i])
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
				if(!u){ u = nex[fail[x]][i]; continue; }
				q.push(u);
				int v = fail[x];
				while(v && !nex[v][i]) v = fail[v];
				fail[u] = nex[v][i];
				cnt[u] |= cnt[fail[u]];
			}
		}
	}

	void get_prob()
	{
		mem(prob, 0);
		int t;
		double tmp;
		char ord[3];
		sf("%d", &t);
		REP(i,1,t)
		{
			sf("%s%lf", ord, &tmp);
			prob[c_id(ord[0])] = tmp;
		}
	}

	double dfs(int x, int rem)
	{
		if(!rem) return 1.0;
		if(vis[x][rem]) return dis[x][rem];
		dis[x][rem] = 0;
		vis[x][rem] = true;
		for(int i=0; i<c_size; ++i) if(cnt[nex[x][i]]==false && prob[i]>0.0)
		{
			dis[x][rem] += prob[i] * dfs(nex[x][i], rem-1);
		}
		//pf("dis[%d][%d] = %f\n", x, rem, dis[x][rem]);
		return dis[x][rem];
	}
}AC;

double init()
{
	int n;
	sf("%d", &n);
	char aa[max_len+5];
	AC.clear();
	REP(i,1,n)
	{
		sf("%s", aa);
		AC.insert(0, aa);
	}
	AC.AC_build();
	AC.get_prob();
	int l;
	sf("%d", &l);
	return AC.dfs(0, l);
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int t;
	cin >> t;
	for(int i=1;i<=t;++i)
		pf("Case #%d: %.6f\n", i, init());
	return 0;
}
