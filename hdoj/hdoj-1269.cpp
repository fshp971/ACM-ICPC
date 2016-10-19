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

const int maxn = 10000;
const int maxm = 100000;

int n, m;
int h[maxn+5], e[maxm+5], nex[maxm+5];

int Low[maxn+5], DFN[maxn+5], Belong[maxn+5];
int sta[maxn+5], top, Index, scc;
char Insta[maxn+5];

void Tarjan(int u)
{
	Low[u] = DFN[u] = ++Index;
	Insta[u] = 1, sta[++top] = u;
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
	int t;
	if(Low[u] == DFN[u])
	{
		++scc;
		do
		{
			t = sta[top--];
			Belong[t] = scc;
			Insta[t] = 0;
		}while(t != u);
	}
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int u, v;
	while(sf("%d%d", &n, &m), n || m)
	{
		mem(h, 0);
		REP(i,1,m)
		{
			sf("%d%d", &u, &v);
			e[i] = v, nex[i] = h[u], h[u] = i;
		}
		top = Index = scc = 0;
		mem(DFN, 0);
		mem(Insta, 0);
		for(int i=1; i<=n; ++i)
			if(!DFN[i])
				Tarjan(i);
		pf(scc == 1 ? "Yes\n" : "No\n");
	}
	return 0;
}
