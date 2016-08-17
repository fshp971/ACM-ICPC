#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<iostream>
#include<algorithm>
#include<string>
#include<queue>
#include<vector>
#include<utility>
#include<map>
#include<set>

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
	int n, aa[105];
	int f[105][105];
	sf("%d", &n);
	REP(i,1,n) sf("%d", aa+i);
	mem(f, 0x7f);
	for(int i=1; i<n; ++i) f[i][i+1] = 0;
	for(int t=1; t<=n; ++t)
	{
		for(int i=1; i+t-1<=n; ++i)
		{
			int j = i+t-1;
			for(int k=i+1; k<j; ++k)
				f[i][j] = min(f[i][j], f[i][k] + f[k][j] + aa[i]*aa[k]*aa[j]);
		}
	}
	pf("%d\n", f[1][n]);
	return 0;
}
