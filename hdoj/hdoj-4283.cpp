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

int n, val[105];
int f[105][105];

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int T;
	sf("%d", &T);
	for(int t=1; t<=T; ++t)
	{
		sf("%d", &n);
		mem(f, 0x7f); val[0] = 0;
		REP(i,1,n) sf("%d", val+i), val[i] += val[i-1];
		for(int i=1; i<=n; ++i) f[i][i] = f[i+1][i] = 0;
		for(int l=2; l<=n; ++l)
		{
			for(int i=1; i+l-1<=n; ++i)
			{
				int j = i+l-1;
				for(int k=i; k<=j; ++k)
				{
					f[i][j] = min(f[i][j],
								  (k-i)*(val[i]-val[i-1]) + f[i+1][k] + (k-i+1)*(val[j]-val[k]) + f[k+1][j]);
				}
			}
		}
		pf("Case #%d: %d\n", t, f[1][n]);
	}
	return 0;
}
