#include<bits/stdc++.h>

using namespace std;

#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define mem(a,b) memset(a,b,sizeof(a))
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;

LL Gcd(LL a, LL b) { return b ? Gcd(b, a%b) : a; }

void Ex_Gcd(LL a, LL b, LL &g, LL &x, LL &y) {
	if(b == 0) g = a, x = 1, y = 0;
	else Ex_Gcd(b, a%b, g, y, x), y -= (a/b) * x;
}

int main() {
	int T, K, sk;
	LL xa, ya, xb, yb, A, B, g, x, y;
	vector<pll> arr;
	scanf("%d", &T);
	while(T--) {
		scanf("%lld%lld%lld%lld%d", &xa, &ya, &xb, &yb, &K);
		A = ya - yb;
		B = -(xa - xb);
		Ex_Gcd(abs(A), abs(B), g, x, y);
		if(A < 0) x = -x;
		if(B < 0) y = -y;
		x += xb, y += yb;
		arr.clear();
		pll vec = MP( (xa - xb) / g, (ya - yb) / g );
		for(int i = 0; i < K; ++i) {
			printf("%lld %lld\n", x, y);
			x += vec.first, y += vec.second;
		}
	}
	return 0;
}
