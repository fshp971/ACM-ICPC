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

const LL INF = (LL)1 << 50;

int n, m, kk, col[105];
int wi[105][105];
LL f[105][105][105];

LL dfs(int poi, int n_col, int all)
{
	if(all < 0) return INF;
	if(f[poi][n_col][all] != -1) return f[poi][n_col][all];
	if(poi == 1) return f[poi][n_col][all] = all ? INF : 0;
	LL res = INF, tmp;
	if(col[poi-1])
		return f[poi][n_col][all] = dfs(poi-1, col[poi-1], n_col == col[poi-1] ? all : all-1);
	for(int i=1; i<=m; ++i)
	{
		//col[poi-1] = i;
		tmp = dfs(poi-1, i, n_col == i ? all : all-1) + wi[poi-1][i];
		res = min(res, tmp);
	}
	//col[poi-1] = 0;
	return f[poi][n_col][all] = res;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	mem(f, -1);
	sf("%d%d%d", &n, &m, &kk);
	REP(i,1,n) sf("%d", col+i);
	REP(i,1,n) REP(k,1,m) sf("%d", &wi[i][k]);
	LL ans = dfs(n+1, m+1, kk);
	if(ans == INF) pf("-1\n");
	else pf("%lld\n", ans);
	return 0;
}
