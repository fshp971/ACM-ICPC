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

const int maxn = 3000;

int n;
int aa[maxn+5], bb[maxn+5];
LL f[maxn+5];

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	sf("%d", &n);
	REP(i,1,n)
		sf("%d", aa+i), aa[i] -= i, bb[i] = aa[i];
	sort(bb+1, bb+1+n);
	for(int i=1; i<=n; ++i)
	{
		LL mini = (LL)1 << 60;
		for(int k=1; k<=n; ++k)
		{
			mini = min(mini, f[k]);
			f[k] = abs(aa[i] - bb[k]) + mini;
		}
	}
	LL ans = (LL)1 << 60;
	for(int i=1; i<=n; ++i) ans = min(ans, f[i]);
	pf("%lld\n", ans);
	return 0;
}
