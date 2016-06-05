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
#define sf scanf
#define pf printf

const int maxn = 100000;

int n,kk,hh;
int arr[maxn+10];

void init()
{
	cin>>n>>hh>>kk;
	REP(i,1,n) sf("%d",arr+i);
	int now = 1, rem = 0;
	LL NT = 0;
	while(1)
	{
		while(now<=n && arr[now]<=hh-rem)
		{
			rem += arr[now];
			++now;
		}
		int tmp;
		if(now == n+1)
		{
			tmp = rem/kk;
			if(tmp*kk < rem) ++tmp;
			NT += tmp;
			break;
		}
		int delta = rem - (hh-arr[now]);
		tmp = delta/kk;
		if(tmp*kk < delta) ++tmp;
		NT += tmp;
		rem = max(0, rem-tmp*kk);
	}
	cout<<NT<<"\n";
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	init();
	return 0;
}
