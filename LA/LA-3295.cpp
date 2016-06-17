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

int n,m;

int gcd[maxn+10][maxn+10];
LL res[maxn+10][maxn+10], f[maxn+10][maxn+10];

int cal_gcd(int a,int b){ return b ? cal_gcd(b,a%b) : a; }

LL cal_cube(LL x){ return x * (x-1) * (x-2) / 6; }

void run()
{
	mem(f,0); mem(res,0);
	REP(i,1,maxn) REP(k,1,maxn) gcd[i][k] = cal_gcd(i,k);
	REP(i,1,maxn) REP(k,1,maxn)
	{
		f[i][k] = f[i-1][k] + f[i][k-1] - f[i-1][k-1] + gcd[i][k] - 1;
	}
	REP(i,1,maxn) REP(k,1,maxn)
		res[i][k] = res[i][k-1] + res[i-1][k] - res[i-1][k-1] + f[i][k];
	/*
	REP(i,1,10) REP(k,1,10)
	{
		//printf("f[%d][%d] = %lld\n",i,k,f[i][k]);
		//printf("gcd[%d][%d] = %d\n", i, k, gcd[i][k]);
		printf("res[%d][%d] = %lld\n",i,k,res[i][k]);
	}
	*/
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	run();
	int NT = 0;
	while(~sf("%d%d",&n,&m), n && m)
	{
		LL ans = cal_cube((n+1)*(m+1)) - cal_cube(n+1) * (m+1) - cal_cube(m+1) * (n+1) - res[n][m] * 2;
		cout << "Case " << (++NT) << ": " << ans << "\n";
	}
	return 0;
}
