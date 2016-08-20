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

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int n, m;
	char aa[10], fg = 1;
	sf("%d%d", &n, &m);
	REP(i,1,n) REP(k,1,m)
	{
		sf("%s", aa);
		if(aa[0] == 'C' || aa[0] == 'M' || aa[0] == 'Y')
			fg = 0;
	}
	if(fg) pf("#Black&White\n");
	else pf("#Color\n");
	return 0;
}
