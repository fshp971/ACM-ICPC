//#include<cstdio>
#include<stdio.h>
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

struct Matrix
{
	int row, col;
	LL mat[5][5];
	Matrix(): row(0), col(0) { mem(mat,0); }
	Matrix operator*(const Matrix &a)
	{
		Matrix res;
		res.row = row, res.col = a.col;
		FOR(i,0,res.row) FOR(j,0,res.col)
		{
			FOR(k,0,col)
				res.mat[i][j] = (res.mat[i][j] + mat[i][k]*a.mat[k][j]%md) % md;
		}
		return res;
	}
};

Matrix pow_mod(Matrix a, LL b)
{
	Matrix res;
	res.row = res.col = a.row;
	FOR(i,0,res.row) res.mat[i][i] = 1;
	while(b)
	{
		if(b&1) res = res*a;
		a = a*a, b >>= 1;
	}
	return res;
}

int main()
{
	LL n;
	sf("%lld", &n);

	Matrix ini;
	ini.row = ini.col = 4;
	ini.mat[0][0] = ini.mat[1][0] = ini.mat[1][1] = 1;
	ini.mat[0][1] = 2;

	ini = pow_mod(ini, n);
	LL ans = ini.mat[0][0]*ini.mat[0][0] % md;
	if(n&1) ans = (ans+1) % md;
	pf("%lld\n", ans);
	return 0;
}
