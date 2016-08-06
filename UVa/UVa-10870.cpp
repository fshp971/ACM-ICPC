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

const int maxd = 15;

int dd, n, md;
int arr[maxd+5];

struct Matrix
{
	int n, m;
	LL mat[50][50];
	
	void clear()
	{
		n = m = 0;
		mem(mat, 0);
	}

	Matrix operator*(const Matrix &a)
	{
		Matrix res;
		res.n = n, res.m = a.m;
		for(int i=0; i<res.n; ++i)
			for(int j=0; j<res.m; ++j)
			{
				res.mat[i][j] = 0;
				for(int k=0; k<m; ++k)
					res.mat[i][j] = (res.mat[i][j] + mat[i][k]*a.mat[k][j]) % md;
			}
		return res;
	}
};

Matrix power_mod(Matrix &tmp, int n)
{
	Matrix res;
	res.clear();
	res.n = res.m = tmp.n;
	for(int i=0; i<res.n; ++i) res.mat[i][i] = 1;
	while(n)
	{
		if(n&1) res = res*tmp;
		tmp = tmp*tmp;
		n >>= 1;
	}
	return res;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	Matrix tmp, ff;
	while(sf("%d%d%d", &dd, &n, &md), n)
	{
		tmp.clear(); ff.clear();
		ff.n = 2*dd, ff.m = 1;
		REP(i,1,dd) sf("%d", arr+dd-i+1), arr[dd-i+1] %= md;
		REP(i,1,dd) sf("%lld", &ff.mat[i-1][0]), ff.mat[i-1][0] %= md;
		for(int i=dd+1; i<=2*dd; ++i)
		{
			ff.mat[i-1][0] = 0;
			for(int k=1; k<=dd; ++k)
				ff.mat[i-1][0] = (ff.mat[i-1][0] + ff.mat[i-dd+k-2][0] * arr[k]) % md;
		}
		tmp.n = tmp.m = 2*dd;
		for(int i=dd-1; i<=dd*2-1; ++i)
			for(int k=1; k<=dd; ++k)
				tmp.mat[i][i+k-dd] = arr[k];
		for(int i=0; i<=dd-2; ++i)
			tmp.mat[i][i+1] = 1;
		if(n <= 2*dd)
		{
			pf("%lld\n", ff.mat[n-1][0]);
			continue;
		}
		tmp = power_mod(tmp, n-2*dd);
		ff = tmp*ff;
		pf("%lld\n", ff.mat[2*dd-1][0]);
	}
	return 0;
}
