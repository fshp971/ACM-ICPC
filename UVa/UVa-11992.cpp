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

const int maxn = 1e6;

int row, col, m;

struct Node
{
	int l, r, sum, num, del;
	int mini, maxi;
	bool equ, lzy;
	void up_date(int x)
	{
		if(equ) num += x;
		else del += x, lzy = true;
		sum += (r-l+1) * x;
	}
	void set_date(int x)
	{
		lzy = false, del = 0;
		equ = true, num = x;
		sum = (r-l+1) * x;
	}
	int get_min()
	{
		int res = mini;
		if(equ) res = num;
		if(lzy) res += del;
		return res;
	}
	int get_max()
	{
		int res = maxi;
		if(equ) res = num;
		if(lzy) res += del;
		return res;
	}
};//dat[21][4*maxn+2];

Node dat[maxn*5+2];

void build(Node* tree, int x, int l, int r)
{
	tree[x].l = l, tree[x].r = r;
	tree[x].sum = tree[x].del = tree[x].num = 0;
	tree[x].equ = tree[x].lzy = false;
	tree[x].mini = tree[x].maxi = 0;
	if(l < r)
	{
		int mid = (tree[x].l+tree[x].r) >> 1;
		build(tree, x*2, l, mid);
		build(tree, x*2+1, mid+1, r);
	}
	return;
}

void up_inc(Node* tree, int x, int l, int r, int del)
{
	if(l<=tree[x].l && tree[x].r<=r)
	{
		tree[x].up_date(del);
		return;
	}
	if(tree[x].equ)
	{
		tree[x*2].set_date(tree[x].num);
		tree[x*2+1].set_date(tree[x].num);
		tree[x].equ = false, tree[x].num = 0;
	}
	else if(tree[x].del)
	{
		tree[x*2].up_date(tree[x].del);
		tree[x*2+1].up_date(tree[x].del);
		tree[x].lzy = false, tree[x].del = 0;
	}
	int mid = (tree[x].l+tree[x].r) >> 1;
	if(l<=mid) up_inc(tree, x*2, l, r, del);
	if(r>=mid+1) up_inc(tree, x*2+1, l, r, del);
	tree[x].sum = tree[x*2].sum + tree[x*2+1].sum;
	tree[x].mini = min(tree[x*2].get_min(), tree[x*2+1].get_min());
	tree[x].maxi = max(tree[x*2].get_max(), tree[x*2+1].get_max());
	return;
}

void set_inc(Node* tree, int x, int l, int r, int num)
{
	if(l<=tree[x].l && tree[x].r<=r)
	{
		tree[x].set_date(num);
		return;
	}
	if(tree[x].equ)
	{
		tree[x*2].set_date(tree[x].num);
		tree[x*2+1].set_date(tree[x].num);
		tree[x].equ = false, tree[x].num = 0;
	}
	else if(tree[x].del)
	{
		tree[x*2].up_date(tree[x].del);
		tree[x*2+1].up_date(tree[x].del);
		tree[x].lzy = false, tree[x].del = 0;
	}
	int mid = (tree[x].l+tree[x].r) >> 1;
	if(l<=mid) set_inc(tree, x*2, l, r, num);
	if(r>=mid+1) set_inc(tree, x*2+1, l, r, num);
	tree[x].sum = tree[x*2].sum + tree[x*2+1].sum;
	tree[x].mini = min(tree[x*2].get_min(), tree[x*2+1].get_min());
	tree[x].maxi = max(tree[x*2].get_max(), tree[x*2+1].get_max());
	return;
}

int query(Node* tree, int x, int l, int r, int &mini, int &maxi)
{
	if(l<=tree[x].l && tree[x].r<=r)
	{
		mini = min(mini, tree[x].get_min());
		maxi = max(maxi, tree[x].get_max());
		return tree[x].sum;
	}
	if(tree[x].equ)
	{
		tree[x*2].set_date(tree[x].num);
		tree[x*2+1].set_date(tree[x].num);
		tree[x].equ = false, tree[x].num = 0;
	}
	else if(tree[x].del)
	{
		tree[x*2].up_date(tree[x].del);
		tree[x*2+1].up_date(tree[x].del);
		tree[x].lzy = false, tree[x].del = 0;
	}
	tree[x].mini = min(tree[x*2].get_min(), tree[x*2+1].get_min());
	tree[x].maxi = max(tree[x*2].get_max(), tree[x*2+1].get_max());
	int res = 0;
	int mid = (tree[x].l+tree[x].r) >> 1;
	if(l <= mid) res += query(tree, x*2, l, r, mini, maxi);
	if(r >= mid+1) res += query(tree, x*2+1, l, r, mini, maxi);
	return res;
}

void init()
{
	int ord, x1, y1, x2, y2, v;
	REP(i,1,row)
	{
		build(dat+(i-1)*col*5, 1, 1, col);
		dat[(i-1)*col*5 + 1].equ = true;
		//dat[i][1].equ = true;
	}
	REP(i,1,m)
	{
		sf("%d%d%d%d%d", &ord, &x1, &y1, &x2, &y2);
		if(ord == 1)
		{
			sf("%d", &v);
			REP(k,x1,x2)
				up_inc(dat+(k-1)*col*5, 1, y1, y2, v);
		}
		else if(ord == 2)
		{
			sf("%d", &v);
			REP(k,x1,x2)
				set_inc(dat+(k-1)*col*5, 1, y1, y2, v);
		}
		else
		{
			int ans = 0;
			int mini = 1<<30, maxi = -mini;
			REP(k,x1,x2)
			{
				ans += query(dat+(k-1)*col*5, 1, y1, y2, mini, maxi);
			}


			pf("%d %d %d\n", ans, mini, maxi);
		}
	}
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	while(~sf("%d%d%d", &row, &col, &m))
		init();
	return 0;
}
