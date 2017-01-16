#include<bits/stdc++.h>

using namespace std;

#define LL long long
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define mem(a,b) memset(a,b,sizeof(a))
#define MP make_pair
#define pii pair<int,int>
#define sf scanf
#define pf printf

const int maxn = 50000, maxk = 100;
const int md = 1e9 + 7;

int n, kk, sum[maxn+5];
LL ccc[maxk+5][maxk+5];
LL g[maxk+5], ans[maxn+5];
char arr[maxn+5];

LL C(int cn, int cm)
{
	if(ccc[cn][cm] != -1) return ccc[cn][cm];
	if(cm == 0 || cn == cm) return ccc[cn][cm] = 1;
	return ccc[cn][cm] = (C(cn-1, cm)+C(cn-1,cm-1)) % md;
}

int main()
{
	mem(ccc, -1);
	int T;
	sf("%d", &T);
	while(T--)
	{
		sf("%d%d", &n, &kk);
		sf("%s", arr);
		sum[0] = 0;
		REP(i,1,n) sum[i] = sum[i-1] + arr[i-1] - 48;
		mem(g, 0);
		REP(i,1,n)
		{
			LL ttp = 1, dt = (md-sum[i-1]) % md;
			REP(k,0,kk)
			{
				g[k] = (g[k] + ttp) % md;
				ttp = ttp*dt % md;
			}
			ans[i] = 0;
			ttp = 1, dt = sum[i];
			for(int k=kk; k>=0; --k)
			{
				LL tmp = C(kk,k) * ttp % md;
				tmp = tmp * g[k] % md;
				ans[i] = (ans[i]+tmp) % md;
				ttp = ttp*dt % md;
			}
		}
		REP(i,1,n)
		{
			if(i>1) pf(" ");
			pf("%lld", ans[i]);
		}
		pf("\n");
	}
	return 0;
}
