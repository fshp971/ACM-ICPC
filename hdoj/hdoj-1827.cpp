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

const int maxn = 1000, maxm = 2000;

int n, m;
LL ci[maxn+5];
int h[maxn+5], e[maxm+5], nex[maxm+5];

int scc, top, Index;
int sta[maxn+5], Low[maxn+5], DFN[maxn+5], Belong[maxn+5];
LL cc[maxn+5];
int cnt[maxn+5];
char Insta[maxn+5];

void Tarjan(int u)
{
	Low[u] = DFN[u] = ++Index;
	sta[++top] = u, Insta[u] = 1;
	for(int i=h[u]; i; i=nex[i])
	{
		if(!DFN[e[i]])
		{
			Tarjan(e[i]);
			Low[u] = min(Low[u], Low[e[i]]);
		}
		else if(Insta[e[i]])
			Low[u] = min(Low[u], Low[e[i]]);
	}
	if(Low[u] == DFN[u])
	{
		cc[++scc] = ci[u];
		int t;
		do{
			t = sta[top--];
			Insta[t] = 0;
			Belong[t] = scc;
			cc[scc] = min(cc[scc], ci[t]);
		}while(t != u);
	}
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int u, v;
	while(~sf("%d%d", &n, &m))
	{
		REP(i,1,n) sf("%lld", ci+i);
		mem(h, 0);
		REP(i,1,m)
		{
			sf("%d%d", &u, &v);
			e[i] = v, nex[i] = h[u], h[u] = i;
		}
		mem(DFN, 0);
		scc = top = Index = 0;
		REP(i,1,n)
			if(!DFN[i])
				Tarjan(i);
		mem(cnt, 0);
		REP(i,1,n)
		{
			for(int k=h[i]; k; k=nex[k])
			{
				if(Belong[i] != Belong[e[k]])
					++cnt[Belong[e[k]]];
			}
		}
		int cont = 0;
		LL ans = 0;
		REP(i,1,scc) if(!cnt[i])
			++cont, ans += cc[i];
		pf("%d %lld\n", cont, ans);
	}
	return 0;
}
