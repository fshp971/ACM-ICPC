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

int n, kk;
double l, v1, v2;

void init()
{
	sf("%d%lf%lf%lf%d", &n, &l, &v1, &v2, &kk);
	int tk = n/kk;
	if(tk*kk < n) ++tk;
	double ans = l / (v1*(2.0*tk-1) + v2) * (2.0*tk + v1/v2 - 1.0);
	pf("%.10f\n", ans);
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	init();
	return 0;
}
