#include<bits/stdc++.h>

using namespace std;

#define LL long long
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define pii pair<int,int>
#define mem(a,b) memset(a,b,sizeof(a))
#define MP(a,b) make_pair(a,b)
#define sf scanf
#define pf printf

const int maxn = 1<<20;

int n, que, N;
int tree[maxn*2+5];

void build()
{
	for(int i=N-1; i; --i) tree[i] = min(tree[i<<1], tree[i<<1|1]);
}

void update(int x, int dat)
{
	for(tree[x+=N-1] = dat, x>>=1; x; x>>=1) tree[x] = min(tree[x<<1], tree[x<<1|1]);
}

int query(int l, int r)
{
	int res = 1<<30;
	for(l+=N-1, r+=N-1; l<=r; l>>=1, r>>=1)
	{
		if(l&1) res = min(res, tree[l++]);
		if(~r&1) res = min(res, tree[r--]);
	}
	return res;
}

bool input(pii* sta, int& top)
{
	char arr[40];
	sf("%s", arr);
	top = 0;
	bool fg = false, num = false;
	int x = 0;
	if(arr[0] == 'q') fg = true;
	for(int i=1;i<strlen(arr);++i)
	{
		char &c = arr[i];
		if('0'<=c && c<='9')
			x = x*10 + c-48, num = true;
		else if(num)
			sta[top++].first = x, x = 0, num = false;
	}
	FOR(i,0,top)
		sta[i].second = tree[sta[(i+1)%top].first+N-1];
	return fg;
}

void init()
{
	sf("%d%d", &n, &que);
	for(N = 1; N < n; N <<= 1);
	REP(i,1,n) sf("%d", tree+N-1+i);
	REP(i,n+1,N) tree[i+N-1] = 1<<30;
	build();
	pii sta[40];
	int top;
	REP(i,1,que)
	{
		if(input(sta, top))
			pf("%d\n", query(sta[0].first, sta[1].first));
		else
		{
			FOR(k,0,top)
				update(sta[k].first, sta[k].second);
		}
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
