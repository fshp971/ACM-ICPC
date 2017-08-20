#include<bits/stdc++.h>

using namespace std;

#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define FOR(i,a,b) for(int i = a; i < b; ++i)
#define mem(a,b) memset(a,b,sizeof(a))
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 1e6 + 100;

int n, m, kk, md;
LL Fac[maxn + 2], InvFac[maxn + 2], Pow[maxn + 2];

LL PowMod(LL a, LL b) {
	LL res = 1; a %= md;
	while(b) {
		if(b & 1) res = res * a % md;
		a = a * a % md, b >>= 1;
	}
	return res;
}

int Divide(char *a, int &la, int d, char *b, int &lb) {
	lb = 0;
	int tmp = 0;
	for(int i = 0; i < la; ++i) {
		tmp = tmp * 10 + a[i];
		if(tmp >= d) {
			b[lb++] = tmp / d;
			tmp -= int(b[lb-1]) * d;
		}
		else b[lb++] = 0;
	}
	if(lb == 0) b[lb++] = 0;
	return tmp;
}

char aa[maxn + 5], bb[maxn + 5];
int prime[maxn + 2];
void Init() {
	scanf("%s", aa);
	scanf("%d%d", &kk, &md);
	int len = strlen(aa), tot;
	for(int i = 0; i < len; ++i)
		aa[i] -= '0';
	n = Divide(aa, len, md, bb, tot);
	m = Divide(bb, tot, md - 1, aa, len);
	kk %= (md - 1);

	Fac[0] = 1;
	for(int i = 1; i <= n; ++i)
		Fac[i] = Fac[i-1] * i % md;

	InvFac[n] = PowMod(Fac[n], md - 2);
	for(int i = n - 1; i >= 0; --i)
		InvFac[i] = InvFac[i+1] * (i + 1) % md;

	Pow[0] = 0, Pow[1] = 1, tot = 0;
	for(int i = 2; i <= n; ++i) {
		if(!Pow[i])
			Pow[i] = PowMod(i, kk), prime[++tot] = i;
		for(int k = 1; k <= tot && LL(i) * prime[k] <= n; ++k) {
			Pow[i * prime[k]] = Pow[i] * Pow[prime[k]] % md;
			if(i % prime[k] == 0) break;
		}
	}
}

LL C(int tn, int tm) { return Fac[tn] * InvFac[tn - tm] % md * InvFac[tm] % md; }

int main() {
	Init();
	LL ans = 0;
	int tmp;
	for(int j = 0; j <= n; ++j) {
		tmp = (Pow[j] - Pow[n - j] + md) % md;
		ans = (ans + C(n, j) * tmp % md * tmp) % md;
	}
	ans = ans * PowMod(2, m) % md;
	printf("%lld\n", ans);
	return 0;
}
