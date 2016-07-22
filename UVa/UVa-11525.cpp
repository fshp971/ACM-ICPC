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

const int maxn = 50000, INF = 1<<30;

int n, N;
int ans[maxn+5];

struct Tree
{
	pii mini[maxn*4+5];
	int ll[maxn*4+5], rr[maxn*4+5], del[maxn*4+5];
	bool lazy[maxn*4+5];
	void build(int x, int l, int r)
	{
		ll[x] = l, rr[x] = r, del[x] = 0;
		lazy[x] = false;
		if(l == r)
		{
			mini[x] = MP(0, l);
			return;
		}
		int mid = (l+r) >> 1;
		build(x*2, l, mid);
		build(x*2+1, mid+1, r);
		mini[x] = min(mini[x*2], mini[x*2+1]);
		return;
	}

	void update(int x, int l, int r, int val)
	{
		if(l<=ll[x] && rr[x]<=r)
		{
			if(lazy[x]) del[x] += val;
			else lazy[x] = true, del[x] = val;
			mini[x].first += val;
			return;
		}
		if(lazy[x])
		{
			lazy[x] = false;
			if(lazy[x*2])
				del[x*2] += del[x];
			else lazy[x*2] = true, del[x*2] = del[x];
			mini[x*2].first += del[x];

			if(lazy[x*2+1])
				del[x*2+1] += del[x];
			else lazy[x*2+1] = true, del[x*2+1] = del[x];
			mini[x*2+1].first += del[x];
		}
		int mid = (ll[x]+rr[x]) >> 1;
		if(l<=mid) update(x*2, l, r, val);
		if(r>mid) update(x*2+1, l, r, val);
		mini[x] = min(mini[x*2], mini[x*2+1]);
		return;
	}

	pii query(int x, int l, int r)
	{
		if(l<=ll[x] && rr[x]<=r) return mini[x];
		int mid = (ll[x]+rr[x]) >> 1;
		pii res = MP(INF, INF);
		if(l<=mid) res = min(res, query(x*2, l, r));
		if(r>mid) res = min(res, query(x*2+1, l, r));
		return res;
	}
}tree;

void init()
{
	int a;
	cin >> n;
	tree.build(1, 1, n);
	for(int i=1;i<=n;++i)
	{
		sf("%d", &a);
		tree.update(1, i, i, a);
	}
	for(int i=1;i<=n;++i)
	{
	   pii tmp = tree.query(1,1,n);
	   ans[tmp.second] = i;
	   if(tmp.second<n) tree.update(1, tmp.second+1, n, 1);
	   tree.update(1, tmp.second, tmp.second, INF);
	}
	REP(i,1,n)
	{
		if(i>1) pf(" ");
		pf("%d", ans[i]);
	}
	pf("\n");
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int t;
	cin >> t;
	while(t--)
		init();
	return 0;
}
