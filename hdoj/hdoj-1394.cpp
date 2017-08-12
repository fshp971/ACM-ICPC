#include<bits/stdc++.h>

using namespace std;

#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define FOR(i,a,b) for(int i = a; i < b; ++i)
#define mem(a,b) memset(a,b,sizeof(a))
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 5000;

int n, arr[maxn + 2];
int tree[maxn + 2];

void Add(int x, int del) {
	for(; x <= n; x += x & (-x))
		tree[x] += del;
}

int Sum(int x) {
	int res = 0;
	for(; x > 0; x -= x & (-x))
		res += tree[x];
	return res;
}

int main() {
	while(~scanf("%d", &n)) {
		int ans = 0;
		for(int i = 1; i <= n; ++i)
			scanf("%d", arr + i), ++arr[i], tree[i] = 0;
		for(int i = 1; i <= n; ++i) {
			ans += Sum(n) - Sum(arr[i]);
			Add(arr[i], 1);
		}
		int tmp = ans;
		for(int i = 1; i <= n; ++i) {
			Add(arr[i], -1);
			//tmp -= Sum(arr[i]);
			tmp += Sum(n) - 2 * Sum(arr[i]);
			ans = min(ans, tmp);
			Add(arr[i], 1);
		}
		printf("%d\n", ans);
	}
	return 0;
}
