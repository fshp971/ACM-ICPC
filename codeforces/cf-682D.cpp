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

const int maxn = 1000;

char ss[maxn+5], tt[maxn+5];
int len[maxn+5][maxn+5];
int f[maxn+5][maxn+5][15];
int n,m,kk;

void init()
{
	cin >> n >> m >> kk;
	sf("%s",ss); sf("%s",tt);
	mem(len,0); mem(f,0);
	for(int i=1; i<=n; ++i)
	{
		for(int k=1; k<=m; ++k)
		{
			if(ss[i-1] == tt[k-1])
				len[i][k] = len[i-1][k-1] + 1;
		}
	}
	int ans = 0;
	REP(i,1,n) REP(k,1,m) REP(t,1,kk)
	{
		int &le = len[i][k];
		f[i][k][t] = max(f[i-1][k][t], f[i][k-1][t]);
		if(le)
			f[i][k][t] = max(f[i][k][t], f[i-le][k-le][t-1] + le);
		ans = max(ans, f[i][k][t]);
	}
	/*REP(i,1,n) REP(k,1,m)
		pf("len[%d][%d] = %d\n", i, k, len[i][k]);
	REP(i,1,n) REP(k,1,m) REP(t,1,kk)
	{
		//pf("f[%d][%d][%d] = %d\n", i, k, t, f[i][k][t]);
	}*/
	cout << ans << "\n";
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	init();
	return 0;
}
