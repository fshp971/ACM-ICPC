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
typedef pair<int,int> pii;

const int md = 9973, maxm = 10;

int m;
char mmp[maxm+5][maxm+5];

inline void update(LL &x) {
	if(x >= md) x %= md;
}

struct Matrix {
	int row, col;
	LL mat[maxm+5][maxm+5];
	Matrix(): row(0), col(0) { mem(mat, 0); }
	void clear(int _row = 0, int _col = 0 ) {
		row = _row, col = _col, mem(mat, 0);
	}
	Matrix operator*(const Matrix &a) {
		Matrix res;
		res.row = row, res.col = a.col;
		for(int i=0; i<row; ++i) {
			for(int k=0; k<col; ++k) {
				if(mat[i][k] == 0) continue;
				for(int j=0; j<a.col; ++j)
				{
					res.mat[i][j] += mat[i][k]*a.mat[k][j];
					update(res.mat[i][j]);
				}
			}
		}
		return res;
	}
}B, base[40];

void mat_pow_mod(int b, Matrix &res) {
	res = base[0];
	int cont = 1;
	while(b) {
		if(b&1) res = res*base[cont];
		++cont, b >>= 1;
	}
}

void init_base() {
	base[0].clear(m, m);
	for(int i=0; i<base[0].row; ++i) base[0].mat[i][i] = 1;

	base[1].clear(m, m);
	for(int i=0; i<m; ++i)
		for(int k=i; k<m; ++k)
		{
			if(!mmp[i][k])
				base[1].mat[i][k] = base[1].mat[k][i] = 1;
		}

	for(int i=2; i<=32; ++i)
		base[i] = base[i-1] * base[i-1];
}

LL F(int n)
{
	mat_pow_mod(n-1, B);
	LL res = 0;
	for(int i=0; i<m; ++i)
		for(int k=0; k<m; ++k)
		{
			if(mmp[i][k]) continue;
			res = res+B.mat[i][k], update(res);
		}
	return res;
}

LL Euler(LL n) {
	LL res = n, a = n;
	for(int i=2; i*i<=a; ++i) {
		if(a%i == 0) {
			res = res/i*(i-1);
			while(a%i == 0) a /= i;
		}
	}
	if(a>1) res = res/a*(a-1);
	return res;
}

LL pow_mod(LL a, LL b) {
	LL res = 1;
	while(b) {
		if(b&1)
			res = res*a, update(res);
		a = a*a, update(a);
		b >>= 1;
	}
	return res;
}

int main()
{
	int T, n, kk, a, b;
	sf("%d", &T);
	while(T--)
	{
		sf("%d%d%d", &n, &m, &kk);
		mem(mmp, 0);
		REP(i,1,kk)
		{
			sf("%d%d", &a, &b);
			mmp[a-1][b-1] = mmp[b-1][a-1] = 1;
		}
		init_base();
		if(n == 1)
		{
			printf("%d\n", m);
			continue;
		}
		LL ans = 0;
		for(int i=1; i*i<=n; ++i)
		{
			if(n%i) continue;
			ans = ans + F(i)*Euler(n/i), update(ans);
			if(i*i != n)
				ans = ans + F(n/i)*Euler(i), update(ans);
		}
		ans = ans*pow_mod(n, md-2), update(ans);
		pf("%lld\n", ans);
	}
	return 0;
}
