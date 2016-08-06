//O(n*m)居然不會超時……

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

const LL INF = ((LL)1<<40);
const int maxn = 1e6;

int n, m;
LL ans;
LL f[maxn+5], g[maxn+5], sum[maxn+5];

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	while(~sf("%d%d", &m, &n))
	{
		sum[0] = 0;
		REP(i,1,n) sf("%lld", sum+i), sum[i] += sum[i-1];
		REP(i,1,m) f[i] = g[i] = -INF;
		ans = -INF; f[0] = 0; g[0] = 0;
		for(int i=1; i<=n; ++i)
		{
			for(int j=m; j>=1; --j)
			{
				f[j] = max(f[j], g[j-1] + sum[i]);
				g[j] = max(f[j]-sum[i], g[j]);
			}
			g[0] = max(g[0], -sum[i]);
			ans = max(ans, f[m]);
		}
		pf("%lld\n", ans);
	}
	return 0;
}
