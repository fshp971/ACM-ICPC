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

const int maxn = 200000;

int n, sumx;
LL xx, yy;

int h[maxn+10], e[maxn*2+10], nex[maxn*2+10];
int cnt[maxn+10];

int dfs(int x, int fa)
{
	int son = 2;
	for(int i=h[x]; i; i=nex[i])
	{
		if(e[i] == fa) continue;
		if(dfs(e[i], x) && son)
		{
			++sumx; --son;
		}
	}
	return son; 
}

LL init()
{
	cin >> n >> xx >> yy;
	mem(h,0); mem(cnt,0);
	int top = 0;
	sumx = 0;
	FOR(i,1,n)
	{
		int a, b;
		sf("%d%d", &a, &b);
		e[++top] = b; nex[top] = h[a]; h[a] =top;
		e[++top] = a; nex[top] = h[b]; h[b] =top;
		++cnt[a]; ++cnt[b];
		if(cnt[a]==n-1 || cnt[b]==n-1) sumx = 1;
	}
	if(xx<=yy)
	{
		sumx = 0;
		dfs(1, 0);
	}
	return xx * sumx + yy * (n-1-sumx);
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	cout << init() << "\n";
	return 0;
}
