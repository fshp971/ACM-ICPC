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

int n;
bool vis[300000][20];

double f[300000][20];
double pi[20][20];

double run(int type, int x)
{
	if(vis[type][x]) return f[type][x];
	vis[type][x] = true;
	f[type][x] = 0.0;
	FOR(i,0,n) if(type&(1<<i) && x!=i)
		f[type][x] = max(f[type][x], run(type-(1<<i), x)*pi[x][i] + run(type-(1<<x), i)*pi[i][x]);
	return f[type][x];
}

void init()
{
	cin >> n;
	FOR(i,0,n) FOR(k,0,n)
		cin >> pi[i][k];
	mem(f,0); mem(vis,0);
	f[1][0] = 1.0; vis[1][0] = true;
	double ans = 0;
	FOR(i,0,n)
		ans = max(ans, run((1<<n)-1, i));
	pf("%.8f\n", ans);
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	init();
	return 0;
}
