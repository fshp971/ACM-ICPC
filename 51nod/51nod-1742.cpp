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

const int maxn = 100000;

bool vis[maxn+5];
int prime[maxn+5];
int mu[maxn+5];

void mobius() {
	int tot = 0;
	mu[0] = 0, mu[1] = 1;
	for(int i=2; i<=maxn; ++i) {
		if(!vis[i])
			prime[++tot] = i, mu[i] = -1;
		for(int k=1; k<=tot; ++k) {
			if(LL(prime[k]) * i > maxn) break;
			vis[prime[k] * i] = true;
			if(i % prime[k]) mu[i * prime[k]] = -mu[i];
			else {
				mu[i * prime[k]] = 0;
				break;
			}
		}
	}
	for(int i=1; i<=maxn; ++i) mu[i] += mu[i-1];
}

LL solve(int n)
{
	int m;
	LL res = 0, tmp;
	for(int i=1, nex=0; i<=n; i=nex+1)
	{
		nex = n / (n/i);
		tmp = m = n/i;
		for(int k=1, nex2=0; k*k <= m; k=nex2+1)
		{
			nex2 = sqrt(m / (m/(k*k)));
			tmp -= (LL(m)/(k*k)) * (mu[nex2]-mu[k-1]);
		}
		res += tmp * (nex-i+1);
	}
	return res;
}

int main()
{
	mobius();
	int a, b;
	sf("%d%d", &a, &b);
	pf("%lld\n", solve(b) - solve(a-1));
	return 0;
}
