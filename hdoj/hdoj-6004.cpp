#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<string>
#include<queue>
#include<utility>
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
typedef __int128 Lint;
typedef pair<int,int> pii;

const int maxn = 200;

struct Equ
{
	LL a, b;
	Equ(): a(-1), b(-1) {}
	Equ(LL _a, LL _b) { a = _a, b = _b; }
}pre[maxn+2][maxn*(maxn+1)/2+2];

int n, m;

inline int CalcPoi(int i, int k) { return (2*m+2-i)*(i-1)/2 + k-i+1; }

void ex_gcd(LL a, LL b, LL &g, LL &x, LL &y) {
	if(b == 0) g = a, x = 1, y = 0;
	else ex_gcd(b, a%b, g, y, x), y -= (a/b)*x;
}

Equ Calc(Equ &l, Equ &r)
{
	if(l.a == -1 || r.a == -1) return Equ(-1, -1);
	LL x, y, g;
	LL p, m_a3;
	Lint a3, b3;
	LL &a1 = l.a, &b1 = l.b, &a2 = r.a, &b2 = r.b;
	ex_gcd(b1, b2, g, x, y), y = -y;
	if((a2-a1)%g)
		return Equ(-1, -1);
	p = (a2-a1)/g;
	Lint tx = x, ty = y;
	tx *= p, ty *= p;
	m_a3 = max(a1, a2);
	a3 = a1 + b1*tx, b3 = b1 / g * b2;
	if(a3 < m_a3)
		a3 += ((m_a3-a3)/b3 + 1) * b3;
	if(a3 >= m_a3)
		a3 -= ((a3-m_a3)/b3) * b3;
	return Equ(a3, b3);
}

int main()
{
	int T, que, x1, y1, x2, y2;
	Equ tmp;
	sf("%d", &T);
	REP(t,1,T)
	{
		sf("%d%d", &n, &m);
		REP(i,1,n) REP(k,1,m)
			sf("%lld", &pre[i][CalcPoi(k,k)].a);
		REP(i,1,n) REP(k,1,m)
			sf("%lld", &pre[i][CalcPoi(k,k)].b);
		for(int i=1; i<=n; ++i)
			for(int k=1; k<=m; ++k)
			{
				for(int j=k+1; j<=m; ++j)
				{
					pre[i][CalcPoi(k,j)] = Calc(pre[i][CalcPoi(k,j-1)], pre[i][CalcPoi(j,j)]);
					if(pre[i][CalcPoi(k,j)].a == -1)
					{
						for(int q=j+1; q<=m; ++q)
							pre[i][CalcPoi(k,q)].a = pre[i][CalcPoi(k,q)].b = -1;
						break;
					}
				}
			}
		sf("%d", &que);
		printf("Case #%d:\n", t);
		for(int i=1; i<=que; ++i)
		{
			sf("%d%d%d%d", &x1, &y1, &x2, &y2);
			tmp = pre[x1][CalcPoi(y1,y2)];
			for(int k=x1+1; k<=x2; ++k)
			{
				tmp = Calc(tmp, pre[k][CalcPoi(y1,y2)]);
				if(tmp.a == -1) break;
			}
			printf("%lld\n", tmp.a);
		}
	}
	return 0;
}
