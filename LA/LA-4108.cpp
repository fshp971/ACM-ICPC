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

const int maxn = 1e5;

struct Tree
{
	int maxi[maxn*4+5];
	int ll[maxn*4+5], rr[maxn*4+5];
	bool lazy[maxn*4+5];
	
	void build(int x, int l, int r)
	{
		ll[x] = l, rr[x] = r;
		lazy[x] = (x==1);
		maxi[x] = 0;
		if(l+1 < r)
		{
			int mid = (l+r) >> 1;
			build(x*2, l, mid);
			build(x*2+1, mid, r);
		}
	}

	int insert(int x, int l, int r, int dat)
	{
		if(l<=ll[x] && rr[x]<=r)
		{
			if(maxi[x] <= dat)
			{
				maxi[x] = dat, lazy[x] = true;
				return (rr[x]-ll[x]);
			}
			if(lazy[x] && dat < maxi[x])
				return 0;
		}
		if(lazy[x])
		{
			lazy[x] = false, lazy[x*2] = lazy[x*2+1] = true;
			maxi[x*2] = maxi[x*2+1] = maxi[x];
		}
		int mid = (ll[x]+rr[x]) >> 1, res = 0;
		if(l<mid) res += insert(x*2, l, r, dat);
		if(r>mid) res += insert(x*2+1, l, r, dat);
		maxi[x] = max(maxi[x*2], maxi[x*2+1]);
		if(lazy[x*2] && lazy[x*2+1] && maxi[x*2]==maxi[x*2+1])
			lazy[x*2] = lazy[x*2+1] = false, lazy[x] = true;
		return res;
	}
}tree;

int n;
int aa[maxn+5], bb[maxn+5], cc[maxn+5];

void init()
{
	int a, b, c, ans = 0;
	int l = 1<<30, r = -l;
	REP(i,1,n)
	{
		sf("%d%d%d", aa+i, bb+i, cc+i);
		l = min(l, aa[i]), r = max(r, bb[i]);
	}
	tree.build(1, l, r);
	REP(i,1,n)
		ans += tree.insert(1, aa[i], bb[i], cc[i]);
	pf("%d\n", ans);
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	cin >> n;
	while(sf("%d", &n), n)
		init();
	return 0;
}
