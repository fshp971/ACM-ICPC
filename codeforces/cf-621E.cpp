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

const int md = 1e9 + 7;

struct Matrix
{
	int n_len, m_len;
	LL mat[110][110];

	void initial(int nn, int mm)
	{
		n_len = nn; m_len = mm;
		mem(mat, 0);
	}

	Matrix operator*(const Matrix &a)
	{
		Matrix tmp;
		tmp.initial(n_len, a.m_len);
		FOR(i,0,n_len) FOR(j,0,a.m_len)
		{
			LL sum = 0;
			FOR(k,0,m_len)
				sum = (sum + mat[i][k] * a.mat[k][j]) % md;
			tmp.mat[i][j] = sum;
		}
		return tmp;
	}
};

int n, blo, kk, xx;
int num_c[15];

void init()
{
	int a;
	cin >> n >> blo >> kk >> xx;
	mem(num_c, 0);
	REP(i,1,n)
	{
		sf("%d", &a);
		++num_c[a];
	}
	Matrix beg, ans, now;
	beg.initial(xx, xx);
	ans.initial(xx, 1);
	now.initial(xx, xx);
	ans.mat[0][0] = 1;
	FOR(i,0,xx) REP(t,1,9)
	{
		beg.mat[(i*10+t)%xx][i] += num_c[t];
		beg.mat[(i*10+t)%xx][i] %= md;
		now.mat[i][i] = 1;
	}
	while(blo > 0)
	{
		if(blo&1) now = now * beg;
		beg = beg * beg;
		blo >>= 1;
	}
	ans = now * ans;
	cout << ans.mat[kk][0] << "\n";
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	init();
	return 0;
}
