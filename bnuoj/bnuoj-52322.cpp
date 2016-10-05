#include<bits/stdc++.h>

using namespace std;

#define LL long long
#define MP(a,b) make_pair(a,b)
#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define pii pair<int,int>
#define sf scanf
#define pf printf

const int md = 20160519;

struct Matrix
{
	int row, col;
	LL mat[5][5];
	void clear(int _row = 0, int _col = 0)
	{
		row = _row, col = _col;
		mem(mat, 0);
	}
	Matrix operator*(const Matrix &a)
	{
		Matrix res;
		res.clear(row, a.col);
		for(int i=0; i<res.row; ++i)
			for(int j=0; j<res.col; ++j)
				for(int k=0; k<col; ++k)
				{
					res.mat[i][j] += mat[i][k] * a.mat[k][j];
					res.mat[i][j] %= md;
				}
		return res;
	}
};

const int maxn = 746687;

LL ans[maxn+5];

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	Matrix tmp1, tmp2, tmp3;
	tmp1.clear(2,2);
	tmp1.mat[0][0] = tmp1.mat[1][0] = tmp1.mat[0][1] = 1;
	tmp2.clear(2,2);
	tmp2.mat[0][0] = tmp2.mat[1][1] = 1;

	for(int i=0; i<=maxn; ++i)
	{
		ans[i] = tmp2.mat[1][0];
		tmp3 = tmp1;
		tmp1 = tmp1 * tmp2;
		tmp2 = tmp3;
		//pf("ans[%d] = %lld\n", i, ans[i]);
	}
	int T, n;
	sf("%d", &T);
	while(T--)
	{
		sf("%d", &n);
		pf("%lld\n", ans[n%(maxn+1)]);
	}
	return 0;
}
