#include<bits/stdc++.h>

using namespace std;

#define LL long long
#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define pii pair<int,int>
#define MP(a,b) make_pair(a,b)
#define sf scanf
#define pf printf

const int maxn = 20000;

int n;
int fa[maxn+5], dis[maxn+5];

int find_fa(int x)
{
	if(fa[x] == x) return x;
	int tmp = fa[x];
	fa[x] = find_fa(fa[x]);
	dis[x] += dis[tmp];
	return fa[x];
}

void init()
{
	cin >> n;
	REP(i,1,n) fa[i] = i;
	mem(dis, 0);
	char ord[5];
	int u, v;
	while(sf("%s", ord), ord[0] != 'O')
	{
		if(ord[0] == 'I')
		{
			sf("%d%d", &u, &v);
			fa[u] = v;
			dis[u] = abs(u-v)%1000;
		}
		else
		{
			sf("%d", &u);
			find_fa(u);
			pf("%d\n", dis[u]);
		}
	}
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
