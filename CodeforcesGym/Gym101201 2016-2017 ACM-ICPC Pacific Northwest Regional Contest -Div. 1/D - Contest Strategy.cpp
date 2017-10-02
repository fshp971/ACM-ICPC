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

int n, kk, aa[maxn + 5];
LL Fac[maxn + 5], f[2][maxn + 5];

bool cmp(const int &a, const int &b) { return a > b; }

int main() {
	Fac[0] = 1;
	for(int i = 1; i <= maxn; ++i) Fac[i] = Fac[i-1] * i % md;
	scanf("%d%d", &n, &kk);
	for(int i = 1; i <= n; ++i) scanf("%d", aa + i);
	sort(aa + 1, aa + 1 + n, cmp);
	int par = 0;
    LL ssum = 0;
	mem(f[par], 0);
	for(int i = 1; i <= kk; ++i) {
        ssum = (ssum + aa[kk - i + 1]) % md;
		f[par][i + kk - 1] = Fac[kk] * ssum % md;
    }
	for(int i = kk + 1; i <= n; ++i) {
		par ^= 1, mem(f[par], 0);
		for(int j = kk; j <= i - 1; ++j) {
			f[par][j] = (Fac[i-1] * aa[i] % md + f[par^1][j-1]) % md * j % md;
			f[par][j] = (f[par][j] + f[par^1][j] * (i - j) % md) % md;
		}
		for(int j = i; j <= kk + i - 1; ++j)
			f[par][j] = (Fac[i-1] * aa[i] % md + f[par^1][j-1]) % md * i % md;
	}
	LL ans = 0;
	for(int i = kk; i <= kk + n - 1; ++i)
		ans = (ans + f[par][i]) % md;
	printf("%lld\n", ans);
	return 0;
}
