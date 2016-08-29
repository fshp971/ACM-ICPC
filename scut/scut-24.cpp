#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<string>
#include<queue>
#include<utility>
#include<map>
#include<set>

using namespace std;

#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define mem(a,b) memset(a,b,sizeof(a))
#define MP(a,b) make_pair(a,b)
#define LL long long
#define sf scanf
#define pf printf

const int maxn = 1e6;

int n;
int h[maxn+5], e[maxn*2+5], nex[maxn*2+5];
int fa[maxn+5], son[maxn+5], fam[maxn+5], par[maxn+5];
char vis[maxn+5];

void dfs1(int x, int pre)
{
	fa[x] = pre;
	vis[x] = 1;
	fam[x] = x;
	son[x] = 1<<30;
	for(int i=h[x]; i; i=nex[i])
	{
		if(vis[e[i]]) continue;
		int &nx = e[i];
		dfs1(nx, pre ? pre : nx);
		fam[x] = min(fam[x], fam[nx]);
		son[x] = min(son[x], fam[nx]);
	}
}

void dfs2(int x, int mini)
{
	vis[x] = 1;
	par[x] = mini;
	int min1 = 1<<30, min2 = 1<<30, tmp;
	if(x != 1)
	{
		for(int i=h[x]; i; i=nex[i])
		{
			if(vis[e[i]]) continue;
			tmp = fam[e[i]];
			if(tmp < min1) swap(tmp, min1);
			if(tmp < min2) swap(tmp, min2);
		}
	}
	for(int i=h[x]; i; i=nex[i])
	{
		if(vis[e[i]]) continue;
		if(fam[e[i]] == min1)
			dfs2(e[i], min(mini, min2));
		else dfs2(e[i], min(mini, min1));
	}
}

int main()
{
	int que, u, v, top, ans;
	int min1, min2, min3;
	while(~sf("%d%d", &n, &que))
	{
		top = 0;
		mem(h, 0);
		REP(i,1,n-1)
		{
			sf("%d%d", &u, &v);
			e[++top] = v, nex[top] = h[u], h[u] = top;
			e[++top] = u, nex[top] = h[v], h[v] = top;
		}
		mem(vis, 0);
		dfs1(1, 0);
		mem(vis, 0);
		dfs2(1, 1<<30);
		min1 = min2 = min3 = (1<<30);
		for(int i=h[1]; i; i=nex[i])
		{
			int tmp = fam[e[i]];
			if(tmp < min1) swap(min1, tmp);
			if(tmp < min2) swap(min2, tmp);
			if(tmp < min3) swap(min3, tmp);
		}
		ans = 0;
		for(int i=1; i<=que; ++i)
		{
			sf("%d%d", &u, &v);
			u ^= ans, v ^= ans;
			if(u == v)
			{
				if(u == 1) ans = 2;
				else ans = 1;
			}
			else if(u == 1 || v == 1)
			{
				if(u == 1) swap(u, v);
				ans = min(son[u], par[u]);
				int tmp = min1;
				if(fam[fa[u]] == tmp) tmp = min2;
				ans = min(ans, tmp);
			}
			else if(fa[u] == fa[v]) ans = 1;
			else
			{
				ans = min(son[u], son[v]);
				ans = min(ans, min(par[u], par[v]));
				int tmp = min1;
				if(tmp == fam[fa[u]] || tmp == fam[fa[v]]) tmp = min2;
				if(tmp == fam[fa[u]] || tmp == fam[fa[v]]) tmp = min3;
				ans = min(ans, tmp);
			}
			pf("%d\n", ans);
		}
	}
	return 0;
}
