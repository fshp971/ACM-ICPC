#include<bits/stdc++.h>

using namespace std;

#define LL long long
#define MP(a,b) make_pair(a,b)
#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define pii pair<int,int>
#define sf scanf
#define pf printf

const int maxn = 1e5;

int h[maxn+2], nex[maxn*2+2], e[maxn*2+2], wi[maxn*2+2];
char fg[maxn+2];
int n, m, kk;

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int u, v, l, top = 0;
	mem(fg, 0); mem(h, 0);
	sf("%d%d%d", &n, &m, &kk);
	REP(i,1,m)
	{
		sf("%d%d%d", &u, &v, &l);
		e[++top] = v, wi[top] = l, nex[top] = h[u], h[u] = top;
		e[++top] = u, wi[top] = l, nex[top] = h[v], h[v] = top;
	}
	REP(i,1,kk) sf("%d", &u), fg[u] = 1;
	int ans = -1;
	REP(i,1,n) if(fg[i])
	{
		for(int k=h[i]; k; k=nex[k]) if(!fg[e[k]])
		{
			if(ans == -1) ans = wi[k];
			else ans = min(ans, wi[k]);
		}
	}
	pf("%d\n", ans);
	return 0;
}
