#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<queue>
#include<utility>
#include<map>
#include<set>
#include<bitset>

using namespace std;

#define LL long long
#define MP make_pair
#define pii pair<int,int>
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define sf scanf
#define pf printf

const int maxn = 100000;

int n, T, arr[maxn+5];

int tree[maxn*2+5], top;

void up(int x)
{
	int k;
	while(x>1)
	{
		k = x>>1;
		if(tree[k] > tree[x])
		{
			swap(tree[k], tree[x]);
			swap(k, x);
		}
		else break;
	}
}

void down(int x)
{
	int k;
	while((k = x<<1) <= top)
	{
		if(k+1<=top && tree[k+1]<tree[k]) ++k;
		if(tree[k] < tree[x])
		{
			swap(tree[k], tree[x]);
			swap(k, x);
		}
		else break;
	}
}

char check(int kk)
{
	int tmp = (n-1)/(kk-1);
	if(tmp*(kk-1) < n-1) ++tmp;
	tmp = (kk-1)*tmp + 1;
	top = 0;
	for(int i=1; i<=tmp-n; ++i)
	{
		tree[++top] = 0;
		up(top);
	}
	for(int i=1; i<=n; ++i)
	{
		tree[++top] = arr[i];
		up(top);
	}
	LL all = 0, del;
	while(top > 1)
	{
		del = 0;
		for(int i=1; i<=kk; ++i)
		{
			del += tree[1];
			tree[1] = tree[top--];
			down(1);
		}
		if((all+=del) > T) return 0;
		tree[++top] = del;
		up(top);
	}
	return 1;
}

int main()
{
	//freopen("in.txt", "r", stdin);
	//freopen("out.txt", "w", stdout);
	int t0, l, r, mid, ans;
	sf("%d", &t0);
	while(t0--)
	{
		sf("%d%d", &n, &T);
		REP(i,1,n) sf("%d", arr+i);
		l = 2, r = n, ans = 0;
		while(l<r)
		{
			mid = (l+r) >> 1;
			if(check(mid))
				ans = mid, r = mid-1;
			else l = mid+1;
		}
		pf("%d\n", ans);
	}
	return 0;
}
