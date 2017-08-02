#include<bits/stdc++.h>

using namespace std;

#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define FOR(i,a,b) for(int i = a; i < b; ++i)
#define mem(a,b) memset(a,b,sizeof(a))
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

const LL P = 998244353;
const LL G = 3;
const int maxn = 1 << 19;

LL PowMod(LL a, LL b) {
	LL res = 1;
	while(b) {
		if(b & 1) res = res * a % P;
		a = a * a % P, b >>= 1;
	}
	return res;
}

void NTT(LL *a, int len, int type) {
	int i, j, k, l;
	for(int i = 1, j = len >> 1; i < len - 1; ++i) {
		if(i < j) swap(a[i], a[j]);
		k = len >> 1;
		while(j >= k) j -= k, k >>= 1;
		j += k;
	}
	LL var, step, u, v;
	for(l = 2; l <= len; l <<= 1) {
		step = PowMod(G, (P - 1) / l);
		for(k = 0; k < len; k += l) {
			var = 1;
			for(i = k; i < k + l/2; ++i) {
				u = a[i], v = var * a[i+l/2] % P;
				a[i] = (u + v) % P;
				a[i+l/2] = (u - v + P) % P;
				var = var * step % P;
			}
		}
	}
	if(type == -1) {
		for(i = 1; i < len / 2; ++i) swap(a[i], a[len - i]);
		LL inv = PowMod(len, P - 2);
		for(i = 0; i < len; ++i) a[i] = a[i] * inv % P;
	}
}

LL Fac[maxn + 2], InvFac[maxn + 2];
LL A[maxn + 2], B[maxn + 2];
int arr[maxn + 2];

int main() {
	Fac[0] = InvFac[0] = 1;
	for(int i = 1; i <= maxn; ++i) {
		Fac[i] = Fac[i-1] * i % P;
		InvFac[i] = PowMod(Fac[i], P - 2);
	}
	int n, m, len, tmp;
	LL sum;
	while(~scanf("%d", &n)) {
		for(int i = 0; i <= n; ++i)
			scanf("%d", arr + i);
		scanf("%d", &m);
		sum = 0;
		for(int i = 1; i <= m; ++i)
			scanf("%d", &tmp), sum = (sum + tmp) % P;
		sum = (P - sum) % P;
		len = 1;
		while(n + n + 2 > len) len <<= 1;
		for(int i = 0; i < len; ++i) {
			if(i > n) {
				A[i] = B[i] = 0;
				continue;
			}
			A[i] = arr[i] * Fac[i] % P;
			B[i] = InvFac[n - i] * PowMod(sum, n - i);
		}
		NTT(A, len, 1);
		NTT(B, len, 1);
		for(int i = 0; i < len; ++i)
			A[i] = A[i] * B[i] % P;
		NTT(A, len, -1);
		for(int i = 0; i <= n; ++i)
			printf("%lld ", A[i + n] * InvFac[i] % P);
		printf("\n");
	}
	return 0;
}
