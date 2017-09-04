#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

LL PowMod(LL a, LL b, LL md) {
	LL res = 1;
	while(b) {
		if(b & 1) res = res * a % md;
		a = a * a % md, b >>= 1;
	}
	return res;
}

int main() {
	int n, a, md;
	while(~scanf("%d%d", &n, &a)) {
		if(a & 1) printf("1\n");
		else {
			int ans = 0, c;
			md = 1 << n;
			for(int i = 1; i < n; ++i)
				if(PowMod(a, i, md) == PowMod(i, a, md))
					++ans;
			c = 1 << (int)ceil(double(n) / a);
			ans += md / c - (n - 1) / c;
			printf("%d\n", ans);
		}
	}
	return 0;
}
