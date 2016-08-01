//#include<bits/stdc++.h>
#include<cstdio>
#include<cstdlib>
#include<cstring>

using namespace std;

#define LL long long
#define MP(a,b) make_pair(a,b)
#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define pii pair<int,int>
#define sf scanf
#define pf printf

const int max_mu = 1000;

bool vis[max_mu+5];
int mu[max_mu+5], prime[max_mu+5];

void mobius()
{
	mem(vis, 0);
	mu[1] = 1;
	int tot = 0;
	for(int i=2; i<=max_mu; ++i)
	{
		if(!vis[i]) prime[++tot] = i, mu[i] = -1;
		for(int j=1; j<=tot; ++j)
		{
			if(i * prime[j] > max_mu) break;
			vis[i*prime[j]] = true;
			if(i % prime[j]) mu[i * prime[j]] = -mu[i];
			else{ mu[i * prime[j]] = 0; break; }
		}
	}
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	mobius();
	int T, n, ans;
	sf("%d", &T);
	for(int t=1; t<=T; ++t)
	{
		sf("%d", &n);
		ans = 2;
		for(int i=1; i<=n; ++i)
			ans += mu[i] * (n/i) * (n/i);
		pf("%d %d %d\n", t, n, ans);
	}
	return 0;
}
