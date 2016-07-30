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

const int maxn = 1e5, max_step = 34;

int n, poi[maxn+5][max_step+5];
LL kk, sum[maxn+5][max_step+5], mini[maxn+5][max_step+5];

void build()
{
	for(int t=1; t<=max_step; ++t)
	{
		for(int i=1; i<=n; ++i)
		{
			poi[i][t] = poi[poi[i][t-1]][t-1];
			sum[i][t] = sum[i][t-1] + sum[poi[i][t-1]][t-1];
			mini[i][t] = min(mini[i][t-1], mini[poi[i][t-1]][t-1]);
		}
	}
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	sf("%d%lld", &n, &kk);
	REP(i,1,n) sf("%d", &poi[i][0]), ++poi[i][0];
	REP(i,1,n) sf("%lld", &sum[i][0]), mini[i][0] = sum[i][0];
	build();
	for(int i=1; i<=n; ++i)
	{
		int rem = kk, now = i;
		LL ss = 0, mm = (LL)1<<62;
		int k = 0;
		while(rem)
		{
			if(rem&1)
			{
				ss += sum[now][k];
				mm = min(mm, mini[now][k]);
				now = poi[now][k];
			}
			++k;
			rem >>= 1;
		}
		pf("%lld %lld\n", ss, mm);
	}
	return 0;
}
