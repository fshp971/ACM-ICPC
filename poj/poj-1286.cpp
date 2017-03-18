#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<queue>
#include<string>
#include<vector>
#include<map>
#include<set>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define sf scanf
#define pf printf
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 24;

LL three[maxn+5];

LL gcd(LL a, LL b) { return b ? gcd(b, a%b) : a; }

int main()
{
	int n, g;
	LL ans;
	three[0] = 1;
	for(int i=1; i<=maxn; ++i) three[i] = three[i-1]*3;
	while(sf("%d", &n), ~n)
	{
		if(n == 0)
		{
			printf("0\n");
			continue;
		}
		if(n%2)
			ans = n*three[n/2]*3;
		else
			ans = (n/2)*three[n/2] + (n/2)*three[n/2+1];
		for(int i=1; i<=n; ++i)
			ans += three[gcd(n,i)];
		ans /= n*2;
		pf("%lld\n", ans);
	}
	return 0;
}
