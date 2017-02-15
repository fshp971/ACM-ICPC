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

const int maxn = 1e5, maxnode = 2e5, c_size = 26;

struct PTree
{
	int tot, S_len[2], last[2];
	int len[maxnode+5], fail[maxnode+5];
	int nex[maxnode+5][c_size+2];
	int S[maxnode+5];
	LL num[maxnode+5];

	int newnode(int l)
	{
		len[tot] = l, fail[tot] = 0, num[tot] = 0;
		mem(nex[tot], 0);
		return tot++;
	}

	void init()
	{
		tot = 0;
		last[0] = last[1]  = newnode(0);
		fail[0] = newnode(-1), fail[1] = 0;
		S_len[0] = maxn+2, S_len[1] = S_len[0]-1;
	}

	int getfail(int x, int type)
	{
		S[S_len[0]-1] = S[S_len[1]+1] = -1;
		if(type == 1)
		{
			while(S[S_len[1]-len[x]-1] != S[S_len[1]])
				x = fail[x];
		}
		else
		{
			while(S[S_len[0]+len[x]+1] != S[S_len[0]])
				x = fail[x];
		}
		return x;
	}

	LL add(int w, int type)
	{
		if(type == 1)
		{
			S[++S_len[1]] = w;
			last[1] = getfail(last[1], 1);
		}
		else
		{
			S[--S_len[0]] = w;
			last[0] = getfail(last[0], 0);
		}
		if(nex[last[type]][w] == 0)
		{
			int u = newnode(len[last[type]]+2);
			fail[u] = nex[getfail(fail[last[type]], type)][w];
			num[u] = num[fail[u]]+1;
			nex[last[type]][w] = u;
		}
		last[type] = nex[last[type]][w];
		if(len[last[type]] == S_len[1]-S_len[0]+1)
			last[type^1] = last[type];
		return num[last[type]];
	}
}tree;

int main()
{
	int n, ord;
	LL ans;
	char arr[5];
	while(~sf("%d", &n))
	{
		ans = 0;
		tree.init();
		REP(i,1,n)
		{
			sf("%d", &ord);
			if(ord <= 2)
			{
				sf("%s", arr);
				ans += tree.add(arr[0]-'a', ord-1);
			}
			else if(ord == 3)
				pf("%d\n", tree.tot-2);
			else
				pf("%lld\n", ans);
		}
	}
	return 0;
}
