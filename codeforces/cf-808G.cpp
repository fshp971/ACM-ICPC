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

int n, m;
char ss[maxn+2], tt[maxn+2];
int dp[2][maxn+2], nx[maxn+2][27], f[maxn+2];

int main() {
	scanf("%s%s", ss, tt);
	n = strlen(ss), m = strlen(tt);

	for(int i = 2; i <= m; ++i) {
		int k = f[i-1];
		while(k && tt[k] != tt[i-1])
			k = f[k];
		if(tt[k] == tt[i-1])
			f[i] = k + 1;
	}

	nx[0][tt[0] - 'a'] = 1;
	for(int i = 1; i <= m; ++i) {
		for(int k = 0; k < 26; ++k) {
			if(i < m && k + 'a' == tt[i])
				nx[i][k] = i+1;
			else
				nx[i][k] = nx[f[i]][k];
		}
	}

	int poi = 0, x;
	mem(dp[poi], -1), dp[0][0] = 0;
	for(int i = 1; i <= n; ++i) {
		for(int k = 0; k <= m; ++k) dp[poi^1][k] = -1;
		for(int k = 0; k <= m; ++k) {
			if(dp[poi][k] == -1) continue;
			if(ss[i-1] == '?') {
				for(int c = 0; c < 26; ++c) {
					x = nx[k][c];
					dp[poi^1][x] = max(dp[poi^1][x], dp[poi][k] + ( x == m ? 1 : 0 ) );
				}
			}
			else {
				x = nx[k][ss[i-1] - 'a'];
				dp[poi^1][x] = max(dp[poi^1][x], dp[poi][k] + ( x == m ? 1 : 0 ) );
			}
		}
		poi ^= 1;
	}

	int ans = 0;
	for(int i = 0; i <= m; ++i)
		ans = max(ans, dp[poi][i]);
	printf("%d\n", ans);
	return 0;
}
