#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<cctype>
#include<iostream>
#include<algorithm>
#include<queue>
#include<string>
#include<utility>
#include<map>
#include<set>
#include<vector>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define MP(a,b) make_pair(a,b)
#define LL long long
#define pii pair<int,int>
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define sf scanf
#define pf printf

const int maxn = 50000;

int n;

double f[maxn+10], arr[maxn+10];

void run()
{
	f[0] = 0;
	REP(i,1,maxn)
		f[i] = f[i-1] + log10(i);
}

double init()
{
	cin>>n;
	FOR(i,0,n) cin>>arr[i];
	double res = 0;
	REP(i,0,n-1)
	{
		if(arr[i] == 0) continue;
		double tmp = f[n-1] + log10(fabs(arr[i])) - f[n-1-i] - f[i] - log10(2) * (n-1);
		//printf("tmp = %f\n", tmp);
		if(arr[i] > 0) res += pow(10, tmp);
		else res -= pow(10, tmp);
	}
	return res;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	run();
	int t;
	cin>>t;
	REP(i,1,t)
		pf("Case #%d: %.3f\n",i,init());
	return 0;
}
