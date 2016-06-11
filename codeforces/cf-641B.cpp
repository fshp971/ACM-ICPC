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
#define MP(a,b) make_pair(a,b)
#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define pii pair<int,int>
#define sf scanf
#define pf printf

const int maxn = 100;

int n,m,que;
int ans[maxn+10][maxn+10];

pii mmp[maxn+10][maxn+10];

void init()
{
	cin >> n >> m >> que;
	mem(ans, 0);
	FOR(i,0,n) FOR(k,0,m) mmp[i][k] = MP(i,k);
	REP(t,1,que)
	{
		int ord, num, nx, ny, xx;
		sf("%d", &ord);
		if(ord == 1)
		{
			sf("%d", &num);
			pii tmp = mmp[num-1][0];
			FOR(i,0,m-1) mmp[num-1][i] = mmp[num-1][i+1];
			mmp[num-1][m-1] = tmp;
		}
		else if(ord == 2)
		{
			sf("%d", &num);
			pii tmp = mmp[0][num-1];
			FOR(i,0,n-1) mmp[i][num-1] = mmp[i+1][num-1];
			mmp[n-1][num-1] = tmp;
		}
		else
		{
			sf("%d%d%d", &nx, &ny, &xx);
			pii &tmp = mmp[nx-1][ny-1];
			ans[tmp.first][tmp.second] = xx;
		}
	}
	FOR(i,0,n)
	{
		FOR(k,0,m)
		{
			if(k) pf(" ");
			pf("%d", ans[i][k]);
		}
		pf("\n");
	}
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	init();
	return 0;
}
