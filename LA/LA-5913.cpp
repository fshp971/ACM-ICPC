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

const int maxnode = (1e4) * 40, c_size = 26;

struct Tire
{
	int top, nex[maxnode+5][c_size+5], cont[c_size+5];

	void clear()
	{
		mem(nex[0], 0); mem(cont, 0); top = 0;
	}

	int c_id(char c){ return c-97; }

	void insert(char *a)
	{
		int len = strlen(a), u = 0, t;
		for(int i=0; i<len; ++i)
		{
			t = c_id(a[i]);
			if(!nex[u][t])
			{
				nex[u][t] = (++top);
				mem(nex[top], 0);
				if(i) ++cont[t];
			}
			u = nex[u][t];
		}
	}

	void inv_insert(char *a)
	{
		int len = strlen(a), u = 0, t;
		for(int i=len-1; i>=0; --i)
		{
			t = c_id(a[i]);
			if(!nex[u][t])
			{
				nex[u][t] = (++top);
				mem(nex[top], 0);
				if(i<len-1) ++cont[t];
			}
			u = nex[u][t];
		}
	}
}tire1, tire2;

int n;
bool vis[c_size];
char arr[50];

void init()
{
	LL ans = 0;
	mem(vis, 0);
	tire1.clear(); tire2.clear();
	for(int i=1;i<=n;++i)
	{
		sf("%s", arr);
		tire1.insert(arr);
		tire2.inv_insert(arr);
		if(arr[1] == '\0' && !vis[arr[0]-97])
			vis[arr[0]-97] = true, ++ans;
	}
	ans += (LL)tire1.top * tire2.top;
	for(int i=0;i<c_size;++i)
	{
		ans -= (LL)tire1.cont[i] * tire2.cont[i];
	}
	pf("%lld\n", ans);
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	while(~sf("%d", &n))
		init();
	return 0;
}
