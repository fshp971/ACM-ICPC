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

const int maxn = 1000;

int ans[maxn+5];

void init()
{
	mem(ans, -1);
	int sum;
	for(int i=1; i<=maxn; ++i)
	{
		sum = 0;
		for(int k=1; k<=i; ++k)
			if(i%k == 0) sum += k;
		if(sum <= maxn) ans[sum] = i;
	}
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	init();
	int n, T = 0;
	while(scanf("%d", &n), n)
		pf("Case %d: %d\n", ++T, ans[n]);
	return 0;
}
