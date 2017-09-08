#include<stdio.h>
//#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<queue>
#include<utility>
#include<bitset>
#include<complex>
#include<map>
#include<set>
#include<unordered_map>
#include<unordered_set>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

const int md = 1e9 + 7;
const int maxn = 1e5;

bool vist[maxn + 5];
int prime[maxn + 5], mu[maxn + 5];
LL F[maxn + 5];
void Init() {
	int tot = 0;
	mu[1] = 1;
	for(int i = 2; i <= maxn; ++i) {
		if(!vist[i])
			prime[++tot] = i, mu[i] = -1;
		for(int k = 1; k <= tot; ++k) {
			if((LL)prime[k] * i > maxn) break;
			vist[prime[k] * i] = true;
			if(i % prime[k]) mu[i * prime[k]] = -mu[i];
			else {
				mu[i * prime[k]] = 0;
				break;
			}
		}
	}
	F[0] = 0;
	for(LL i = 1; i <= maxn; ++i)
		F[i] = (F[i - 1] + i * mu[i] + md) % md;
}

unordered_map<int, int> Hash;

inline LL S2(LL l, LL r) {
	return (((l + r) * (r - l + 1)) >> 1) % md;
}

LL G(int n) {
	if(n <= maxn) return F[n];
	if(Hash.count(n)) return Hash[n];
	LL res = 0;
	for(int i = 2, nex = 0; i <= n; i = nex + 1) {
		nex = n / (n / i);
		res = (res + S2(i, nex) * G(n / i) % md) % md;
	}
	res = (1 - res + md) % md;
	Hash[n] = res;
	return res;
}

int main() {
	Init();
	int n;
	LL ans = 0;
	scanf("%d", &n);
	for(int i = 1, nex; i <= n; i = nex + 1) {
		nex = n / (n / i);
		ans = (ans + (G(nex) - G(i - 1) + md) % md * (n / i)) % md;
	}
	ans = ans * ans % md;
	printf("%lld\n", ans);
	return 0;
}
