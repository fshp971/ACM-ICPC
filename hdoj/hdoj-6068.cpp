#include<bits/stdc++.h>

using namespace std;

#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define FOR(i,a,b) for(int i = a; i < b; ++i)
#define mem(a,b) memset(a,b,sizeof(a))
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 100000 + 5;
const int maxm = 200 + 5;

void KMP(char *s, int n, char *t, int m, LL ff[][maxm]) {
	static int u, fail[maxn + 2];
	fail[1] = 0;
	for(int i = 2; i <= m; ++i) {
		u = fail[i - 1];
		while(u && t[u] != t[i - 1])
			u = fail[u];
		fail[i] = (t[u] == t[i - 1]) ? (u + 1) : 0;
	}
	u = 0;
	for(int i = 1; i <= n; ++i) {
		for(int k = 0; k <= m; ++k)
			ff[i][k] = ff[i - 1][k];
		while(u && s[i - 1] != t[u])
			u = fail[u];
		if(s[i - 1] == t[u])
			++u;
		int v = u;
		while(v) {
			++ff[i][v];
			v = fail[v];
		}
		if(u == m)
			u = fail[u];
	}
	for(int i = 1; i <= n; ++i)
		ff[i][m] += ff[i - 1][m];
}

LL f[2][maxn][maxm];
char ss[maxn], tt[maxm];

int main() {
	int T, n, m, kk, l, r;
	scanf("%d", &T);
	while(T--) {
		scanf("%d%d%d", &n, &m, &kk);
		scanf("%s", ss);
		scanf("%s", tt);

		KMP(ss, n, tt, m, f[0]);
		reverse(ss, ss + n);
		reverse(tt, tt + m);
		KMP(ss, n, tt, m, f[1]);

		while(kk--) {
			scanf("%d%d", &l, &r);
			LL ans = f[0][l][m] * (n - r + 1) + f[1][n - r + 1][m] * l;
			for(int i = 1; i < m; ++i)
				ans += f[0][l][i] * f[1][n - r + 1][m-i];
			printf("%lld\n", ans);
		}
	}
	return 0;
}
