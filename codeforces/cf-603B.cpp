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

const int maxp = 1e6;
const int md = 1e9 + 7;

int pp, kk;
bool vis[maxp+5];

void dfs(LL x)
{
	vis[x] = true;
	x = x * kk % pp;
	if(!vis[x]) dfs(x);
}

void init()
{
	cin >> pp >> kk;
	LL ans = 1;
	if(kk<=1)
	{
		if(kk == 1) ans = pp;
		FOR(i,1,pp)
			ans = ans * pp % md;
		cout << ans << "\n";
		return;
	}
	mem(vis, 0);
	FOR(i,1,pp) if(!vis[i])
	{
		dfs(i);
		ans = ans * pp % md;
	}
	cout << ans << "\n";
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	init();
	return 0;
}
