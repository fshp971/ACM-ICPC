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

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int T;
	LL n, m, bb, kk, tmp, nex;
	sf("%d", &T);
	for(int t=1; t<=T; ++t)
	{
		sf("%lld%lld%lld", &m, &n, &bb);
		kk = 1;
		for(LL i=2; i<=m; i=nex+1)
		{
			nex = min(n/(n/i), m/(m/i));
			if( (n/i) - (m/i) >= bb )
				kk = nex;
		}
		for(LL i=m+1; i<=n; i=nex+1)
		{
			nex = n/(n/i);
			if( (n/i) >= bb )
				kk = nex;
		}
		pf("Case #%d: %lld\n", t, kk);
	}
	return 0;
}
