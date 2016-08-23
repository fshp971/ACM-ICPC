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

const int maxn = 100000;

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int T, n, que, bb, kk;
	int arr[maxn+2];
	map< pii, LL > ans;
	pii tmp;
	LL sum;
	sf("%d", &T);
	for(int t=1; t<=T; ++t)
	{
		sf("%d", &n);
		FOR(i,0,n) sf("%d", arr+i);
		sf("%d", &que);
		ans.clear();
		printf("Case #%d:\n", t);
		REP(i,1,que)
		{
			sf("%d%d", &kk, &bb);
			tmp.first = kk, tmp.second = bb;
			if(!ans.count( tmp ))
			{
				sum = 0;
				for(int k=bb; k<n; k+=kk)
					sum += arr[k];
				ans[tmp] = sum;
			}
			printf("%lld\n", ans[tmp]);

		}
	}
	return 0;
}
