//51nod-1190
#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define sf scanf
#define pf printf
typedef long long LL;
typedef pair<int,int> pii;

const int md = 1e9 + 7;
const int maxn = 100000;
const LL inv2 = 500000004;

char vis[maxn+5];
int prime[maxn+5];
int mu[maxn+5];

void mobius() {
	int tot = 0;
	mu[0] = 0, mu[1] = 1;
	for(int i = 2; i <= maxn; ++i) {
		if(!vis[i])
			prime[++tot] = i, mu[i] = -1;
		for(int k = 1; k <= tot; ++k) {
			if(LL(prime[k]) * i > maxn) break;
			vis[prime[k] * i] = true;
			if(i % prime[k]) mu[i * prime[k]] = -mu[i];
			else {
				mu[i * prime[k]] = 0;
				break;
			}
		}
	}
	for(int i = 1; i <= maxn; ++i)
		mu[i] = (mu[i] + md) % md;
		//mu[i] = (mu[i] + md + mu[i-1]) % md;
}

LL S(LL n) {
	return n * (n+1) % md * inv2 % md;
}

LL G(LL n, LL m) {
	LL res = 0;
	for(int i = 1; i*i <= m; ++i) {
		if(m % i) continue;
		res = (res + mu[i] * S(n/i)) % md;
		if(i*i != m)
			res = (res + mu[m/i] * S(n / (m/i))) % md;
	}
	return res;
}

LL F(LL n, LL m) {
	LL res = 0;
	for(LL i = 1; i*i <= m; ++i) {
		if(m % i) continue;
		res = (res + G(n/i, m/i)) % md;
		if(i*i != m)
			res = (res + G(n / (m/i), i)) % md;
	}
	res = res * m % md;
	return res;
}

int main()
{
	mobius();
	int T, a, b;
	sf("%d", &T);
	while(T--) {
		scanf("%d%d", &a, &b);
		printf("%lld\n", (F(b, b) - F(a-1, b) + md) % md);
	}
	return 0;
}
