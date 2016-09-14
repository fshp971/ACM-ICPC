#include<bits/stdc++.h>

using namespace std;

#define LL long long
#define mem(a,b) memset(a,b,sizeof(a))
#define MP(a,b) make_pair(a,b)
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define sf scanf
#define pf printf

const int md = 1e9+7;
const int maxn = 2e5 + 100;

int n, kk;
LL f[maxn*2+5][2];

int main()
{
	int T, a, b, poi = 0;
	LL now;
	sf("%d%d%d%d", &a, &b, &kk, &T);
	kk *= 2;
	n = T*kk+100;
	f[a-b+n+1][0] = 1;
	for(int i=a-b+n+2; i<=2*n+1; ++i) f[i][0] = 1;
	for(int t=1; t<=T; ++t)
	{
		now = 0;
		for(int i=kk+1; i>=1; --i)
			now += f[i][poi];
		now %= md;
		f[1][poi^1] = now;
		for(int i=2; i<=2*n+1; ++i)
		{
			int l = max(1, i-kk-1);
			now = (now - f[i-1][poi] + f[l-1][poi] + md);
			l = min(2*n+1, i+kk);
			now = (now + f[l][poi] - f[i-1][poi] + md);
			now %= md;
			f[i][poi^1] = (f[i-1][poi^1]+now) % md;
		}
		poi ^= 1;
	}
	LL ans = (f[2*n+1][poi] - f[n+1][poi] + md) % md;
	pf("%lld\n", ans);
	return 0;
}
