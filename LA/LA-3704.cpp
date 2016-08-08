#include<bits/stdc++.h>

using namespace std;

#define LL long long
#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define MP(a,b) make_pair(a,b)
#define pii pair<int,int>
#define sf scanf
#define pf printf

const int maxn = 500;

int n, md;

struct Matrix
{
	int mat[maxn+5][maxn+5], row, col;
	
	void clear(){ row = col = 0; mem(mat, 0); }

	Matrix operator*(const Matrix &a)
	{
		Matrix res;
		res.row = row, res.col = a.col;
		for(int i=0; i<row; ++i)
			for(int j=0; j<a.col; ++j)
			{
				res.mat[i][j] = 0;
				for(int k=0; k<col; ++k)
					res.mat[i][j] += (LL)mat[i][k] * a.mat[k][j] % md;
				res.mat[i][j] %= md;
			}
		return res;
	}
};

void pow_log(Matrix &res, Matrix &tmp, Matrix &rub, int p)
{
	res.row = 1, res.col = n;
	mem(res.mat[0], 0); res.mat[0][0] = 1;
	while(p)
	{
		rub.row = rub.col = n;
		for(int i=0; i<n; ++i)
			for(int k=0; k<n; ++k)
				rub.mat[i][(k+i)%n] = tmp.mat[0][k];
		if(p&1)
			res = res*rub;
		tmp = tmp*rub;
		p >>= 1;
	}
	res.row = n;
	for(int i=1; i<n; ++i)
		for(int k=0; k<n; ++k)
			res.mat[i][(k+i)%n] = res.mat[0][k];
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	Matrix now, ans, res, rub;
	int dd, kk;
	while(~sf("%d%d%d%d", &n, &md, &dd, &kk))
	{
		ans.row = n, ans.col = 1;
		for(int i=0; i<n; ++i) sf("%d", &ans.mat[i][0]);
		now.row = 1, now.col = n;
		for(int k=0; k<n; ++k)
			now.mat[0][k] = min(abs(0-k), n-abs(0-k)) <= dd ? 1 : 0;
		pow_log(res, now, rub, kk);
		ans = res * ans;
		FOR(i,0,n)
		{
			if(i) pf(" ");
			pf("%d", ans.mat[i][0]);
		}
		pf("\n");
	}
	return 0;
}
