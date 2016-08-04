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

const int maxn = 1e5;

bool vis[maxn+5];
int mu[maxn+5], prime[maxn+5];

void mobius()
{
	mem(vis, 0);
	mu[0] = 0, mu[1] = 1;
	int tot = 0;
	for(int i=2; i<=maxn; ++i)
	{
		if(!vis[i]) mu[i] = -1, prime[++tot] = i;
		for(int j=1; j<=tot && (LL)i*prime[j]<=maxn; ++j)
		{
			vis[i*prime[j]] = true;
			if(i%prime[j]) mu[i*prime[j]] = -mu[i];
			else{ mu[i*prime[j]] = 0; break; }
		}
	}
	//for(int i=1; i<=30; ++i) pf("mu[%d] = %d\n", i, mu[i]);
	REP(i,1,maxn) mu[i] += mu[i-1];
}

LL calc(int a, int b)
{
	LL res = 0;
	int nex;
	for(int i=1; i<=min(a, b); i=nex+1)
	{
		nex = min(a/(a/i), b/(b/i));
		res += (LL)(a/i) * (b/i) * (mu[nex] - mu[i-1]);
	}
	return res;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	mobius();
	int T, a, b, nex, kk;
	LL ans;
	sf("%d", &T);
	REP(t,1,T)
	{
		sf("%d%d%d%d%d", &a, &a, &b, &b, &kk);
		if(!kk) ans = 0;
		else
		{
			a /= kk, b /= kk;
			ans = calc(a,b) - calc(min(a,b), min(a,b)) / 2;
		}
		pf("Case %d: %lld\n", t, ans);
	}
	return 0;
}
