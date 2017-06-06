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

const int maxn = 5000;

int n, f[maxn + 2][maxn + 2];
int aa[maxn + 2], bb[maxn + 2], cc[maxn + 2], dd[maxn + 2];
int MxMod[maxn + 2][7], MxNum[maxn + 2][maxn + 2];

int tot;
map<int, int> Map;

int main() {
	scanf("%d", &n);
	tot = 0;
	for(int i = 1; i <= n; ++i) {
		scanf("%d", aa + i);
		if(!Map.count(aa[i]))
			Map[aa[i]] = ++tot;
		dd[i] = Map[aa[i]];
		if(Map.count(aa[i] + 1))
			bb[i] = Map[aa[i] + 1];
		if(Map.count(aa[i] - 1))
			cc[i] = Map[aa[i] - 1];
	}
	int ans = 0;
	for(int i = 1; i <= n; ++i)
		for(int j = 0; j < i; ++j) {
			f[i][j] = 1 + max( max(MxMod[j][aa[i] % 7], f[j][0]), max(MxNum[j][bb[i]], MxNum[j][cc[i]]) );
			ans = max(ans, f[i][j]);
			MxMod[j][aa[i] % 7] = max(MxMod[j][aa[i] % 7], f[i][j]);
			MxNum[j][dd[i]] = max(MxNum[j][dd[i]], f[i][j]);
			if(j) {
				MxMod[i][aa[j] % 7] = max(MxMod[i][aa[j] % 7], f[i][j]);
				MxNum[i][dd[j]] = max(MxNum[i][dd[j]], f[i][j]);
			}
		}
	printf("%d\n", ans);
	return 0;
}
