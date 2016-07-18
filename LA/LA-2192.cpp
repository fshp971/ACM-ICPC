#include<bits/stdc++.h>

using namespace std;

#define LL long long
#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define MP(a,b) make_pair(a,b)
#define pii pair<int,int>
#define sf scanf
#define pf printf

const int maxN = 1<<20;

int n, N;
int tree[maxN*2+5];

void build()
{
	for(int i=N-1; i>=1; --i) tree[i] = tree[i<<1] + tree[i<<1|1];
}

void update(int x, int dat)
{
	tree[x = N-1+x] = dat;
	for(x >>= 1; x; x >>= 1) tree[x] = tree[x<<1] + tree[x<<1|1];
}

int query(int l, int r)
{
	int res = 0;
	for(l = l+N-1, r = r+N-1; l<=r; l >>= 1, r >>= 1)
	{
		if(l&1) res += tree[l++];
		if(~r&1) res += tree[r--];
	}
	return res;
}

void init()
{
	REP(i,1,n) sf("%d", tree+(N-1)+i);
	REP(i,n+1,N) tree[i+N-1] = 0;
	build();
	int x, y;
	char ord[5];
	while(sf("%s", ord), ord[0] != 'E')
	{
		sf("%d%d", &x, &y);
		if(ord[0] == 'S')
			update(x, y);
		else
			pf("%d\n", query(x, y));
	}
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int t = 0;
	while(sf("%d", &n), n)
	{
		if(t)
			pf("\n");
		pf("Case %d:\n", ++t);
		for(N = 1; N < n; N<<=1);
		init();
	}
	return 0;
}
