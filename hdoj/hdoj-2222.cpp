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

const int maxn = 500000;
const int c_size = 26;

int n;
int vis[10010];

struct Tire
{
	int top;
	int cnt[maxn+5], sum[maxn+5], nex[maxn+5][c_size+2];
	int fail[maxn+5], last[maxn+5];
	void clear()
	{
		top = 0;
		mem(nex[0], 0), mem(cnt, 0);
	}
	
	void insert(int x, char *a, int type)
	{
		if(*a == '\0')
		{
			if(cnt[x])
				++sum[x];
			else cnt[x] = type, sum[x] = 1;
		}
		else
		{
			int t = *a - 97;
			if(!nex[x][t])
			{
				nex[x][t] = ++top;
				mem(nex[top], 0);
			}
			insert(nex[x][t], a+1, type);
		}
	}

	void AC_build()
	{
		queue<int> q;
		fail[0] = last[0] = 0;
		for(int i=0; i<c_size; ++i) if(nex[0][i])
		{
			q.push(nex[0][i]);
			fail[nex[0][i]] = last[nex[0][i]] = 0;
		}
		while(!q.empty())
		{
			int x = q.front(); q.pop();
			for(int i=0; i<c_size; ++i) if(nex[x][i])
			{
				q.push(nex[x][i]);
				int v = fail[x];
				while(v && !nex[v][i]) v = fail[v];
				fail[nex[x][i]] = nex[v][i];
				last[nex[x][i]] = cnt[fail[nex[x][i]]] ? fail[nex[x][i]] : last[fail[nex[x][i]]];
			}
		}
	}

	void find(char *a)
	{
		int len = strlen(a), now = 0;
		for(int i=0; i<len; ++i)
		{
			int x = a[i] - 97;
			while(now && !nex[now][x]) now = fail[now];
			now = nex[now][x];
			if(cnt[now]) check(now);
			else check(last[now]);
		}
	}

	void check(int x)
	{
		if(x)
		{
			vis[cnt[x]] = sum[x];
			check(last[x]);
		}
	}
}AC;

char arr[1000010];

void init()
{
	AC.clear();
	cin >> n;
	REP(i,1,n)
	{
		sf("%s", arr);
		AC.insert(0, arr, i);
	}
	AC.AC_build();
	mem(vis, 0);
	sf("%s", arr);
	AC.find(arr);
	int ans = 0;
	REP(i,1,n) if(vis[i]) ans += vis[i];
	pf("%d\n", ans);
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
