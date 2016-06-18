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

const int maxn = 1e5;

int n;
int h[maxn+5], e[maxn*2+5], nex[maxn*2+5], wi[maxn*2+5];
int val[maxn+5];
bool vis[maxn+5];

int ans = 0;

void dfs(int x, LL sum)
{
	++ans; vis[x] = true;
	//pf("x = %d\n",x);
	if(sum < 0) sum = 0;
	for(int i=h[x]; i; i=nex[i])
	{
		int son = e[i];
		if(vis[son]) continue;
		if(sum + wi[i] > (LL)val[son]) continue;
		dfs(son, sum+wi[i]);
	}
	return;
}

void init()
{
	cin >> n;
	REP(i,1,n) sf("%d", val+i);
	int top = 0, a, b;
	mem(h,0);
	REP(i,2,n)
	{
		sf("%d%d", &a, &b);
		e[++top] = a; wi[top] = b; nex[top] = h[i]; h[i] = top;
		e[++top] = i; wi[top] = b; nex[top] = h[a]; h[a] = top;
	}
	mem(vis,0);
	dfs(1, 0);
	cout << n - ans << "\n";
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	init();
	return 0;
}
