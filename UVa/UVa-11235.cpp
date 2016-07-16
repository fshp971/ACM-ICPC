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

const int maxn = 100000;

int n, que, top, arr[maxn+5];
int rmq[maxn+5][21];
pii seg[maxn+5];

int find_seg(int x)
{
	int ll = 1, rr = top;
	while(ll <= rr)
	{
		int mid = (ll+rr) >> 1;
		if(seg[mid].first<=x && x<=seg[mid].second)
			return mid;
		else if(x > seg[mid].second)
			ll = mid+1;
		else
			rr = mid-1;
	}
}

void init()
{
	arr[top=0] = -(1<<30);
	int a, b;
	REP(i,1,n)
	{
		sf("%d", &a);
		if(arr[top] != a)
		{
			arr[++top] = a;
			rmq[top][0] = 1;
			seg[top].first = seg[top].second = i;
		}
		else ++rmq[top][0], ++seg[top].second;
	}
	for(int i=1; (1<<i)<=top; ++i)
	{
		for(int k=top; k>=(1<<i); --k)
			rmq[k][i] = max(rmq[k][i-1], rmq[k-(1<<(i-1))][i-1]);
	}
	/*for(int i=1;i<=top;++i)
	{
		for(int k=0;k<=4;++k)
			pf("rmq[%d][%d] = %d\n", i, k, rmq[i][k]);
	}
	pf("\n");*/
	REP(t,1,que)
	{
		sf("%d%d", &a, &b);
		int k = 0, res;
		int pa = find_seg(a), pb = find_seg(b);
		if(pa == pb)
			res = b-a+1;
		else
			res = max(seg[pa].second-a+1, b-seg[pb].first+1);
		//pf("pa = %d, pb = %d\n", pa, pb);
		//pf("res1 = %d\n", res);
		if(pa+1 <= pb-1)
		{
			while((1<<(k+1)) < (pb-pa))
				++k;
			//pf("k = %d\n", k);
			//pf("a = %d, b = %d, k = %d\n", a, b, k);
			res = max(res, max(rmq[pb-1][k], rmq[pa+(1<<k)][k]));
		}
		pf("%d\n", res);
	}
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	while(sf("%d", &n), n)
	{
		sf("%d", &que);
		init();
	}
	return 0;
}
