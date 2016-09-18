#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<queue>
#include<utility>
#include<map>
#include<set>
#include<bitset>

using namespace std;

#define LL long long
#define MP make_pair
#define pii pair<int,int>
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define sf scanf
#define pf printf

const LL md = 1e9+7;
const int maxn = 1e6;

LL pow_mod(LL a, LL b)
{
	LL res = 1, tmp = a;
	while(b)
	{
		if(b&1) res = res * tmp % md;
		b >>= 1;
		tmp = tmp*tmp % md;
	}
	return res;
}

LL jie[maxn+5], inv[maxn+5];

int main()
{
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	jie[0] = inv[0] = 1;
	for(int i=1; i<=maxn; ++i)
	{
		jie[i] = jie[i-1] * i % md;
		inv[i] = pow_mod(jie[i], md-2);
	}
	int T, n, m, kk, s;
	LL ans;
	sf("%d", &T);
	while(T--)
	{
		sf("%d%d%d", &n, &m, &kk);
		s = n-m*kk;
		if(m>s)
		{
			pf("0\n");
			continue;
		}
		ans = jie[s-1] * inv[m] % md * inv[s-m] % md * n % md;
		//pf("%lld\n", ans);
		cout << ans << "\n";
	}
	return 0;
}
