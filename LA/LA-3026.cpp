#include<bits/stdc++.h>

using namespace std;

#define LL long long
#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define MP(a,b) make_pair(a,b)
#define pii pair<int,int>
#define sf scanf
#define pf printf

const int maxn = 1000000;

int n, pp[maxn+5];
char arr[maxn+5];

void init()
{
	sf("%s", arr);
	mem(pp, 0);
	int now = 0;
	for(int i=1;i<n;++i)
	{
		while(now && arr[now] != arr[i]) now = pp[now];
		pp[i+1] = arr[now] == arr[i] ? (++now) : now;
		if(pp[i+1])
		{
			int t = (i+1) - pp[i+1];
			//pf("pp[%d] = %d, t = %d\n", i+1, pp[i+1], t);
			if((i+1)%t == 0)
				pf("%d %d\n", i+1, (i+1)/t);
		}
	}
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int t = 0;
	while(sf("%d", &n), n)
	{
		pf("Test case #%d\n", ++t);
		init();
		pf("\n");
	}
	return 0;
}
