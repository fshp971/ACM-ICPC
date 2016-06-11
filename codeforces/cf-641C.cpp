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

const int maxn = 1000000;

int n, que;
int res[maxn+10];

void move(int &x, int mov)
{
	x = (x + mov + n) % n;
}

void init()
{
	int ord, mov;
	int poi1 = 0, poi2 = 0;
	cin >> n >> que;
	REP(i,1,que)
	{
		sf("%d", &ord);
		if(ord == 1)
		{
			sf("%d", &mov);
			move(poi1, mov);
			move(poi2, mov);
		}
		else
		{
			if(poi1%2)
			{
				move(poi1, -1);
				move(poi2, 1);
			}
			else
			{
				move(poi1, 1);
				move(poi2, -1);
			}
		}
	}
	REP(i,1,n)
	{
		if(i%2) res[(i-1+poi1)%n+1] = i;
		else res[(i-1+poi2)%n+1] = i;
	}
	REP(i,1,n)
	{
		if(i>1) pf(" ");
		pf("%d",res[i]);
	}
	pf("\n");
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	init();
	return 0;
}
