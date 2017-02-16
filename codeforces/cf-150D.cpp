#include<bits/stdc++.h>

using namespace std;

#define LL long long
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define mem(a,b) memset(a,b,sizeof(a))
#define MP make_pair
#define pii pair<int,int>
#define sf scanf
#define pf printf

const int maxn = 150;

int n;
int arr[maxn+5], dp[maxn+5];
int f[maxn+5][maxn+5][maxn+5];
int ans[maxn+5];
char aa[maxn+5];

void CalDP()
{
	dp[0] = -1, dp[1] = arr[1];
	for(int i=2; i<=n; ++i)
	{
		dp[i] = arr[i];
		for(int k=1; (k<<1) < i; ++k)
		{
			if(arr[k*2]!=-1 && dp[i-k*2]!=-1)
				dp[i] = max(dp[i], arr[k*2]+dp[i-k*2]);
		}
	}
}

int main()
{
	sf("%d", &n);
	REP(i,1,n) sf("%d", arr+i);
	sf("%s", aa);
	CalDP();
	mem(f, -1);
	for(int l=1; l<=n; ++l)
	{
		f[l][l][1] = 0;
		if(dp[1] != -1)
			f[l][l][0] = dp[1];
		if(l<n)
		{
			if(aa[l-1] == aa[l])
			{
				f[l][l+1][2] = 0;
				if(dp[2] != -1)
					f[l][l+1][0] = dp[2];
			}
			if(dp[1] != -1)
			{
				f[l][l+1][1] = dp[1];
				f[l][l+1][0] = max(f[l][l+1][0], dp[1]*2);
			}
		}
	}
	for(int ll=3; ll<=n; ++ll)
	{
		for(int l=1, r=ll; r<=n; ++l, ++r)
		{
			for(int len=0; len<=ll; ++len)
			{
				if(len>=2 && aa[l-1]==aa[r-1])
					f[l][r][len] = f[l+1][r-1][len-2];
				for(int k=l; k<r; ++k)
				{
					if(f[l][k][len]!=-1 && f[k+1][r][0]!=-1)
						f[l][r][len] = max(f[l][r][len], f[l][k][len]+f[k+1][r][0]);
					if(f[l][k][0]!=-1 && f[k+1][r][len]!=-1)
						f[l][r][len] = max(f[l][r][len], f[l][k][0]+f[k+1][r][len]);
				}
				if(dp[len] != -1 && f[l][r][len] != -1)
					f[l][r][0] = max(f[l][r][0], f[l][r][len]+dp[len]);
			}
		}
	}
	ans[0] = 0;
	for(int i=1; i<=n; ++i)
	{
		ans[i] = ans[i-1];
		for(int k=1; k<=i; ++k)
			if(f[k][i][0] != -1)
				ans[i] = max(ans[i], ans[k-1]+f[k][i][0]);
	}
	pf("%d\n", ans[n]);
	return 0;
}
