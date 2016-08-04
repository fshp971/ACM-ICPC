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

const int maxn = 1e7;

bool vis[maxn+5];
int mu[maxn+5], prime[maxn+5];
int G[maxn+5];

void mobius()
{
	mem(vis, 0);
	mem(G, 0);
	int tot = 0, top = 0;
	mu[1] = 1, mu[0] = 0;
	for(int i=2; i<=maxn; ++i)
	{
		if(!vis[i])
			prime[++tot] = i, mu[i] = -1, G[i] = 1;
		for(int j=1; j<=tot && (LL)i*prime[j] <= maxn; ++j)
		{
			vis[i*prime[j]] = true;
			if(i%prime[j])
				mu[i*prime[j]] = -mu[i], G[i*prime[j]] = -G[i]+mu[i];
			else
			{
				mu[i*prime[j]] = 0, G[i*prime[j]] = mu[i];
				break;
			}
		}
	}
	//for(int i=1; i<=30; ++i) pf("G[%d] = %d\n", i, G[i]);
	for(int i=1; i<=maxn; ++i) G[i] += G[i-1];
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	mobius();
	int T, a, b, nex;
	sf("%d", &T);
	LL ans;
	while(T--)
	{
		sf("%d%d", &a, &b);
		ans = 0;
		for(int i=1; i<=min(a,b); i=nex+1)
		{
			nex = min(a/(a/i), b/(b/i));
			ans += (LL)(a/i) * (b/i) * (G[nex] - G[i-1]);
		}
		cout << ans << "\n";
	}
	return 0;
}
