//http://codeforces.com/gym/101201/attachments
#include<bits/stdc++.h>

using namespace std;

#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define FOR(i,a,b) for(int i = a; i < b; ++i)
#define mem(a,b) memset(a,b,sizeof(a))
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 650;
const int md = 1e9 + 7;

inline LL PowMod(LL a, LL b) {
	LL res = 1;
	while(b) {
		if(b&1) res = res * a % md;
		a = a * a % md; b >>= 1;
	}
	return res;
}

int n, kk, aa[maxn + 5];
LL Fac[maxn + 5], InvFac[maxn + 5];
unordered_map<int,int> Map;
LL f[2][maxn + 5];

bool cmp(const int &a, const int &b) { return a > b; }

int main() {
	Fac[0] = 1;
	for(int i = 1; i <= maxn; ++i) Fac[i] = Fac[i-1] * i % md;
	InvFac[maxn] = PowMod(Fac[maxn], md - 2);
	for(int i = maxn - 1; i >= 0; --i)
		InvFac[i] = InvFac[i+1] * (i+1) % md;

	scanf("%d%d", &n, &kk);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", aa + i);
		if(!Map.count(aa[i])) Map[aa[i]] = 1;
		else ++Map[aa[i]];
	}
	sort(aa + 1, aa + 1 + n, cmp);
	//for(int i = 1; i <= n; ++i) printf("aa[%d] = %d\n", i, aa[i]);
	int par = 0;
	mem(f[par], 0);
	for(int i = 1; i <= kk; ++i)
		f[par][i + kk - 1] = aa[kk - i + 1];
	///*
	for(int i = 0; i <= n + kk - 1; ++i)
		printf("f[par][%d] = %lld\n", i, f[par][i]);
	printf("\n");
	//*/
	for(int i = kk + 1; i <= n; ++i) {
		par ^= 1, mem(f[par], 0);
		for(int j = kk; j <= kk + i - 1; ++j) {
			LL tmp = (Fac[i-1] * InvFac[i-j+kk-2] % md * aa[i] % md + f[par^1][j-1]) % md;
			f[par][j] = f[par^1][j] * Fac[i-1] % md * (i-j+kk-1) % md;
			f[par][j] = (f[par][j] + tmp * (j-kk+1) % md) % md;
			//f[par][j] = Fac[i-1] * InvFac[i-j] % md * aa[i] % md * j % md;
			//f[par][j] = (f[par][j] + f[par^1][j] * (i+kk-1-j) + f[par^1][j-1]) % md;
		}
	}
	LL ans = 0;
	for(int i = kk; i <= kk + n - 1; ++i)
		printf("f[par][%d] = %lld\n", i, f[par][i]);
	for(int i = kk; i <= kk + n - 1; ++i)
		ans = (ans + f[par][i]) % md;
	printf("%lld\n", ans);
	return 0;
}
