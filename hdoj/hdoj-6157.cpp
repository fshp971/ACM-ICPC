#include<bits/stdc++.h>

using namespace std;

#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define FOR(i,a,b) for(int i = a; i < b; ++i)
#define mem(a,b) memset(a,b,sizeof(a))
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 100;

int n, m;
int arr[maxn + 2];
int f[2][maxn + 2][maxn + 2];

int main() {
	while(~scanf("%d%d", &n, &m)) {
		scanf("%d", &arr[0]);
		for(int i = 2; i <= n; ++i)
			scanf("%d", arr + i), arr[i] += arr[i-1];
		int par = 0, ans = -(1 << 30);
		mem(f[par], 0x80);
		f[par][0][0] = 0;
		for(int i = 1; i <= n; ++i) {
			par ^= 1;
			mem(f[par], 0x80);
			for(int k = 0; k <= m; ++k) {
				for(int p = 0; p <= m; ++p) {
					f[par][k][p] = f[par^1][k][p];
					if(k >= 1) {
						f[par][k][p] = max(f[par][k][p], f[par^1][k-1][p]);
						f[par][k][p] = max(f[par][k][p], f[par^1][k-1][p+1] + arr[i] * 2 + arr[0]);
						if(p >= 1)
							f[par][k][p] = max(f[par][k][p], f[par^1][k-1][p-1] - arr[i] * 2 + arr[0]);
					}
				}
			}
			ans = max(ans, f[par][m][0]);
		}
		printf("%d\n", ans);
	}
	return 0;
}
