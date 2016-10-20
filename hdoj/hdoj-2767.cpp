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

const int maxn = 20000;
const int maxm = 50000;

int top, scc, Index;
int sta[maxn+5], DFN[maxn+5], Low[maxn+5], Belong[maxn+5];
char Insta[maxn+5];

int n, m;
int h[maxn+5], e[maxm+5], nex[maxm+5];
char cnt1[maxn+5], cnt2[maxn+5];

void Tarjan(int u)
{
	DFN[u] = Low[u] = ++Index;
	Insta[u] = 1; sta[++top] = u;
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
	if(DFN[u] == Low[u])
	{
		int t;
		++scc;
		do
		{
			t = sta[top--];
			Insta[t] = 0;
			Belong[t] = scc;
		}while(t != u);
	}
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int T, u, v, ans1, ans2;
	sf("%d", &T);
	while(T--)
	{
		sf("%d%d", &n, &m);
		mem(h, 0);
		REP(i,1,m)
		{
			sf("%d%d", &u, &v);
			e[i] = v, nex[i] = h[u], h[u] = i;
		}
		top = scc = Index = 0;
		mem(DFN, 0);
		REP(i,1,n)
			if(!DFN[i])
				Tarjan(i);
		if(scc == 1)
		{
			pf("0\n");
			continue;
		}
		mem(cnt1, 0);
		mem(cnt2, 0);
		REP(i,1,n)
		{
			for(int k=h[i]; k; k=nex[k])
			{
				if(Belong[i] != Belong[e[k]])
				{
					cnt1[Belong[i]] = 1;
					cnt2[Belong[e[k]]] = 1;
				}
			}
		}
		ans1 = ans2 = 0;
		for(int i=1; i<=scc; ++i)
		{
			if(!cnt1[i]) ++ans1;
			if(!cnt2[i]) ++ans2;
		}
		pf("%d\n", max(ans1, ans2));
	}
	return 0;
}
