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

const int maxn = 500;

int vis[maxn+2], prime[maxn+2], tot;

void init()
{
	mem(vis, 0);
	prime[0] = 2, tot = 1;
	for(int i=3; i<=maxn; i+=2)
	{
		if(!vis[i])
		{
			prime[tot++] = i;
			for(int k=i+i; k<=maxn; k+=i)
				vis[k] = 1;
		}
	}
}

int n;
int mat[102][102];

int guass()
{
	int t, res = 0, row = 0;
	for(int i=0; i<n; ++i)
	{
		t = -1;
		for(int k=row; k<tot; ++k)
			if(mat[k][i])
			{
				t = k;
				break;
			}
		if(t == -1) continue;
		++res;
		if(t != row)
			for(int j=i; j<n; ++j) swap(mat[row][j], mat[t][j]);
		for(int k=row+1; k<tot; ++k)
			if(mat[k][i])
			{
				for(int j=row; j<n; ++j)
					mat[k][j] ^= mat[row][j];
			}
		++row;
	}
	return res;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	init();
	int T, rank;
	LL ans, x;
	sf("%d", &T);
	while(T--)
	{
		sf("%d", &n);
		mem(mat, 0);
		for(int i=0; i<n; ++i)
		{
			sf("%lld", &x);
			for(int k=0; k<tot && x>=prime[k]; ++k)
			{
				while(x%prime[k] == 0)
				{
					x /= prime[k];
					mat[k][i] ^= 1;
				}
			}
		}
		n -= guass();
		ans = 1;
		for(int i=0; i<n; ++i) ans *= 2;
		--ans;
		pf("%lld\n", ans);
	}
	return 0;
}
