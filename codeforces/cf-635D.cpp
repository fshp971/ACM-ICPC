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

struct node
{
	int ll, rr;
	LL max_a, max_b;
}tree[maxn*5+10];

int n, kk, que;
LL aa, bb;

void build(int x, int ll, int rr)
{
	 tree[x].ll = ll; tree[x].rr = rr;
	 tree[x].max_a = tree[x].max_b = 0;
	 if(ll == rr) return;
	 int mid = (ll+rr) >> 1;
	 build(x*2, ll, mid);
	 build(x*2+1, mid+1, rr);
	 return;
}

void update(int x, int di, int ai)
{
	if(tree[x].ll == tree[x].rr)
	{
		tree[x].max_a = min(tree[x].max_a+ai, aa);
		tree[x].max_b = min(tree[x].max_b+ai, bb);
		return;
	}
	int mid = (tree[x].ll+tree[x].rr) >> 1;
	if(di <= mid) update(x*2, di, ai);
	else update(x*2+1, di, ai);
	tree[x].max_a = tree[x*2].max_a + tree[x*2+1].max_a;
	tree[x].max_b = tree[x*2].max_b + tree[x*2+1].max_b;
	return;
}

LL count_a(int x, int ll, int rr)
{
	if(ll<=tree[x].ll && tree[x].rr<=rr) return tree[x].max_a;
	int mid = (tree[x].ll+tree[x].rr) >> 1;
	LL res = 0;
	if(ll <= mid) res += count_a(x*2, ll, rr);
	if(rr > mid) res += count_a(x*2+1, ll, rr);
	return res;
}

LL count_b(int x, int ll, int rr)
{
	if(ll<=tree[x].ll && tree[x].rr<=rr) return tree[x].max_b;
	int mid = (tree[x].ll+tree[x].rr) >> 1;
	LL res = 0;
	if(ll <= mid) res += count_b(x*2, ll, rr);
	if(rr > mid) res += count_b(x*2+1, ll, rr);
	return res;
}

void init()
{
	cin >> n >> kk >> aa >> bb >> que;
	int ord, di, ai, pi;
	build(1,1,n);
	REP(i,1,que)
	{
		sf("%d", &ord);
		if(ord == 1)
		{
			sf("%d%d", &di, &ai);
			update(1, di, ai);
		}
		else
		{
			sf("%d", &pi);
			int p2 = pi+kk-1;
			LL res = 0;
			if(p2 < n) res += count_a(1, p2+1, n);
			if(1 < pi) res += count_b(1, 1, pi-1);
			cout << res << "\n";
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
