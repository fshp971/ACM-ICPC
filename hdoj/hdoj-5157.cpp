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

const int maxn = 1e5, c_size = 26;

struct PTree
{
	int tot, S_len, last;
	LL num[maxn+5];
	int len[maxn+5], fail[maxn+5];
	int nex[maxn+5][c_size+2];
	int S[maxn+5];

	void init()
	{
		tot = 2, S_len = 0, last = 0;
		last = 0, S[0] = -1, fail[0] = 1;
		len[0] = 0, len[1] = -1;
		num[0] = num[1] = 0;
		mem(nex[0],0), mem(nex[1],0);
	}

	int add(int w)
	{
		S[++S_len] = w;
		while(S[S_len-len[last]-1] != S[S_len])
			last = fail[last];
		if(!nex[last][w])
		{
			int u = tot++;
			mem(nex[u],0);
			len[u] = len[last]+2;
			int v = fail[last];
			while(S[S_len-len[v]-1] != S[S_len])
				v = fail[v];
			fail[u] = nex[v][w];
			num[u] = num[fail[u]]+1;
			nex[last][w] = u;
		}
		last = nex[last][w];
		return num[last];
	}
}tree;

char arr[maxn+5];
LL sum[maxn+5];

int main()
{
	int n;
	LL ans;
	while(~sf("%s", arr))
	{
		n = strlen(arr);
		tree.init();
		sum[n+1] = 0;
		for(int i=n; i>=1; --i)
			sum[i] = sum[i+1] + tree.add(arr[i-1]-'a');
		ans = 0;
		tree.init();
		for(int i=1; i<=n; ++i)
			ans += sum[i+1] * tree.add(arr[i-1]-'a');
		pf("%lld\n", ans);
	}
	return 0;
}
