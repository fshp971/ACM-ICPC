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

const int md = 1e9 + 7;
const int maxn = 1e6, c_size = 26;

int sum1[maxn+5], sum2[maxn+5];
char arr[maxn+5];

struct PTree
{
	int tot, last, S_len;
	char S[maxn+5];
	int len[maxn+5], fail[maxn+5], poi[maxn+5];
	int nex[maxn+5][c_size], num[maxn+5];

	int newnode(int l)
	{
		len[tot] = l, fail[tot] = num[tot] = poi[tot] = 0;
		mem(nex[tot], 0);
		return tot++;
	}

	void init()
	{
		tot = 0;
		newnode(0), newnode(-1);
		fail[0] = 1, last = 0;
		S[S_len = 0] = -1;
	}

	int get_fail(int x)
	{
		while(S[S_len-len[x]-1] != S[S_len])
			x = fail[x];
		return x;
	}

	int add(int w, int ppoi, int type)
	{
		S[++S_len] = w;
		last = get_fail(last);
		LL res;
		if(nex[last][w] == 0)
		{
			int u = newnode(len[last]+2);
			fail[u] = nex[get_fail(fail[last])][w];
			num[u] = num[fail[u]]+1;
			poi[u] = ppoi;
			if(type == 0)
				res = ppoi-len[u]+1 + sum1[poi[fail[u]]];
			else
				res = ppoi+len[u]-1 + sum2[poi[fail[u]]];
			res += (LL)num[fail[u]]*(ppoi-poi[fail[u]]);
			res %= md;
			nex[last][w] = u;
		}
		else
		{
			int &u = nex[last][w];
			if(type == 0)
				res = sum1[poi[u]];
			else res = sum2[poi[u]];
			res += (LL)num[u]*(ppoi-poi[u]);
			res %= md;
		}
		last = nex[last][w];
		return (int)res;
	}
}tree;

int main()
{
	while(~sf("%s", arr))
	{
		int n = strlen(arr);
		tree.init();
		for(int i=1; i<=n; ++i)
			sum1[i] = tree.add(arr[i-1]-'a', i, 0);
		tree.init();
		for(int i=n; i>=1; --i)
			sum2[i] = tree.add(arr[i-1]-'a', i, 1);
		LL ans = 0;
		for(int i=1; i<n; ++i)
			ans = (ans + (LL)sum1[i]*sum2[i+1]) % md;
		pf("%lld\n", ans);
	}
	return 0;
}
