#include<bits/stdc++.h>

using namespace std;

#define LL long long
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define mem(a,b) memset(a,b,sizeof(a))
#define MP make_pair
#define pii pair<int,int>
#define sf scanf
#define pf printf

const int maxn = 15;

int n, sum;
int arr[maxn+5];

struct TriNode
{
	int a, b, c;
	TriNode(int _a, int _b, int _c)
	{
		a = _a, b = _b, c = _c;
	}
	bool operator<(const TriNode &t) const
	{
		if(a != t.a) return a<t.a;
		if(b != t.b) return b<t.b;
		return c<t.c;
	}
};

set<TriNode> Set;

inline bool check(int a, int b, int c)
{
	return a<=b && b<=c && a>0 && b>0 && c>0 && a+b>c && a+c>b && b+c>a;
}

void dfs2(int poi, int side1, int side2, int side3, int step)
{
	for(int i=step; i<n; ++i)
	{
		if(poi & (1<<i)) continue;
		side2 += arr[i];
		side3 -= arr[i];
		if(check(side1, side2, sum-side1-side2))
			Set.insert( TriNode(side1, side2, side3) );
		if(side2 < side3)
			dfs2(poi, side1, side2, side3, i+1);
		side2 -= arr[i];
		side3 += arr[i];
	}
}

void dfs1(int poi, int side1, int step)
{
	for(int i=step; i<n; ++i)
	{
		side1 += arr[i];
		if(side1*3 <= sum)
		{
			dfs2(poi+(1<<i), side1, 0, sum-side1,0);
			dfs1(poi+(1<<i), side1, i+1);
		}
		side1 -= arr[i];
	}
}

int main()
{
	int T;
	sf("%d", &T);
	while(T--)
	{
		sf("%d", &n);
		sum = 0;
		Set.clear();
		for(int i=0; i<n; ++i)
			sf("%d", arr+i), sum += arr[i];
		dfs1(0, 0, 0);
		cout << Set.size() << "\n";
	}
	return 0;
}
