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

const int maxk = 2000;
const int md = 1e9 + 7;

inline LL PowMod(LL a, LL b) {
	LL res = 1;
	while(b) {
		if(b & 1) res = res * a % md;
		a = a * a % md, b >>= 1;
	}
	return res;
}

LL Fac[maxk + 5], InvFac[maxk + 5], B[maxk + 5];
LL C(int n, int m) { return Fac[n] * InvFac[n - m] % md * InvFac[m] % md; }

int kk;
LL n, R, RN1, inv;
map<int,int> Map;

int S(int k) {
	if(Map.count(k))
		return Map[k];
	LL res;
	if(k == 0) {
		res = (R - RN1 + md) % md * inv % md;
		Map[k] = res;
		return res;
	}
	res = 1;
	for(int i = 0; i <= k - 1; ++i)
		res = (res + C(k, i) * S(i)) % md;
	res = (res * R % md - PowMod(n, k) * RN1 % md + md) % md;
	res = res * inv % md;
	Map[k] = res;
	return res;
}

int Calc2() {
	LL res = 0, tmp;
	tmp = n = (n + 1) % md;
	for(int i = 1; i <= kk + 1; ++i) {
		res = (res + C(kk + 1, i) * B[kk + 1 - i] % md * tmp) % md;
		tmp = tmp * n % md;
	}
	res = res * PowMod(kk + 1, md - 2) % md;
	return res;
}

int main() {
	Fac[0] = 1;
	for(int i = 1; i <= maxk + 2; ++i)
		Fac[i] = Fac[i - 1] * i % md;
	InvFac[maxk + 2] = PowMod(Fac[maxk + 2], md - 2);
	for(int i = maxk + 2 - 1; i >= 0; --i)
		InvFac[i] = InvFac[i + 1] * (i + 1) % md;
	B[0] = 1;
	for(int i = 1; i <= maxk; ++i) {
		LL tmp = 0;
		for(int k = 0; k <= i - 1; ++k)
			tmp = (tmp + C(i + 1, k) * B[k] % md) % md;
		B[i] = (md - tmp) % md * PowMod(i + 1, md - 2) % md;
	}
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%lld%d%lld", &n, &kk, &R);
		if(R == 1) {
			printf("%d\n", Calc2());
			continue;
		}
		R %= md, RN1 = PowMod(R, n + 1);
		inv = PowMod((1 - R + md) % md, md - 2);
		n = (n + 1) % md;
		Map.clear();
		printf("%d\n", S(kk));
	}
	return 0;
}
