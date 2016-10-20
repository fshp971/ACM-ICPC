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

const int maxn = 200000, maxm = 1000000;

int n, m;
int h[maxn+5], e[maxm*2+5], id[maxm*2+5], nex[maxm*2+5];
int _h[maxn+5], _e[maxm*2+5], _nex[maxm*2+5];

int top, scc, Index;
int sta[maxn+5], Low[maxn+5], DFN[maxn+5], Belong[maxn+5];
char Insta[maxn+5], used[maxm+5];

void Tarjan(int u)
{
	Low[u] = DFN[u] = ++Index;
	sta[++top] = u, Insta[u] = 1;
	for(int i=h[u]; i; i=nex[i])
	{
		if(used[id[i]]) continue;
		used[id[i]] = 1;
		if(!DFN[e[i]])
		{
			Tarjan(e[i]);
			Low[u] = min(Low[u], Low[e[i]]);
		}
		else if(Insta[e[i]])
			Low[u] = min(Low[u], Low[e[i]]);
	}
	if(DFN[u] == Low[u])
	{
		++scc;
		int t;
		do
		{
			t = sta[top--];
			Insta[t] = 0;
			Belong[t] = scc;
		}while(t != u);
	}
}

int dis[maxn+5];

int cal_r()
{
	queue<int> que;
	mem(dis, 0x7f);
	que.push(1);
	dis[1] = 0;
	int x, ss;
	while(!que.empty())
	{
		x = que.front();
		que.pop();
		for(int i=_h[x]; i; i=_nex[i])
		{
			if(dis[x]+1 < dis[_e[i]])
			{
				dis[_e[i]] = dis[x]+1;
				que.push(_e[i]);
			}
		}
	}

	ss = 1;
	for(int i=2; i<=scc; ++i)
	{
		if(dis[ss] < dis[i])
			ss = i;
	}

	mem(dis, 0x7f);
	que.push(ss);
	dis[ss] = 0;
	while(!que.empty())
	{
		x = que.front();
		que.pop();
		for(int i=_h[x]; i; i=_nex[i])
		{
			if(dis[x]+1 < dis[_e[i]])
			{
				dis[_e[i]] = dis[x]+1;
				que.push(_e[i]);
			}
		}
	}
	int ans = 0;
	for(int i=1; i<=scc; ++i)
		ans = max(ans, dis[i]);
	return ans;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int u, v, tp;
	while(sf("%d%d", &n, &m), n||m)
	{
		mem(h, 0); tp = 0;
		REP(i,1,m)
		{
			sf("%d%d", &u, &v);
			e[++tp] = v, id[tp] = i, nex[tp] = h[u], h[u] = tp;
			e[++tp] = u, id[tp] = i, nex[tp] = h[v], h[v] = tp;
		}
		mem(DFN, 0); mem(used, 0);
		top = scc = Index = 0;
		for(int i=1; i<=n; ++i)
			if(!DFN[i])
				Tarjan(i);
		if(scc == 1)
		{
			pf("0\n");
			continue;
		}
		mem(_h, 0), tp = 0;
		for(int i=1; i<=n; ++i)
		{
			for(int k=h[i]; k; k=nex[k])
			{
				if(Belong[i] != Belong[e[k]])
				{
					u = Belong[i], v = Belong[e[k]];
					_e[++tp] = v, _nex[tp] = _h[u], _h[u] = tp;
					_e[++tp] = u, _nex[tp] = _h[v], _h[v] = tp;
				}
			}
		}
		pf( "%d\n", scc-1 - cal_r() );
	}
	return 0;
}
