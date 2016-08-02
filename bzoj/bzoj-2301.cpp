/**************************************************************
	Problem: 2301
	User: fshp971
	Language: C++
	Result: Accepted
	Time:10136 ms
	Memory:1728 kb
****************************************************************/

#include<bits/stdc++.h>

using namespace std;

#define LL long long
#define MP(a,b) make_pair(a,b)
#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define pii pair<int,int>
#define sf scanf
#define pf printf

const int maxn = 50000;

bool vis[maxn+5];
int mu[maxn+5], prime[maxn+5];

void mobius()
{
	mem(vis, 0);
	int tot = 0;
	mu[0] = 0, mu[1] = 1;
	for(int i=2; i<=maxn; ++i)
	{
		if(!vis[i]) mu[i] = -1, prime[++tot] = i;
		for(int j=1; j<=tot; ++j)
		{
			if((LL)i * prime[j] > maxn) break;
			vis[i*prime[j]] = true;
			if(i % prime[j]) mu[i*prime[j]] = -mu[i];
			else
			{
				mu[i*prime[j]] = 0; break;
			}
		}
	}
	for(int i=2; i<=maxn; ++i) mu[i] += mu[i-1];
}

int cal(int n, int m)
{
	int res = 0, nex;
	for(int i=1; i<=min(n, m); ++i)
	{
		nex = min(n / (n/i), m / (m/i));
		res += (mu[nex] - mu[i-1]) * (n/i) * (m/i);
		i = nex;
	}
	return res;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	mobius();
	int t, aa, bb, cc, dd, kk, ans;
	sf("%d", &t);
	while(t--)
	{
		sf("%d%d%d%d%d", &aa, &bb, &cc, &dd, &kk);
		ans = cal(bb/kk, dd/kk) - cal((aa-1)/kk, dd/kk) - cal(bb/kk, (cc-1)/kk) + cal((aa-1)/kk, (cc-1)/kk);
		pf("%d\n", ans);
	}
	return 0;
}
