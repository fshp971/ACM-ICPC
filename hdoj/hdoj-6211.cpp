#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 31623;
const int lim = 1e9;
const int md = (1 << 17) - 1;

bool vist[maxn + 5];
int f[md + 5];

void Init() {
	for(int i = 1; i <= maxn; i += 2) {
		mem(vist, 0);
		int tmp = i, ii = i*i;
		for(int k = 2; k*k <= i; ++k) {
			if(tmp % k) continue;
			while(tmp%k == 0) tmp /= k;
			for(int j = k; j <= maxn; j += k)
				vist[j] = 1;
		}
		if(tmp > 1)
			for(int j = tmp; j <= maxn; j += tmp)
				vist[j] = 1;
		for(int k = 2; k*k + ii <= lim; k += 2) {
			if(vist[k]) continue;
			int a = abs(ii - k*k), b = 2*i*k;
			if(a < b) ++f[b & md];
			else ++f[a & md];
		}
	}
}

int aa[md + 5];

int main() {
	Init();
	int T, n;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		n = (1 << n) - 1;
		for(int i = 0; i <= n; ++i)
			scanf("%d", aa + i);
		LL ans = 0;
		for(int i = 0; i <= md; ++i) {
			ans += aa[i&n] * f[i];
		}
		printf("%lld\n", ans);
	}
	return 0;
}
