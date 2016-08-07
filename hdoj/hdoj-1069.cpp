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

#define lld I64d

const int maxn = 100;

struct Node
{
	int row, col, height;
	Node(): row(0), col(0), height(0){}
	Node(const int _row, const int _col, const int _height)
	{
		row = _row, col = _col, height = _height;
	}
	bool operator<(const Node &a)const
	{
		if(row<a.row && col<a.col) return true;
		if(row<a.col && col<a.row) return true;
		return false;
	}
}arr[maxn+5];

int n;
LL f[maxn+5];

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int NT = 0;
	int a, b, c;
	LL ans;
	while(sf("%d", &n), n)
	{
		REP(i,1,n)
		{
			sf("%d%d%d", &a, &b, &c);
			arr[i] = Node(a,b,c);
			arr[i+n] = Node(b,c,a);
			arr[i+n*2] = Node(a,c,b);
		}
		n *= 3;
		REP(i,1,n) f[i] = arr[i].height;
		for(int i=1; i<=n; ++i)
			for(int k=1; k<=n; ++k)
				for(int j=1; j<=n; ++j)
				{
					if(arr[k]<arr[j])
						f[k] = max(f[k], arr[k].height + f[j]);
				}
		ans = 0;
		REP(i,1,n) ans = max(ans, f[i]);
		pf("Case %d: maximum height = %lld\n", ++NT, ans);
	}
	return 0;
}
