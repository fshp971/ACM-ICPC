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

const int maxn = 100000;
const LL INF = ((LL)1<<60);

struct node
{
	int lson, rson;
	LL dat;
}tree[maxn*4+10];

int n,arr[maxn+10];

LL f[maxn+10];

void build(int x,int lson,int rson)
{
	tree[x].lson = lson; tree[x].rson = rson;
	tree[x].dat = INF;
	if(lson == rson) return;
	int mid = (lson+rson) >> 1;
	build(x*2,lson,mid); build(x*2+1,mid+1,rson);
}

void update(int x, int poi, LL dat)
{
	if(tree[x].lson == tree[x].rson)
	{
		tree[x].dat = dat;
		return;
	}
	int mid = (tree[x].lson+tree[x].rson) >> 1;
	if(poi<=mid) update(x*2,poi,dat);
	else update(x*2+1,poi,dat);
	tree[x].dat = min(tree[x*2].dat, tree[x*2+1].dat);
}

LL cal(int x,int ll,int rr)
{
	if(ll<=tree[x].lson && tree[x].rson<=rr)
		return tree[x].dat;
	int mid = (tree[x].lson+tree[x].rson) >> 1;
	LL ans = INF;
	if(ll<=mid) ans = min(ans, cal(x*2,ll,rr));
	if(rr>mid) ans = min(ans, cal(x*2+1,ll,rr));
	return ans;
}

void init()
{
	cin>>n;
	FOR(i,1,n) scanf("%d",arr+i);
	build(1,1,n);
	update(1,n,n);
	//return;
	f[n] = 0;
	for(int i=n-1;i>=1;--i)
	{
		//printf("i = %d\n",i);
		f[i] = cal(1,i+1,arr[i]) + n-i-arr[i];
		update(1,i,f[i]+i);
	}
	LL ans = 0;
	REP(i,1,n) ans += f[i];
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
