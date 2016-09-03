#include<bits/stdc++.h>

using namespace std;

#define LL long long
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define pii pair<int,int>
#define mem(a,b) memset(a,b,sizeof(a))
#define MP(a,b) make_pair(a,b)
#define sf scanf
#define pf printf

#define lld I64d

const int md = 2520;

LL f[20][md+5][50];
int _hash[md+5];
int number[20];

LL gcd(LL a, LL b){ return b ? gcd(b, a%b) : a; }
LL lcm(LL a, LL b){ return a / gcd(a, b) * b; }

LL dfs(int poi, int _mul, int _lcm, char flag)
{
	if(!poi) return _mul % _lcm == 0;
	if(flag && f[poi][_mul][_hash[_lcm]] != -1) return f[poi][_mul][_hash[_lcm]];
	int range = flag ? 9 : number[poi];
	int n_mul, n_lcm;
	LL res = 0;
	for(int i=0; i<=range; ++i)
	{
		n_mul = (_mul*10 + i) % md;
		n_lcm = i ? lcm(_lcm, i) : _lcm;
		res += dfs(poi-1, n_mul, n_lcm, flag || i!=number[poi]);
	}
	if(flag) f[poi][_mul][_hash[_lcm]] = res;
	return res;
}

LL calc(LL x)
{
	if(!x) return 1;
	int top = 0;
	while(x)
	{
		number[++top] = x%10;
		x /= 10;
	}
	return dfs(top, 0, 1, 0);
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	mem(f, -1);
	mem(_hash, 0);
	int top = 0;
	for(int i=1; i<=md; ++i)
		if(md%i == 0)
			_hash[i] = top++;

	int T;
	LL l, r;
	sf("%d", &T);
	while(T--)
	{
		sf("%lld%lld", &l, &r);
		pf("%lld\n", calc(r) - calc(l-1));
	}
	return 0;
}
