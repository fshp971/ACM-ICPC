#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<queue>
#include<string>
#include<vector>
#include<utility>
#include<map>
#include<set>
#include<bitset>

using namespace std;

#define LL long long
#define pii pair<int,int>
#define MP make_pair
#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define sf scanf
#define pf printf

const int maxn = 100, maxm = 1000;

int n, m, size;
int cnt[maxn+5];
char mmp[maxn+5][maxn+5];
int h[maxn+5], e[maxm+5], nex[maxm+5];
int sta[maxn+5];
int ans;

void dfs(int rem, int now, int cont)
{
	if(cont == size)
	{
		++ans;
		return;
	}
	if(rem+cont < size) return;
	char fg = 1;
	for(int i=1; i<=cont; ++i)
		if(!mmp[e[now]][sta[i]])
		{
			fg = 0;
			break;
		}
	if(fg)
	{
		sta[cont+1] = e[now];
		dfs(rem-1, nex[now], cont+1);
	}
	dfs(rem-1, nex[now], cont);
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int T, u, v;
	sf("%d", &T);
	while(T--)
	{
		sf("%d%d%d", &n, &m, &size);
		mem(h, 0); mem(cnt, 0); mem(mmp, 0);
		for(int i=1; i<=m; ++i)
		{
			sf("%d%d", &u, &v);
			mmp[u][v] = mmp[v][u] = 1;
			++cnt[u];
			e[i] = v, nex[i] = h[u], h[u] = i;
		}
		ans = 0;
		for(int i=1; i<=n; ++i)
		{
			if(cnt[i]+1 < size) continue;
			sta[1] = i;
			dfs(cnt[i], h[i], 1);
		}
		pf("%d\n", ans);
	}
	return 0;
}
