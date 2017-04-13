#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<iostream>
#include<algorithm>
#include<string>
#include<queue>
#include<utility>
#include<unordered_map>
#include<map>
#include<set>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define sf scanf
#define pf printf
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 5e6;
const int md = 1e9 + 7;
const LL inv2 = 500000004;

int Phi[maxn+5];
unordered_map<LL,LL> Hash;

void PhiMaker() {
	Phi[0] = 0, Phi[1] = 1;
	for(int i = 2; i <= maxn; ++i) if(!Phi[i]) {
		for(int k = i; k <= maxn; k += i) {
			if(!Phi[k]) Phi[k] = k;
			Phi[k] = Phi[k] / i * (i-1);
		}
	}
	for(int i = 1; i <= maxn; ++i)
		Phi[i] = (Phi[i] + Phi[i-1]) % md;
}

LL F(LL n) {
	if(n <= maxn) return Phi[n];
	if(Hash.count(n)) return Hash[n];
	LL res = 0;
	for(LL i = 2, nex = 0; i <= n; i = nex+1) {
		nex = n / (n/i);
		res = (res + (nex-i+1) % md * F(n/i) % md) % md;
	}
	res = ((n+1)%md * (n%md) % md * inv2 % md - res + md) % md;
	Hash[n] = res;
	return res;
}

int main() {
	PhiMaker();
	LL n, ans = 0;
	sf("%lld", &n);
	for(LL i = 1, j, tmp, nex = 0; i <= n; i = nex+1) {
		j = n/i, nex = n / j, j %= md;
		tmp = (F(nex) - F(i-1) + md) % md * j % md * j % md;
		ans = (ans+tmp) % md;
	}
	pf("%lld\n", ans);
	return 0;
}
