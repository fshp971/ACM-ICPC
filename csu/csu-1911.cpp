#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = (1 << 18) + 100;
const int md = 1e9 + 7;

void FWT(LL *tA, int len, int type) {
	for(int l = 1; l < len; l <<= 1) {
		for(int i = 0; i < len; i += (l << 1)) {
			for(int k = 0; k < l; ++k) {
				LL x = tA[i + k], y = tA[i + k + l];
				if(type == 0)
					tA[i + k + l] = (x + y) % md;
				else
					tA[i + k + l] = (y - x + md) % md;
			}
		}
	}
}

LL A[maxn + 2], B[maxn + 2];

int main() {
	int T, len, tmp, n, m;
	char aa[30];
	scanf("%d", &T);
	for(int t = 1; t <= T; ++t) {
		printf("Case #%d:\n", t);
		scanf("%d%d", &n, &m);
		len = 1 << m;

		mem(A, 0), mem(B, 0);
		for(int i = 1; i <= n; ++i) {
			scanf("%s", aa), tmp = 0;
			int l = strlen(aa);
			for(int k = 0; k < l; ++k)
				tmp = (tmp << 1) + aa[k] - '0';
			++A[tmp];
		}
		for(int i = 1; i <= n; ++i) {
			scanf("%s", aa), tmp = 0;
			int l = strlen(aa);
			for(int k = 0; k < l; ++k)
				tmp = (tmp << 1) + aa[k] - '0';
			++B[tmp];
		}

		FWT(A, len, 0);
		FWT(B, len, 0);
		for(int i = 0; i < len; ++i)
			A[i] = A[i] * B[i] % md;
		FWT(A, len, 1);
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i) {
			scanf("%s", aa), tmp = 0;
			int l = strlen(aa);
			for(int k = 0; k < l; ++k)
				tmp = (tmp << 1) + aa[k] - '0';
			printf("%lld\n", A[tmp]);
		}
	}
	return 0;
}
