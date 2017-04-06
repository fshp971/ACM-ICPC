#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<string>
#include<queue>
#include<utility>
#include<map>
#include<set>

using namespace std;

#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define mem(a,b) memset(a,b,sizeof(a))
#define MP make_pair
#define sf scanf
#define pf printf
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 1000;

int arr[maxn+5];

bool check_M(int n, int m)
{
	if(m <= 1) return false;
	if(m == 2) return n%2 == 0;
	int len;
	if(m%2)
	{
		len = m * (m-1) / 2;
		if(len == n) return true;
		return len+2 <= n;
	}
	len = (m-1)*(m-2)/2 + ((m-1)/2)*3 + 2;
	return len <= n;
}

char mmp[maxn+2][maxn+2];

int dfs(int m)
{
	mem(arr, 0);
	int len = m*(m-1)/2;
	arr[1] = 1;
	for(int i=2; i<=len; ++i)
	{
		for(int k=arr[i-1]+1; k<=m; ++k)
		{
			if(!mmp[arr[i-1]][k])
			{
				arr[i] = k;
				mmp[arr[i-1]][k] = mmp[k][arr[i-1]] = 1;
				break;
			}
		}
		if(arr[i] == 0)
		{
			for(int k=1; k<arr[i-1] && !arr[i]; ++k)
				if(!mmp[arr[i-1]][k])
				{
					arr[i] = k;
					mmp[arr[i-1]][k] = mmp[k][arr[i-1]] = 1;
				}
		}
	}
	return len;
}

void solve(int n, int m)
{
	if(m == 2)
	{
		for(int i=1; i<=n; ++i) arr[i] = i%2 + 1;
		return;
	}
	int last = (m%2 == 0) ? dfs(m-1) : dfs(m);
	if(m%2)
	{
		if(last == n) return;
		arr[++last] = 1, arr[++last] = m;
		int tmp;
		while(last < n)
		{
			for(tmp = 2; tmp == arr[last]; ++tmp);
			arr[++last] = tmp;
		}
	}
	else
	{
		int err = arr[last], tmp;
		arr[++last] = m;
		for(int i=m-1; i>=1; --i)
		{
			if(i == err) continue;
			if(arr[last] == m)
				arr[++last] = i;
			else
			{
				arr[++last] = i;
				arr[++last] = m;
			}
		}
		while(last+1 < n)
		{
			for(tmp = 1; tmp == arr[last] || tmp == err; ++tmp);
			arr[++last] = tmp;
		}
		arr[++last] = err;
	}
}

int main()
{
	freopen("achromatic.in", "r", stdin);
	freopen("achromatic.out", "w", stdout);
	int n, m = 0;
	sf("%d", &n);
	for(int i=2; i<=n; ++i)
		if(check_M(n,i))
			m = i;
	printf("%d\n", m);
	solve(n, m);
	for(int i=1; i<=n; ++i)
	{
		if(i>1) printf(" ");
		printf("%d", arr[i]);
	}
	printf("\n");
	return 0;
}
