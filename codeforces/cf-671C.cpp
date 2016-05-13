#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<queue>
#include<string>
#include<utility>
#include<map>
#include<set>
#include<vector>

using namespace std;

#define LL long long
#define MP(a,b) make_pair(a,b)
#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define pii pair<int,int>

const int maxn = 200000;

struct node
{
	int ll,rr,mx,mn;
	LL sum;
}tree[maxn*5+10];

vector<int> G[maxn+10];

int n,arr[maxn+10];

LL f[maxn+10];

void build(int x,int ll,int rr)
{
	tree[x].ll=ll; tree[x].rr=rr;
	if(ll==rr)
	{
		tree[x].sum = tree[x].mx = tree[x].mn = ll;
		return;
	}
	int mid=(ll+rr)>>1;
	build(x*2,ll,mid);
	build(x*2+1,mid+1,rr);
	tree[x].mx = max(tree[x*2].mx, tree[x*2+1].mx);
	tree[x].mn = min(tree[x*2].mn, tree[x*2+1].mn);
	tree[x].sum = tree[x*2].sum + tree[x*2+1].sum;
	return;
}

void update(int x,int ll,int rr,int dat)
{
	if(dat <= tree[x].mn) return;
	if(ll<=tree[x].ll && tree[x].rr<=rr && tree[x].mx<=dat)
	{
		tree[x].mx = tree[x].mn = dat;
		tree[x].sum = (LL)(tree[x].rr-tree[x].ll+1) * dat;
		return;
	}
	if(tree[x].mx == tree[x].mn)
	{
		tree[x*2].mx = tree[x*2].mn = tree[x].mx;
		tree[x*2].sum = (LL)(tree[x*2].rr-tree[x*2].ll+1)*tree[x].mx;
		tree[x*2+1].mx = tree[x*2+1].mn = tree[x].mx;
		tree[x*2+1].sum = (LL)(tree[x*2+1].rr-tree[x*2+1].ll+1)*tree[x].mx;
	}
	int mid = (tree[x].ll+tree[x].rr)>>1;
	if(ll<=mid) update(x*2,ll,rr,dat);
	if(rr>mid) update(x*2+1,ll,rr,dat);
	tree[x].mx = max(tree[x*2].mx, tree[x*2+1].mx);
	tree[x].mn = min(tree[x*2].mn, tree[x*2+1].mn);
	tree[x].sum = tree[x*2].sum + tree[x*2+1].sum;
	return;
}

void init()
{
	cin>>n;
	int a;
	REP(i,1,n)
	{
		scanf("%d",&a);
		arr[a]=i;
	}
	build(1,1,n);
	REP(i,1,maxn)
		for(int k=i;k<=maxn;k+=i)
		{
			if(arr[k]) G[i].push_back(arr[k]);
		}
	f[0] = 0; f[maxn+1] = (LL)n*(n+1)/2;
	for(int i=maxn;i>=1;--i)
	{
		if(G[i].size() < 2)
		{
			f[i] = f[i+1];
			continue;
		}
		sort(G[i].begin(), G[i].end());
		int len = G[i].size();
		update(1, 1, G[i][0], G[i][len-2]);
		update(1, G[i][0]+1, G[i][1], G[i][len-1]);
		if(n>G[i][1])
			update(1, G[i][1]+1, n, n+1);
		f[i] = (LL)n*(n+1) - tree[1].sum;
	}
	LL ans=0;
	cout<<ans<<"\n";
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	init();
	return 0;
}
