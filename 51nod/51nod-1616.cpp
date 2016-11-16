#include<cstdio>
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

const int maxa = 1e6;

int n;
int f[maxa+5];
char vis[maxa+5];

int main()
{
	int a, ans = 0, fg;
	sf("%d", &n);
	REP(i,1,n)
		sf("%d", &a), vis[a] = 1;
	for(int i=1; i<=maxa; ++i)
	{
		for(int k=i; k<=maxa; k+=i)
			if(vis[k]) ++f[i];
	}
	for(int i=1; i<=maxa; ++i)
	{
		if(!f[i]) continue;
		fg = 1;
		for(int k=i+i; k<=maxa; k+=i)
			if(f[i] == f[k])
			{
				fg = 0;
				break;
			}
		ans += fg;
	}
	pf("%d\n", ans);
	return 0;
}
