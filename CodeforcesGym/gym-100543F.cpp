#include<bits/stdc++.h>

using namespace std;

#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define FOR(i,a,b) for(int i = a; i < b; ++i)
#define mem(a,b) memset(a,b,sizeof(a))
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

const int md = 1e9 + 9;
const int maxn = 1e6;

LL f[2][4], g[28 * 28 * 28 * 28][9];
char arr[3][maxn + 2];

void Init() {
	for(int i = 0; i <= 26; ++i)
		for(int k = 0; k <= 26; ++k)
			for(int j = 0; j <= 26; ++j) {
				for(int st = 0; st < 27; ++st) {
					int p2 = st / 9, p1 = (st - p2 * 9) / 3, p0 = st - p2 * 9 - p1 * 3;
					if((i == 0 && p0 != 0) || (i != 0 && p0 == 0)) continue;
					if((k == 0 && p1 != 0) || (k != 0 && p1 == 0)) continue;
					if((j == 0 && p2 != 0) || (j != 0 && p2 == 0)) continue;
					int msk = 0;
					if(i != 0) msk += (p0 == 1) ? i : 27;
					if(k != 0) msk += ((p1 == 1) ? k : 27) * 28;
					if(j != 0) msk += ((p2 == 1) ? j : 27) * 28 * 28;

					if(i && i == k && k == j) ++g[msk][0];
					if(i == k && k < j) ++g[msk][1];
					if(i == k) ++g[msk][2];
					if(i < k && k == j) ++g[msk][3];
					if(k == j) ++g[msk][4];
					if(i < k && k < j) ++g[msk][5];
					if(i < k) ++g[msk][6];
					if(k < j) ++g[msk][7];
					++g[msk][8];
				}
			}
}

int main() {
	Init();
	int T;
	scanf("%d", &T);
	while(T--) {
		REP(i,0,2) scanf("%s", arr[i]);
		int n0 = strlen(arr[0]), n1 = strlen(arr[1]), n2 = strlen(arr[2]);
		int n = max(n0, max(n1, n2));
		int par = 0, msk;
		mem(f, 0), f[0][0] = 1;
		for(int i = 0; i < n; ++i) {
			par ^= 1, msk = 0;
			if(i < n0) msk += (arr[0][i] == '?') ? 27 : (arr[0][i] - 'a' + 1);
			if(i < n1) msk += ((arr[1][i] == '?') ? 27 : (arr[1][i] - 'a' + 1)) * 28;
			if(i < n2) msk += ((arr[2][i] == '?') ? 27 : (arr[2][i] - 'a' + 1)) * 28 * 28;

			f[par][0] = (f[par^1][0] * g[msk][0]) % md;
			f[par][1] = (f[par^1][0] * g[msk][1] + f[par^1][1] * g[msk][2]) % md;
			f[par][2] = (f[par^1][0] * g[msk][3] + f[par^1][2] * g[msk][4]) % md;
			f[par][3] = (f[par^1][0] * g[msk][5] + f[par^1][1] * g[msk][6] + f[par^1][2] * g[msk][7] + f[par^1][3] * g[msk][8]) % md;
		}
		printf("%lld\n", f[par][3]);
	}
	return 0;
}
