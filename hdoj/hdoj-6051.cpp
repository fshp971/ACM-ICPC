#include<bits/stdc++.h>

using namespace std;

#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define FOR(i,a,b) for(int i = a; i < b; ++i)
#define mem(a,b) memset(a,b,sizeof(a))
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 1e6;
const int md = 1e9 + 7;

int Phi[maxn + 2];
LL InvTwo;

LL PowMod(LL a, LL b) {
	LL res = 1;
	while(b) {
		if(b & 1) res = res * a % md;
		a = a * a % md, b >>= 1;
	}
	return res;
}

void PhiMaker() {
	Phi[1] = 1;
	for(int i = 2; i <= maxn; ++i) if(!Phi[i]) {
		for(int k = i; k <= maxn; k += i) {
			if(!Phi[k]) Phi[k] = k;
			Phi[k] = Phi[k] / i * (i - 1);
		}
	}
}

LL Euler(int x) {
	if(x <= maxn) return Phi[x];
	LL res = x, a = x;
	for(LL i = 2; i * i <= a; ++i) {
		if(a % i == 0) {
			res = res / i * (i - 1);
			while(a % i == 0) a /= i;
		}
	}
	if(a > 1) res = res / a * (a - 1);
	return res;
}

LL Calc(LL n) {
	LL res = n * Euler(n) % md;
	if(n == 1) ++res;
	return res * InvTwo % md;
}

int main() {
	InvTwo = PowMod(2, md - 2);
	PhiMaker();
	int T, m, p;
	scanf("%d", &T);
	for(int t = 1; t <= T; ++t) {
		scanf("%d%d", &m, &p);
		LL ans = LL(p) * (p - 1) / 2;
		ans = -ans + (ans / md + 1) * md;
		while(ans < 0) ans += md;
		ans %= md;
		for(LL d = 1; d * d <= p - 1; ++d) {
			if((p-1) % d) continue;
			ans = (ans + d * d * Calc( (p-1) / d )) % md;
			if(d * d != (p-1))
				ans = (ans + ((p-1)/d) * ((p-1)/d) * Calc(d)) % md;
		}
		ans = ans * m % md;
		printf("Case #%d: %lld\n", t, ans);
	}
	return 0;
}
