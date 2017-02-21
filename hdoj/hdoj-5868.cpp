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

const int md = 1e9+7;

struct Matrix
{
	int row, col;
	LL mat[2][2];
	Matrix(): row(0), col(0) { mem(mat,0); }
	Matrix operator*(const Matrix &a)
	{
		Matrix res;
		res.row = row, res.col = a.col;
		for(int i=0; i<row; ++i)
		{
			for(int k=0; k<col; ++k)
			{
				if(mat[i][k] == 0) continue;
				for(int j=0; j<a.col; ++j)
				{
					res.mat[i][j] += mat[i][k]*a.mat[k][j];
					res.mat[i][j] %= md;
				}
			}
		}
		return res;
	}
} M_res, M_tmp;

LL f(int n)
{
	if(n == 1) return 1;
	n -= 2;

	M_res.row = M_res.col = 2;
	M_res.mat[0][0] = M_res.mat[1][1] = 1;
	M_res.mat[1][0] = M_res.mat[0][1] = 0;

	M_tmp.row = M_tmp.col = 2;
	M_tmp.mat[0][0] = M_tmp.mat[0][1] = M_tmp.mat[1][0] = 1;
	M_tmp.mat[1][1] = 0;

	while(n)
	{
		if(n&1) M_res = M_res*M_tmp;
		M_tmp = M_tmp*M_tmp, n >>= 1;
	}
	return (M_res.mat[0][0]*3 + M_res.mat[0][1]) % md;
}

LL Euler(int n)
{
	LL res = n, a = n;
	for(int i=2; i*i<=a; ++i)
	{
		if(a%i == 0)
		{
			res = res/i*(i-1);
			while(a%i == 0) a /= i;
		}
	}
	if(a>1) res = res/a*(a-1);
	return res;
}

LL pow_mod(LL a, LL b)
{
	LL res = 1;
	while(b)
	{
		if(b&1) res = res*a % md;
		a = a*a % md;
		b >>= 1;
	}
	return res;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int n;
	LL ans;
	while(~sf("%d", &n))
	{
		if(n == 1)
		{
			pf("2\n");
			continue;
		}
		ans = 0;
		for(int i=1; i*i<=n; ++i)
		{
			if(n%i) continue;
			ans += f(i) * Euler(n/i) % md;
			if(i*i != n) ans += f(n/i) * Euler(i) % md;
			ans %= md;
		}
		ans = ans*pow_mod(n,md-2) % md;
		pf("%lld\n", ans);
	}
	return 0;
}
