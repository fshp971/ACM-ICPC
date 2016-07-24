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

const int c_size = 2, maxn = 50000, maxnode = 1e7;

struct Tire
{
	int top;
	int nex[maxnode+5][c_size], cnt[maxnode+5];

	inline int c_id(char c){ return c-48; }

	void clear()
	{
		top = 0, cnt[0] = 0;
		mem(nex[0], 0);
	}

	int insert(char *a)
	{
		int len = strlen(a), u = 0, t;
		int res = 0;
		for(int i=0; i<len; ++i)
		{
			t = c_id(a[i]);
			if(!nex[u][t])
			{
				nex[u][t] = (++top);
				mem(nex[top], 0);
				cnt[top] = 0;
			}
			u = nex[u][t];
			++cnt[u];
			res = max(res, cnt[u]*(i+1));
		}
		return res;
	}
}tire;

int n;
char arr[maxn+5];

void init()
{
	sf("%d", &n);
	tire.clear();
	int ans = 0;
	REP(i,1,n)
	{
		sf("%s", arr);
		ans = max(ans, tire.insert(arr));
	}
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
