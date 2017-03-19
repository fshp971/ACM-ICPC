#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<string>
#include<queue>
#include<utility>
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

const int md = 1e9 + 7;

LL gcd(LL a, LL b) { return b ? gcd(b, a%b) : a; }

LL pow_mod(LL a, LL b)
{
	LL res = 1;
	while(b)
	{
		if(b&1) res = res*a % md;
		a = a*a % md, b >>= 1;
	}
	return res;
}

int main()
{
	int T, n, m;
	LL ans;
	sf("%d", &T);
	REP(t,1,T)
	{
		sf("%d%d", &n, &m);
		if(m%2)
			ans = m * pow_mod(n, m/2+1) % md;
		else
			ans = m/2 * (pow_mod(n, m/2) + pow_mod(n, m/2+1)) % md;
		for(int i=1; i<=m; ++i)
			ans = (ans + pow_mod(n, gcd(i,m))) % md;
		ans = ans * pow_mod(m*2, md-2) % md;
		printf("Case #%d: %lld\n", t, ans);
	}
	return 0;
}
