#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<iostream>
#include<algorithm>
#include<string>
#include<queue>
#include<vector>
#include<utility>
#include<map>
#include<set>

using namespace std;

#define LL long long
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define pii pair<int,int>
#define mem(a,b) memset(a,b,sizeof(a))
#define MP(a,b) make_pair(a,b)
#define sf scanf
#define pf printf

const int maxn = 14;

int n, m;
int val[maxn+2];
int f[1<<maxn][maxn+2][maxn+2];
LL cont[1<<maxn][maxn+2][maxn+2];
char mmp[maxn+2][maxn+2];

inline int cal(int x, int y, int z)
{
	LL res = val[x], tmp = val[x]*val[y];
	res += tmp;
	if(mmp[x][z]) res += tmp*val[z];
	return res;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int T, a, b, ans1;
	LL ans2;
	sf("%d", &T);
	while(T--)
	{
		sf("%d%d", &n, &m);
		val[0] = 0;
		REP(i,1,n) sf("%d", val+i);
		mem(mmp, 0);
		REP(i,1,m)
		{
			sf("%d%d", &a, &b);
			mmp[a][b] = mmp[b][a] = 1;
		}
		if(n == 1)
		{
			pf("%d %d\n", val[1], 1);
			continue;
		}
		mem(f, 0); mem(cont, 0);

		for(int i=1; i<=n; ++i)
			for(int k=1; k<=n; ++k)
			{
				if(i == k || !mmp[k][i]) continue;
				int t1 = 1<<(i-1), t2 = 1<<(k-1);
				f[t1+t2][i][k] = cal(i, k, 0) + val[k];
				cont[t1+t2][i][k] = 1;
			}

		for(int msk=1; msk <= (1<<n)-1; ++msk)
		{
			for(int i=1; i<=n; ++i)
			{
				if(!((1<<(i-1)) & msk)) continue;
				int p_msk = msk - (1<<(i-1));
				for(int k=1; k<=n; ++k)
				{
					if(!((1<<(k-1)) & p_msk) || !mmp[k][i]) continue;
					for(int j=1; j<=n; ++j)
					{
						if(k == j || !((1<<(j-1)) & p_msk) || !f[p_msk][k][j]) continue;
						int res = f[p_msk][k][j] + cal(i, k, j);
						if(f[msk][i][k] < res)
						{
							f[msk][i][k] = res;
							cont[msk][i][k] = cont[p_msk][k][j];
						}
						else if(f[msk][i][k] == res)
							cont[msk][i][k] += cont[p_msk][k][j];
					}
				}
			}
		}

		ans1 = 0, ans2 = 0;
		for(int i=0; i<=n; ++i)
			for(int k=0; k<=n; ++k)
			{
				if(i == k || !f[(1<<n)-1][i][k]) continue;
				if(f[(1<<n)-1][i][k] > ans1)
				{
					ans1 = f[(1<<n)-1][i][k];
					ans2 = cont[(1<<n)-1][i][k];
				}
				else if(f[(1<<n)-1][i][k] == ans1)
					ans2 += cont[(1<<n)-1][i][k];
			}
		ans2 /= 2;
		cout << ans1 << " " << ans2 << "\n";
	}
	return 0;
}
