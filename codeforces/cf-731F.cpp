#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<string>
#include<queue>
#include<vector>
#include<utility>
#include<map>
#include<set>
#include<bitset>

using namespace std;

#define LL long long
#define mem(a,b) memset(a,b,sizeof(a))
#define MP(a,b) make_pair(a,b)
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define sf scanf
#define pf printf

const int maxn = 200000;

int n, cnt[maxn+5];
int sum[maxn+5];

int main()
{
	sf("%d", &n);
	int a;
	REP(i,1,n) sf("%d", &a), ++cnt[a];
	REP(i,1,maxn) sum[i] = sum[i-1]+cnt[i];
	LL ans = 0, tmp = 0;
	for(int i=1; i<=maxn; ++i)
	{
		if(cnt[i])
		{
			tmp = 0;
			for(int k=i; k<=maxn; k+=i)
			{
				tmp += (LL)k * (sum[min(maxn, k+i-1)] - sum[k-1]);
			}
			ans = max(ans, tmp);
		}
	}
	cout << ans << "\n";
	return 0;
}
