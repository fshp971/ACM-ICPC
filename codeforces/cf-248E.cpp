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

const int maxn = 1e5;

int n, cont[maxn+5];
double f[maxn+5][105];

int main()
{
	int a, T, u, v, ki;
	double ans = 0;
	sf("%d", &n);
	mem(f,0);
	REP(i,1,n)
	{
		sf("%d", &a);
		f[i][a] = 1.0, cont[i] = a;
		if(!a) ++ans;
	}
	sf("%d", &T);
	REP(t,1,T)
	{
		sf("%d%d%d", &u, &v, &ki);
		ans -= f[u][0];
		REP(i,1,ki)
		{
			for(int k=1; k<=min(100,cont[u]); ++k)
			{
				f[u][k-1] += f[u][k]*(double)k/cont[u];
				f[u][k] = f[u][k]*(double)(cont[u]-k)/cont[u];
			}
			--cont[u];
		}
		ans += f[u][0], cont[v] += ki;
		pf("%.12f\n", ans);
	}
	return 0;
}
