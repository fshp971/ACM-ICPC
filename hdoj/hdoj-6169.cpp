#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 320000;
const int md = 1e9 + 7;

bool vist[maxn + 2];
int prime[maxn + 2], tot;

void GetPrime() {
	prime[tot = 1] = 2;
	for(int i = 3; i <= maxn; i += 2)
		if(!vist[i]) {
			prime[++tot] = i;
			for(LL k = LL(i) * i; k <= maxn; k += i)
				vist[k] = 1;
		}
}

map<pair<LL, int>, LL> Map;

inline LL S2(LL n) {
	if(n & 1) return (((n + 1) >> 1) % md) * (n % md) % md;
	return ((n >> 1) % md) * ((n + 1) % md) % md;
}

LL F(pair<LL, int> x) {
	LL &n = x.first;
	int &m = x.second;
	if(n == 0) return 0;
	if(Map.count(x)) return Map[x];
	LL res = 0;
	if(m == 0) res = S2(n);
	else {
		res = F( MP(n / prime[m], m - 1) ) * prime[m] % md;
		res = (F( MP(n, m - 1) ) - res + md) % md;
	}
	Map[x] = res;
	return res;
}

int main() {
	GetPrime();
	int T, pt, fg;
	LL L, R, K;
	scanf("%d", &T);
	for(int t = 1; t <= T; ++t) {
		scanf("%lld%lld%lld", &L, &R, &K);
		fg = 1, pt = 0;
		for(int i = 1; i <= tot; ++i) {
			if(K == prime[i]) { K = 1, pt = i; break; }
			if(K % prime[i] == 0) { K = 1, fg = 0; break; }
		}
		if(K > 1 && fg == 1) {
			printf("Case #%d: %lld\n", t, (L <= K && K <= R) ? K % md : 0LL);
			continue;
		}
		if(fg == 0) {
			printf("Case #%d: %lld\n", t, 0LL);
			continue;
		}
		printf("Case #%d: %lld\n", t, (F( MP(R / prime[pt], pt - 1) ) - F( MP((L - 1) / prime[pt], pt - 1) ) + md) % md * prime[pt] % md);
	}
	return 0;
}
