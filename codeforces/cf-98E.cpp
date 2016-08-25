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

double f[maxn+5][maxn+5];
char vis[maxn+5][maxn+5];

double dfs(int i, int j)
{
	if(vis[i][j]) return f[i][j];
	vis[i][j] = 1;
	if(!j) return f[i][j] = 1.0;
	if(!i) return f[i][j] = 1.0/(double)(j+1);
	double n = i, m = j;
	double p1 = 1.0;
	double p2 = 1.0 - dfs(j, i-1);
	double p3 = m/(m+1) * (1.0 - dfs(j-1, i));
	double p4 = 1.0 - m/(m+1) * dfs(j-1, i);
	double p = (p2-p4) / (p2-p4+p3-p1);
	return f[i][j] = max(1.0/(m+1), p*p1 + (1-p)*p2);
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int n, m;
	sf("%d%d", &n, &m);
	mem(vis, 0);
	double ans = dfs(n, m);
	pf("%.10f %.10f\n", ans, 1.0-ans);
	return 0;
}
