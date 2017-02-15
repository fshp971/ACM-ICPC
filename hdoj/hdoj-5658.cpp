#include<bits/stdc++.h>

using namespace std;

#define LL long long
#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define pii pair<int,int>
#define sf scanf
#define pf printf

const int maxn = 1000, c_size = 26;

struct PTree
{
	int tot, S_len, last;
	int len[maxn+5], fail[maxn+5];
	int nex[maxn+5][c_size+2];
	int S[maxn+5];

	int newnode(int l)
	{
		len[tot] = l, fail[tot] = 0;
		mem(nex[tot],0);
		return tot++;
	}

	void init()
	{
		tot = 0, S_len = 0, last = 0;
		newnode(0), newnode(-1);
		fail[0] = 1, S[0] = -1;
	}

	int getfail(int x)
	{
		while(S[S_len-len[x]-1] != S[S_len])
			x = fail[x];
		return x;
	}

	void add(int w)
	{
		S[++S_len] = w;
		last = getfail(last);
		if(!nex[last][w])
		{
			int u = newnode(len[last]+2);
			fail[u] = nex[getfail(fail[last])][w];
			nex[last][w] = u;
		}
		last = nex[last][w];
	}
}tree;

int n, m, ans[maxn+5][maxn+5];
char arr[maxn+5];

int main()
{
	int T, l, r;
	sf("%d", &T);
	while(T--)
	{
		sf("%s", arr);
		n = strlen(arr);
		for(int i=1; i<=n; ++i)
		{
			tree.init();
			for(int k=i; k<=n; ++k)
				tree.add(arr[k-1]-'a'), ans[i][k] = tree.tot-2;
		}
		sf("%d", &m);
		for(int i=1; i<=m; ++i)
		{
			sf("%d%d", &l, &r);
			pf("%d\n", ans[l][r]);
		}
	}
	return 0;
}
