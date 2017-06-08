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

const int maxn = 1000;

int n, cnt[maxn + 2];
LL f[maxn + 2][2][2];
LL xi[maxn + 2], yi[maxn + 2], ri[maxn + 2];
vector<int> G[maxn + 2];

LL Dist2(int i, int k) {
	return (xi[i] - xi[k]) * (xi[i] - xi[k]) + (yi[i] - yi[k]) * (yi[i] - yi[k]);
}

void dfs(int x) {
	f[x][0][0] = f[x][0][1] = -ri[x];
	f[x][1][0] = f[x][1][1] = ri[x];
	for(int i = 0; i < G[x].size(); ++i) {
		dfs(G[x][i]);
		f[x][1][0] += f[G[x][i]][0][0];
		f[x][0][0] += f[G[x][i]][1][0];
		f[x][0][1] += f[G[x][i]][1][1];
		f[x][1][1] += f[G[x][i]][0][1];
	}
	f[x][0][1] = f[x][1][0] = max(f[x][1][0], f[x][0][1]);
}

int main() {
	scanf("%d", &n);
	REP(i,1,n) {
		scanf("%lld%lld%lld", xi + i, yi + i, ri + i);
		ri[i] *= ri[i];
	}
	for(int i = 1; i <= n; ++i) {
		int t = 0;
		LL tr = 1LL << 60, tmp;
		for(int k = 1; k <= n; ++k) {
			if(ri[i] >= ri[k]) continue;
			tmp = Dist2(i, k);
			if(tmp <= ri[k]) {
				if(t == 0 || ri[k] < ri[t])
					t = k;
			}
		}
		if(t) {
			G[t].push_back(i);
			++cnt[i];
		}
	}
	LL ans = 0;
	for(int i = 1; i <= n; ++i)
		if(!cnt[i]) {
			dfs(i);
			ans += f[i][1][1];
		}
	printf("%.10f\n", acos(-1.0) * ans);
	return 0;
}
