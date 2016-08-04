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

const int maxn = 1e6;

bool vis[maxn+5];
int mu[maxn+5], prime[maxn+5];

void mobius()
{
	mem(vis, 0);
	int tot = 0;
	mu[1] = 1, mu[0] = 0;
	for(int i=2; i<=maxn; ++i)
	{
		if(!vis[i]) mu[i] = -1, prime[++tot] = i;
		for(int j=1; j<=tot && (LL)i*prime[j] <= maxn; ++j)
		{
			vis[i*prime[j]] = true;
			if(i%prime[j]) mu[i*prime[j]] = -mu[i];
			else{ mu[i*prime[j]] = 0; break; }
		}
	}
	REP(i,1,maxn) mu[i] += mu[i-1];
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	mobius();
	int T, n, nex;
	LL ans, tmp;
	sf("%d", &T);
	while(T--)
	{
		sf("%d", &n);
		ans = 3;
		for(int i=1; i<=n; i=nex+1)
		{
			nex = n/(n/i);
			tmp = n/i;
			ans += (tmp*tmp*tmp + tmp*tmp*3) * (mu[nex] - mu[i-1]);
		}
		cout << ans << "\n";
	}
	return 0;
}
