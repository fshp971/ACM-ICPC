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

const int maxn = 100;

int n;
LL ai[maxn + 2], lim;

inline LL Ceil(LL a, LL b) {
	if(a % b) return a / b + 1;
	return a / b;
}

LL FindNext(LL a, LL d) {
	if(a < d) return lim;
	LL now = Ceil(a,d), res;
	if(a % d == 0)
		res = d;
	else {
		res = a / (a/d);
		if(a % (res + 1) == 0)
			++res;
	}
	return res;
}

int main() {
	scanf("%d%lld", &n, &lim);
	REP(i,1,n) scanf("%lld", ai + i), lim += ai[i];
	LL ans = 0;
	for(LL d = 1, nex = 0; d <= lim; d = nex + 1) {
		LL sum = 0;
		nex = lim;
		REP(i,1,n) {
			sum += Ceil(ai[i], d);
			nex = min(nex, FindNext(ai[i], d));
		}
		LL l = d, r = nex, mid;
		while(l <= r) {
			mid = (l + r) >> 1;
			if(mid * sum <= lim)
				ans = mid, l = mid + 1;
			else r = mid - 1;
		}
	}
	printf("%lld\n", ans);
	return 0;
}
