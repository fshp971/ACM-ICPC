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
	char aa[105];
	int n, f[105][105];
	while(sf("%s", aa), aa[0] != 'e')
	{
		mem(f, 0);
		n = strlen(aa);
		for(int t=2; t<=n; ++t)
		{
			for(int i=1; i<=n; ++i)
			{
				int j = i+t-1;
				if(j>n) break;
				f[i][j] = max(f[i][j], f[i+1][j]);
				if(aa[i-1] == ']' && aa[i-1] == ')') continue;
				for(int k=i+1; k<=j; ++k)
				{
					if( (aa[i-1]=='(' && aa[k-1]==')') || (aa[i-1]=='[' && aa[k-1]==']') )
						f[i][j] = max(f[i][j], f[i+1][k-1] + 2 + f[k+1][j]);
				}
			}
		}
		pf("%d\n", f[1][n]);
	}
	return 0;
}
