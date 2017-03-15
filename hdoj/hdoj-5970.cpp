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
#include<bitset>

using namespace std;

#define MP make_pair
#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define sf scanf
#define pf printf

typedef long long LL;
typedef pair<int,int> pii;

int n, m, p;

void Gcd(LL a, LL b, int &g, int &cont)
{
	LL t;
	cont = 0;
	while(b)
	{
		++cont;
		t = a%b, a = b, b = t;
	}
	g = a;
}

LL Calc(int r, int j)
{
	LL sum = 0, dt, tmp;
	int q, g, cont, tn;
	q = (n-r) / j;
	Gcd(r, j, g, cont);
	r /= g, j /= g;
	dt = LL(j) * j;
	for(int t = 0, T = min(cont-1, q); t <= T; ++t)
	{
		tn = (q-t)/cont + 1;
		tmp = (LL(r+t*j) * j / cont) % p;
		dt = LL(j)*j;
		sum += (tmp + tmp + LL(tn-1)*dt) * tn / 2;
		sum %= p;
	}
	return sum;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int T;
	sf("%d", &T);
	while(T--)
	{
		sf("%d%d%d", &n, &m, &p);
		LL sum = 0;
		REP(j,1,m) FOR(r,0,j)
			sum = (sum+Calc(r, j)) % p;
		printf("%lld\n", sum);
	}
	return 0;
}
