#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<queue>
#include<string>
#include<utility>
#include<map>
#include<set>
#include<vector>

using namespace std;

#define LL long long
#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define pii pair<int,int>
#define MP(a,b) make_pair(a,b)
#define sf scanf
#define pf printf

const int maxn = 1000;

int n;
int sum[maxn+5][2];

void init()
{
	mem(sum, 0);
	sf("%d",&n);
	FOR(i,1,n)
	{
		REP(k,i+1,n)
		{
			int a;
			sf("%d",&a);
			++sum[i][a]; ++sum[k][a];
		}
	}
	LL all = (LL)n * (n-1) / 2;
	LL ans = (LL)n * (n-1) * (n-2) / 6;
	//pf("ans = %lld\n", ans);
	LL tmp = 0;
	REP(i,1,n)
		tmp += (LL)sum[i][0] * sum[i][1];
	tmp /= 2; ans -= tmp;
	cout << ans << "\n";
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int t;
	cin >> t;
	REP(i,1,t)
		init();
	return 0;
}
