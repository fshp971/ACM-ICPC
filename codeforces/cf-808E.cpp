#include<cstdio>
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

const int maxn = 1e5;

int n, m, tot0, tot1;
vector<LL> W[4];
LL sum[2][maxn+2];

bool cmp(const LL &a, const LL &b) { return a > b; }

LL Odd(int x) {
	if(x == 0) return 0;
	LL res = sum[1][ min(tot1, (x-1) / 2) ];
	if(W[1].size() > 0)
		res += W[1][0];
	return res;
}

LL Even(int x) {
	return sum[0][ min(tot0, x / 2) ];
}

int main() {
	scanf("%d%d", &n, &m);
	int wi, ci;
	for(int i = 1; i <= n; ++i) {
		scanf("%d%d", &wi, &ci);
		W[wi].push_back(ci);
	}
	for(int i = 1; i <= 3; ++i)
		sort(W[i].begin(), W[i].end(), cmp);

	tot0 = tot1 = 0;

	for(int i = 0; i+1 < W[1].size(); i += 2)
		sum[0][++tot0] = W[1][i] + W[1][i+1];

	for(int i = 1; i+1 < W[1].size(); i += 2)
		sum[1][++tot1] = W[1][i] + W[1][i+1];

	for(int i = 0; i < W[2].size(); ++i) {
		sum[0][++tot0] = W[2][i];
		sum[1][++tot1] = W[2][i];
	}

	sort(sum[0] + 1, sum[0] + 1 + tot0, cmp);
	sort(sum[1] + 1, sum[1] + 1 + tot1, cmp);

	for(int i = 1; i <= tot0; ++i)
		sum[0][i] += sum[0][i-1];
	for(int i = 1; i <= tot1; ++i)
		sum[1][i] += sum[1][i-1];
	for(int i = 1; i < W[3].size(); ++i)
		W[3][i] += W[3][i-1];

	LL ans = max( Odd(m), Even(m) );
	for(int i = 1; i*3 <= m && i-1 < W[3].size(); ++i) {
		ans = max(ans, W[3][i-1] + max( Odd(m - i*3), Even(m - i*3) ) );
	}
	printf("%lld\n", ans);
	return 0;
}
