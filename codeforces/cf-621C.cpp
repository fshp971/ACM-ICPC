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

const int maxn = 100000;

int n, pp;
double pos[maxn+5];

void init()
{
	cin >> n >> pp;
	REP(i,1,n)
	{
		int ll, rr;
		sf("%d%d", &ll, &rr);
		int num = (rr/pp) - ((ll-1)/pp);
		pos[i] = (double)num / (rr-ll+1);
	}
	pos[0] = pos[n]; pos[n+1] = pos[1];
	double ans = 0;
	REP(i,1,n) ans += 2.0*pos[i] + (1-pos[i]) * (pos[i-1]+pos[i+1]);
	ans *= 1000;
	//REP(i,1,n) printf("pos[%d] = %f\n", i, pos[i]);
	printf("%.8f\n",ans);
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	init();
	return 0;
}
