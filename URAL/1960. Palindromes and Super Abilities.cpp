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

const int maxnode = 1e5, c_size = 26;

struct PTree
{
	int tot, S_len, last, fail[maxnode+5], len[maxnode+5];
	int nex[maxnode+5][c_size+2];
	char S[maxnode+5];

	void init()
	{
		tot = 2, S_len = 0, last = 0;
		fail[0] = 1, S[0] = -1;
		len[0] = 0, len[1] = -1;
		mem(nex[0],0), mem(nex[1],0);
	}

	void add(int w)
	{
		S[++S_len] = w;
		while(S[S_len-len[last]-1] != S[S_len])
			last = fail[last];
		if(nex[last][w] == 0)
		{
			int u = tot++;
			mem(nex[u],0);
			len[u] = len[last]+2;
			int v = fail[last];
			while(S[S_len-len[v]-1] != S[S_len])
				v = fail[v];
			fail[u] = nex[v][w];
			nex[last][w] = u;
		}
		last = nex[last][w];
	}
}tree;

char arr[maxnode+5];

int main()
{
	sf("%s", arr);
	int n = strlen(arr);
	tree.init();
	FOR(i,0,n)
	{
		if(i) pf(" ");
		tree.add(arr[i]-'a');
		pf("%d", tree.tot-2);
	}
	pf("\n");
	return 0;
}
