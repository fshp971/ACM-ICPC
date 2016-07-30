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

#define lld I64d

const int maxn = 15;

int n;
LL pi[maxn+5], ai[maxn+5];

int bits(int x)
{
	int cont = 0;
	while(x) cont += x&1, x >>= 1;
	return cont;
}

void ex_gcd(LL a, LL b, LL &g, LL &x, LL &y)
{
	if(b == 0) g = a, x = 1, y = 0;
	else{ ex_gcd(b, a%b, g, y, x); y -= (a/b)*x; }
}

LL CRT(int type, LL l, LL r)
{
	LL M = 7, x0 = 0, x, y, g, res = 0;
	for(int i=0; i<n; ++i) if(type & (1<<i))
		M *= pi[i+1];
	for(int i=0; i<n; ++i) if(type & (1<<i))
	{
		LL tmp = M / pi[i+1];
		ex_gcd(tmp, pi[i+1], g, x, y);
		x = (x+pi[i+1]) % pi[i+1];
		x0 = (x0 + ai[i+1] * tmp % M * x) % M;
	}
	return max((LL)0,r-x0+M) / M - max((LL)0,l-1-x0+M) / M;
}

LL run(LL l, LL r)
{
	LL ans = r/7 - (l-1)/7;
	for(int i=1; i<(1<<n); ++i)
	{
		if(bits(i)&1) ans -= CRT(i, l, r);
		else ans += CRT(i, l, r);
	}
	return ans;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int t;
	LL x, y;
	cin >> t;
	REP(i,1,t)
	{
		sf("%d%lld%lld", &n, &x, &y);
		REP(k,1,n) sf("%lld%lld\n", pi+k, ai+k);
		printf("Case #%d: %lld\n", i, run(x, y));
	}
	return 0;
}
