//#include<cstdio>
#include<stdio.h> //垃圾51nod xjb卡读入
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<iostream>
#include<algorithm>
#include<queue>
#include<vector>
#include<string>
#include<map>
#include<set>
#include<unordered_map>
#include<unordered_set>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define sf scanf
#define pf printf
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;

const int md = 1e9 + 7;
const int maxn = 40000;
const LL inv2 = 500000004;

int tot;
LL prime[maxn+5];
char vis[maxn+5];

//感觉vector有点慢啊……
vector<pii> arr;
vector<LL> fact;

void GetPrime() {
	prime[tot = 1] = 2;
	for(LL i = 3; i <= maxn; i += 2)
		if(!vis[i]) {
			prime[++tot] = i;
			for(LL k = i * i; k <= maxn; k += i)
				vis[k] = 1;
		}
}

void dfs(int id, LL now) {
	if(id >= arr.size()) {
		fact.push_back(now);
		return;
	}
	for(int i = 0; i <= arr[id].second; ++i) {
		dfs(id+1, now);
		now *= arr[id].first;
	}
}

void GetFact(LL n) {
	arr.clear();
	pii tmp;
	for(int i = 1; i <= tot; ++i) {
		if(prime[i] * prime[i] > n) break; //关键优化
		if(n % prime[i]) continue;
		tmp.first = prime[i], tmp.second = 0;
		while(n % prime[i] == 0) n /= prime[i], ++tmp.second;
		arr.push_back(tmp);
	}
	if(n > 1)
		arr.push_back( MP(n, 1) );
	fact.clear();
	dfs(0, 1);
}

LL F(LL n) {
	LL res = 1;
	for(int i = 0; i < arr.size(); ++i) {
		if(n < arr[i].first) break;
		if(n % arr[i].first) continue;
		while(n % arr[i].first == 0) n /= arr[i].first;
		res = (1 - arr[i].first + md) % md * res % md;
	}
	return res;
}

int main()
{
	GetPrime();
	int T;
	LL a, b;
	LL res, tmp, ll, rr;
	sf("%d", &T);
	while(T--) {
		scanf("%lld%lld", &a, &b);
		GetFact(b);
		res = 0;
		for(int i = 0; i < fact.size(); ++i) {
			ll = LL(a - 1) / fact[i] + 1, rr = LL(b) / fact[i];
			tmp = (ll + rr) % md * ((rr - ll + 1) % md) % md * inv2 % md * F(fact[i]) % md;
			res = (res + tmp) % md;
		}
		res = res * b % md;
		printf("%lld\n", res);
	}
	return 0;
}
