//#include<cstdio>
//cnm cstdio TLE10+
#include<stdio.h>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<queue>
#include<string>
#include<vector>
#include<utility>
#include<map>
#include<set>

using namespace std;

#define LL long long
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define pii pair<int,int>
#define MP(a,b) make_pair(a,b)
#define mem(a,b) memset(a,b,sizeof(a))
#define sf scanf
#define pf printf

const int maxn = 2e5;

int n, que;
int fa1[maxn+5], fa2[maxn+5], pre[maxn+5], nex[maxn+5];

int find(int *fa, int x) { return fa[x] == x ? x : fa[x] = find(fa, fa[x]); }

void merge(int x)
{
	for(int i=pre[x]; i && find(fa1,x) == find(fa1,i); i=pre[x])
	{
		fa2[i] = x;
		pre[x] = pre[i];
	}
	for(int i=nex[x]; i && find(fa1,x) == find(fa1,i); i=nex[x])
	{
		fa2[i] = x;
		nex[x] = nex[i];
	}
}

int main()
{
	int type, x, y;
	sf("%d%d", &n, &que);
	REP(i,1,n)
	{
		fa1[i] = fa2[i] = i;
		nex[i] = i+1, pre[i] = i-1;
	}
	nex[n] = 0, pre[1] = 0;
	REP(i,1,que)
	{
		sf("%d%d%d", &type, &x, &y);
		x = find(fa2, x);
		y = find(fa2, y);
		nex[n] = pre[1] = 0;
		if(type == 1)
		{
			fa1[ find(fa1, x) ] = find(fa1, y);
			merge(x);
			y = find(fa2, y);
			merge(y);
		}
		else if(type == 2)
		{
			if(x == y) continue;
			for(int i=nex[x]; i && i<=y; i=nex[x])
			{
				fa1[ find(fa1,i) ] = find(fa1,x);
				fa2[i] = x;
				nex[x] = nex[i];
			}
			merge(x);
		}
		else
			pf(find(fa1,x) == find(fa1,y) ? "YES\n" : "NO\n");
	}
	return 0;
}
