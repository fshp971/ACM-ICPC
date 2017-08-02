#include<bits/stdc++.h>

using namespace std;

#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define FOR(i,a,b) for(int i = a; i < b; ++i)
#define mem(a,b) memset(a,b,sizeof(a))
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

const int maxm = 20;
const int maxn = (1 << 19) + 10;
const int md = 998244353;

int m, bit[maxn + 2];
LL InvTwo;
int A[maxn][maxm], B[maxn][maxm], C[maxn][maxm];

LL PowMod(LL a, LL b) {
	LL res = 1;
	while(b) {
		if(b & 1) res = res * a % md;
		a = a * a % md, b >>= 1;
	}
	return res;
}

void FWT(int a[maxn][maxm], int len, int type) {
	for(int l = 1; l < len; l <<= 1) {
		for(int i = 0; i < len; i += (l << 1)) {
			for(int k = 0; k < l; ++k) {
				for(int j = 0; j <= m; ++j) {
					LL x = a[i + k][j], y = a[i + k + l][j];
					a[i + k][j] = (x + y) % md;
					a[i + k + l][j] = (x - y + md) % md;
					if(type == -1) {
						a[i + k][j] = InvTwo * a[i + k][j] % md;
						a[i + k + l][j] = InvTwo * a[i + k + l][j] % md;
					}
				}
			}
		}
	}
}

int main() {
	InvTwo = PowMod(2, md - 2);
	bit[0] = 0;
	for(int i = 1; i <= maxn; ++i)
		bit[i] = bit[i >> 1] + (i & 1);
	int a;
	scanf("%d", &m);
	for(int i = 0; i < (1 << m); ++i) {
		scanf("%d", &a);
		A[i][bit[i]] = LL(a) * (1 << bit[i]) % md;
	}
	for(int i = 0; i < (1 << m); ++i) {
		scanf("%d", &a);
		B[i][bit[i]] = a;
	}
	FWT(A, 1 << m, 1);
	FWT(B, 1 << m, 1);
	for(int i = 0; i < (1 << m); ++i) {
		for(int k = 0; k <= m; ++k)
			for(int j = k; j <= m; ++j) {
				C[i][j - k] = (C[i][j - k] + LL(A[i][k]) * B[i][j]) % md;
			}
	}
	FWT(C, 1 << m, -1);
	LL ans = 0, base = 1;
	for(int i = 0; i < (1 << m); ++i) {
		ans = (ans + base * C[i][bit[i]]) % md;
		base = base * 1526 % md;
	}
	printf("%lld\n", ans);
	return 0;
}
