#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 50;
const int maxd = 10000;

int n, m, dd;
vector<int> G[maxn+5];
double pro[maxn+5], f[maxd+5][maxn+5];

double Run(int x) {
	for(int i = 1; i <= n; ++i) {
		if(i == x) f[0][i] = 0.0;
		else f[0][i] = double(1) / n;
	}
	for(int i = 1; i <= dd; ++i) {
		for(int k = 1; k <= n; ++k) {
			f[i][k] = 0.0;
			if(k == x) continue;
			for(int j = 0; j < G[k].size(); ++j)
				f[i][k] += f[i-1][G[k][j]] * pro[G[k][j]];
		}
	}
	double ans = 0.0;
	for(int i = 1; i <= n; ++i)
		ans += f[dd][i];
	return ans;
}

int main() {
	int T, a, b;
	scanf("%d", &T);
	while(T--) {
		scanf("%d%d%d", &n, &m, &dd);
		mem(pro, 0);
		REP(i,1,n) G[i].clear();
		for(int i = 1; i <= m; ++i) {
			scanf("%d%d", &a, &b);
			G[a].push_back(b);
			G[b].push_back(a);
			pro[a] += 1.0, pro[b] += 1.0;
		}
		REP(i,1,n) pro[i] = double(1) / pro[i];
		for(int i = 1; i <= n; ++i) {
			printf("%.10f\n", Run(i));
		}
	}
	return 0;
}
