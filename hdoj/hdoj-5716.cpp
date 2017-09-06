#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 500;
const int maxm = 2000000;
const int c_size = 62;

int Id(char c) {
	if('0' <= c && c <= '9') return c - '0';
	if('A' <= c && c <= 'Z') return c - 'A' + 10;
	if('a' <= c && c <= 'z') return c - 'a' + 26 + 10;
	return -1;
}

int n;
char arr[maxm + 5];
bitset<maxn + 1> f[c_size], dp;

int main() {
	char str[100];
	int len;
	while(gets(arr)) {
		scanf("%d", &n);
		for(int i = 0; i < c_size; ++i) f[i].reset();
		for(int i = 1; i <= n; ++i) {
			scanf("%d%s", &len, str);
			for(int k = 0; k < len; ++k) {
				f[Id(str[k])][i] = 1;
			}
		}
		dp.reset(), dp[0] = 1;
		int fg = 0;
		for(int i = 0; arr[i] != '\0'; ++i) {
			if(Id(arr[i]) < 0) dp.reset();
			else
				dp = (dp << 1) & f[Id(arr[i])];
			dp[0] = 1;
			if(dp[n] == 1) printf("%d\n", i + 2 - n), fg = 1;
		}
		if(!fg) printf("NULL\n");
		getchar();
	}
	return 0;
}
