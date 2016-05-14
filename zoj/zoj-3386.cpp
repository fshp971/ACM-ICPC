#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b)

const int maxv = 1e7;
const int maxn = 1e5;

struct node
{
	int ll,rr,sum,mx,mn;
}tree[maxn*6+10];

int n,arr[maxn+10];

bool nico[maxv+10];

void build(int x,int ll,int rr)
{
	tree[x].ll = ll; tree[x].rr = rr;
	if(ll==rr)
	{
		tree[x].mx = tree[x].mn = arr[ll];
		tree[x].sum = (int)nico[arr[ll]];
		return;
	}
	int mid = (ll+rr)>>1;
	build(x*2,ll,mid); build(x*2+1,mid+1,rr);
	tree[x].sum = tree[x*2].sum + tree[x*2+1].sum;
	tree[x].mx = max(tree[x*2].mx, tree[x*2+1].mx);
	tree[x].mn = min(tree[x*2].mn, tree[x*2+1].mn);
	return;
}

int cal(int x,int ll,int rr)
{
	if(ll<=tree[x].ll && tree[x].rr<=rr)
		return tree[x].sum;
	int mid = (tree[x].ll+tree[x].rr)>>1;
	int res = 0;
	if(ll<=mid) res += cal(x*2,ll,rr);
	if(rr>mid) res += cal(x*2+1,ll,rr);
	return res;
}

void update(int x,int ll,int rr,int md)
{
	if(tree[x].mx<md) return;
	if(tree[x].ll == tree[x].rr)
	{
		arr[tree[x].ll] %= md;
		tree[x].mx = tree[x].mn = arr[tree[x].ll];
		tree[x].sum = (int)nico[tree[x].mx];
		return;
	}
	int mid = (tree[x].ll+tree[x].rr)>>1;
	if(ll<=mid) update(x*2,ll,rr,md);
	if(rr>mid) update(x*2+1,ll,rr,md);
	tree[x].sum = tree[x*2].sum + tree[x*2+1].sum;
	tree[x].mx = max(tree[x*2].mx, tree[x*2+1].mx);
	tree[x].mn = min(tree[x*2].mn, tree[x*2+1].mn);
	return;
}

void add(int x,int poi,int dat)
{
	if(tree[x].ll == tree[x].rr)
	{
		arr[poi] = dat;
		tree[x].mx = tree[x].mn = arr[poi];
		tree[x].sum = (int)nico[arr[poi]];
		return;
	}
	int mid = (tree[x].ll+tree[x].rr)>>1;
	if(poi<=mid) add(x*2,poi,dat);
	else add(x*2+1,poi,dat);
	tree[x].sum = tree[x*2].sum + tree[x*2+1].sum;
	tree[x].mx = max(tree[x*2].mx, tree[x*2+1].mx);
	tree[x].mn = min(tree[x*2].mn, tree[x*2+1].mn);
	return;
}

void init()
{
	REP(i,1,n) scanf("%d",arr+i);
	build(1,1,n);
	int qer,ord,ll,rr,md;
	scanf("%d",&qer);
	REP(i,1,qer)
	{
		scanf("%d",&ord);
		if(ord==1)
		{
			scanf("%d%d",&ll,&rr);
			printf("%d\n",cal(1,ll,rr));
		}
		else if(ord==2)
		{
			scanf("%d%d%d",&ll,&rr,&md);
			update(1,ll,rr,md);
		}
		else
		{
			scanf("%d%d",&ll,&md);
			add(1,ll,md);
		}
	}
	return;
}

void nico_maker()
{
	mem(nico,0);
	for(int i=3;i<=maxv;i+=2) nico[i] = true;
	for(int i=3;i<=maxv;i+=2)
	{
		if(nico[i])
		{
			for(int k=i+i;k<=maxv;k+=i)
				nico[k] = false;
		}
	}
	//Is 1 a ncio-number?
	nico[0] = true;
	int two = 1;
	nico[6] = true;
	while(two<=maxv)
	{
		nico[two] = true;
		two *= 2;
	}
	//int res=0;
	//REP(i,1,maxv) if(nico[i]) ++res;
	//printf("res = %d\n",res);
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	nico_maker();
	while(~scanf("%d",&n))
		init();
	return 0;
}
