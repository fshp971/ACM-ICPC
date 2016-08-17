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

const int maxn = 100000;

int mu[maxn+2], prime[maxn+2];
char vis[maxn+2];

void mobius()
{
	mem(vis, 0);
	int tot = 0;
	mu[0] = 0, mu[1] = 1;
	for(int i=2; i<=maxn; ++i)
	{
		if(!vis[i])
			prime[++tot] = i, mu[i] = -1;
		for(int k=1; k<=tot && (LL)i*prime[k]<=maxn; ++k)
		{
			vis[prime[k]*i] = 1;
			if(i%prime[k]) mu[i*prime[k]] = -mu[i];
			else
			{
				mu[i*prime[k]] = 0;
				break;
			}
		}
	}
	REP(i,1,maxn) mu[i] += mu[i-1];
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	mobius();
	int NT = 0, n, nex;
	LL ans;
	while(sf("%d", &n), n)
	{
		n /= 2, ans = 3;
		for(int i=1; i<=n; i=nex+1)
		{
			nex = n / (n/i);
			ans += (LL)4 * (mu[nex] - mu[i-1]) * (n/i) * (n/i) * (n/i);
			ans += (LL)6 * (mu[nex] - mu[i-1]) * (n/i) * (n/i);
		}
		pf("Crystal %d: %lld\n", ++NT, ans*2);
	}
	return 0;
}
