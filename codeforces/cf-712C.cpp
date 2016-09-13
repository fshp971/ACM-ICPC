#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<string>
#include<queue>
#include<vector>
#include<utility>
#include<map>
#include<set>
#include<bitset>

using namespace std;

#define LL long long
#define mem(a,b) memset(a,b,sizeof(a))
#define MP(a,b) make_pair(a,b)
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define sf scanf
#define pf printf

int main()
{
	int x, y, a, b, c, ans = 0;
	sf("%d%d", &x, &y);
	a = b = c = y;
	int mx = y;
	while(mx < x)
	{
		++ans;
		if(ans%3 == 1) a = (b+c)-1;
		else if(ans%3 == 2) b = (a+c)-1;
		else c = (a+b)-1;
		mx = max(a, max(b, c));
	}
	pf("%d\n", ans+2);
	return 0;
}
