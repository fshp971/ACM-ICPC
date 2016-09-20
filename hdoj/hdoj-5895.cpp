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

#define LL long long
#define pii pair<int,int>
#define MP make_pair
#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define sf scanf
#define pf printf

const int maxs = 1e8 + 1;

struct Matrix
{
	int row, col;
	LL mat[6][6], md;
	void clear()
	{
		row = col = 0;
		md = 1;
		mem(mat, 0);
	}
	Matrix operator*(const Matrix &a)
	{
		Matrix res;
		res.row = row, res.col = a.col, res.md = md;
		mem(res.mat, 0);
		FOR(i,0,res.row)
		{
			FOR(k,0,col)
			{
				if(!mat[i][k]) continue;
				FOR(j,0,res.col)
				{
					res.mat[i][j] = (res.mat[i][j] + mat[i][k]*a.mat[k][j]);
					if(res.mat[i][j] >= md) res.mat[i][j] %= md;
				}
			}
		}
		return res;
	}
};

LL phi(LL x)
{
	LL ans = x;
	for(LL i=2; i*i<=x; ++i)
		if(x%i == 0)
		{
			ans -= ans/i;
			while(x%i == 0) x /= i;
		}
	if(x>1) ans -= ans/x;
	return ans;
}

LL cal_G(LL p, LL s)
{
	if(!p) return 0;
	Matrix res, tmp;
	res.clear(); tmp.clear();

	if(p<=10)
		res.md = tmp.md = (LL)1 << 60;
	else
		res.md = tmp.md = phi(s);
	res.row = res.col = tmp.row = tmp.col = 4;
	FOR(i,0,4) res.mat[i][i] = 1;
	tmp.mat[0][0] = tmp.mat[0][3] = tmp.mat[1][3] = tmp.mat[2][2] = tmp.mat[3][1] = 1;
	tmp.mat[0][1] = tmp.mat[0][2] = tmp.mat[1][1] = tmp.mat[1][2] = 4;
	tmp.mat[2][1] = 2;

	--p;
	while(p)
	{
		if(p&1) res = res*tmp;
		p >>= 1, tmp = tmp*tmp;
	}
	if(p+1 <= 10)
		return res.mat[0][0] + res.mat[0][1];
	return (res.mat[0][0]+res.mat[0][1])%phi(s) + phi(s);
}

LL read_int()
{
	char a[15];
	LL res = 0;
	sf("%s", a);
	for(int i=0; i<strlen(a); ++i)
		res = res*10 + a[i]-48;
	return res;
}

LL pow_mod(LL x, LL p, LL md)
{
	LL res = 1, tmp = x;
	while(p)
	{
		if(p&1) res = res*tmp % md;
		p >>= 1, tmp = tmp*tmp % md;
	}
	return res;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int T;
	LL n, y, x, s, gg;
	sf("%d", &T);
	while(T--)
	{
		n = read_int();
		y = read_int();
		x = read_int();
		s = read_int();
		gg = cal_G(n*y, s+1);
		pf("%lld\n", pow_mod(x, gg, s+1));
	}
	return 0;
}
