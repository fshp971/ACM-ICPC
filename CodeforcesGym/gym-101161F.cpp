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

const int maxnode = 2e6;

int tot, SG[maxnode + 2], nx[maxnode + 2][26];

void Insert(int x, char *arr, int rem) {
	if(!rem) return;
	if(nx[x][arr[0] - 97] == -1) {
		SG[tot] = 0;
		mem(nx[tot], -1);
		nx[x][arr[0] - 97] = tot++;
	}
	else
		SG[x] ^= SG[nx[x][arr[0] - 97]] + 1;
	Insert(nx[x][arr[0] - 97], arr + 1, rem - 1);
	SG[x] ^= SG[nx[x][arr[0] - 97]] + 1;
}

int main() {
	int T, n;
	char arr[50];
	scanf("%d", &T);
	for(int t = 1; t <= T; ++t) {
		printf("Case %d:\n", t);
		scanf("%d", &n);
		tot = 1, SG[0] = 0, mem(nx[0], -1);
		for(int i = 0; i < n; ++i) {
			scanf("%s", arr);
			Insert(0, arr, strlen(arr));
		}
		scanf("%d", &n);
		for(int i = 0; i < n; ++i) {
			scanf("%s", arr);
			Insert(0, arr, strlen(arr));
			printf("%d\n", SG[0] ? 1 : 2);
		}
	}
	return 0;
}
