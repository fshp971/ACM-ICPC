#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define FOR(i,a,b) for(int i = a; i < b; ++i)
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 200000;

int n, col[maxn + 2], sum[maxn + 2], sz[maxn + 2];
LL ans;
vector<int> G[maxn + 2];

void dfs(int x, int par) {
	int add = 1, pre;
	sz[x] = 1;
	for(int i = 0; i < G[x].size(); ++i) {
		if(G[x][i] == par) continue;
		pre = sum[col[x]];
		dfs(G[x][i], x);
		sz[x] += sz[G[x][i]];
		LL tmp = sz[G[x][i]] - (sum[col[x]] - pre);
		ans -= tmp * (tmp - 1) / 2;
		add += tmp;
	}
	sum[col[x]] += add;
}

int main() {
	int u, v, cas = 0;
	while(~scanf("%d", &n)) {
		REP(i,1,n) {
			scanf("%d", col + i);
			G[i].clear(), sum[i] = 0;
		}
		for(int i = 1; i < n; ++i) {
			scanf("%d%d", &u, &v);
			G[u].push_back(v);
			G[v].push_back(u);
		}
		ans = LL(n) * n * (n-1) / 2;
		dfs(1, 0);
		for(int i = 1; i <= n; ++i) {
			LL tmp = n - sum[i];
			ans -= tmp * (tmp - 1) / 2;
		}
		printf("Case #%d: %lld\n", ++cas, ans);
	}
	return 0;
}
