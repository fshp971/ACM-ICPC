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

const int maxn = 200000;

int n;
LL ss[maxn+5];

int main()
{
	sf("%d", &n);
	REP(i,1,n) sf("%lld", ss+i), ss[i] += ss[i-1];
	LL now = ss[n];
	for(int i=n-1; i>=2; --i)
		now = max(now, ss[i] - now);
	pf("%lld\n", now);
	return 0;
}
