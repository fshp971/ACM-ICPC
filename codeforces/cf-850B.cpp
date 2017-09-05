#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 1e6;

int n, xx, yy;
LL sum[(maxn << 1) + 100];
int cnt[(maxn << 1) + 100];

int main() {
	int u;
	scanf("%d%d%d", &n, &xx, &yy);
	for(int i = 1; i <= n; ++i)
		scanf("%d", &u), ++cnt[u];
	for(int i = 1; i <= (maxn << 1); ++i) {
		sum[i] = sum[i-1] + LL(cnt[i]) * i;
		cnt[i] += cnt[i-1];
	}
	LL ans = 1LL << 60, tmp;
	int cont = xx / yy;
	for(int i = 2; i <= maxn; ++i) {
		tmp = 0;
		for(int k = 0; k <= maxn; k += i) {
			int mid = max((k + i) - cont, k + 1);
			tmp += yy * (LL(cnt[k + i] - cnt[mid - 1]) * LL(k + i) - (sum[k + i] - sum[mid - 1]));
			tmp += xx * LL(cnt[mid - 1] - cnt[k]);
		}
		ans = min(ans, tmp);
	}
	printf("%lld\n", ans);
	return 0;
}
