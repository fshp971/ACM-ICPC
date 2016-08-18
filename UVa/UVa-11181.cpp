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

int n;
double val[22];

int bitcnt(int x, double &prob)
{
	int cnt = 0;
	prob = 1.0;
	for(int i=0; i<n; ++i)
	{
		if(x & (1<<i)) prob *= val[i], ++cnt;
		else prob *= (1.0 - val[i]);
	}
	return cnt;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int NT = 0, r;
	double prob, sum;
	double res[22];
	while(sf("%d%d", &n, &r), n)
	{
		FOR(i,0,n) sf("%lf", val+i);
		sum = 0;
		mem(res, 0);
		for(int msk=(1<<n)-1; msk>=0; --msk)
		{
			if(bitcnt(msk, prob) == r)
			{
				sum += prob;
				int x = msk, i = 0;
				while(x)
				{
					if(x&1)
						res[i] += prob;
					x >>= 1, ++i;
				}
			}
		}
		pf("Case %d:\n", ++NT);
		FOR(i,0,n) pf("%.6f\n", res[i] / sum);
	}
	return 0;
}
