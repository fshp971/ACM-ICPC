#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<queue>
#include<string>
#include<vector>
#include<utility>
#include<map>
#include<set>

using namespace std;

#define LL long long
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define pii pair<int,int>
#define MP(a,b) make_pair(a,b)
#define mem(a,b) memset(a,b,sizeof(a))
#define sf scanf
#define pf printf

const LL md = 1e9 + 7;

LL pow_mod(LL a, LL b)
{
	LL res = 1;
	while(b)
	{
		if(b&1) res =res*a % md;
		a = a*a % md, b >>= 1;
	}
	return res;
}

int main()
{
	LL a, b, c;
	//cin >> a >> b >> c;
	sf("%lld%lld%lld", &a, &b, &c);
	//cout << pow_mod(2, c) << "\n";
	pf("%lld\n", pow_mod(2, c) );
	return 0;
}
