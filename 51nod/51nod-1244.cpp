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
#include<unordered_map>
#include<set>
#include<unordered_set>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define sf scanf
#define pf printf
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 6e6;

unordered_map<LL, LL> Hash;
bool vis[maxn+5];
int prime[maxn+5];
int mu[maxn+5];

void mobius() {
	mem(vis, 0);
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
		mu[i] += mu[i-1];
}

LL S(LL n) {
	if(n <= maxn) return mu[n];
	if(Hash.count(n)) return Hash[n];
	LL res = 0;
	for(LL i = 2, nex = 0; i <= n; i = nex+1) {
		nex = n / (n/i);
		res += S(n/i) * (nex - i + 1);
	}
	res = 1 - res;
	Hash[n] = res;
	return res;
}

int main() {
	mobius();
	LL a, b;
	sf("%lld%lld", &a, &b);
	printf("%lld\n", S(b) - S(a-1));
	return 0;
}
