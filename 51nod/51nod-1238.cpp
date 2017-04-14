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
const int mo = 2939, step = 103;
const LL md = 1e9 + 7;
const LL inv2 = 500000004, inv6 = 166666668;

int Phi[maxn+5];
unordered_map<LL, int> Hash;

void PhiMaker() {
	Phi[0] = 0, Phi[1] = 1;
	for(int i = 2; i <= maxn; ++i) if(!Phi[i]) {
		for(int k = i; k <= maxn; k += i) {
			if(!Phi[k]) Phi[k] = k;
			Phi[k] = Phi[k] / i * (i-1);
		}
	}
	for(int i = 1; i <= maxn; ++i)
		Phi[i] = (LL(i) * i % md * Phi[i] % md + Phi[i-1]) % md;
}

inline LL S2(LL n) {
	n %= md;
	return (n*2+1) % md * (n+1) % md * n % md * inv6 % md;
}

LL F(LL n) {
	if(n <= maxn) return Phi[n];
	if(Hash.count(n)) return Hash[n];
	LL res = 0, tmp;
	for(LL i = 2, nex = 0; i <= n; i = nex+1) {
		nex =  n / (n/i);
		tmp = (S2(nex) - S2(i-1) + md) % md * F(n/i) % md;
		res = (res + tmp) % md;
	}
	tmp = (n+1) % md * (n%md) % md * inv2 % md;
	res = (tmp * tmp % md - res + md + md) % md;
	Hash[n] = res;
	return res;
}

int main()
{
	LL n, ans = 0;
	sf("%lld", &n);
	PhiMaker();
	for(LL i = 1, tmp, nex = 0; i <= n; i = nex+1) {
		nex = n / (n/i);
		tmp = (nex-i+1) % md * ((nex+i)%md) % md * inv2 % md * F(n/i) % md;
		ans = (ans + tmp) % md;
	}
	pf("%lld\n", ans);
	return 0;
}
