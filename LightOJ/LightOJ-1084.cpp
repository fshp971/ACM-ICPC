#include<bits/stdc++.h>

using namespace std;

#define LL long long
#define MP(a,b) make_pair(a,b)
#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define pii pair<int,int>
#define sf scanf
#define pf printf

const int maxn = 1e5;

int n, kk, poi[maxn+5];
int f[maxn+5];

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int T, head;
	sf("%d", &T);
	for(int t=1; t<=T; ++t)
	{
		sf("%d%d", &n, &kk);
		kk *= 2;
		REP(i,1,n) sf("%d", poi+i);
		sort(poi+1, poi+1+n);
		mem(f, 0x7f);
		f[0] = 0, head = 1;
		for(int i=1; i<=n; ++i)
		{
			while(head <= i-2)
			{
				if(poi[i]-poi[head] <= kk)
				{
					if(f[i] > f[head-1]+1)
					{
						f[i] = f[head-1]+1;
						break;
					}
				}
				++head;
			}
		}
		pf("Case %d: ", t);
		if(f[n] < maxn) pf("%d\n", f[n]);
		else pf("-1\n");
	}
	return 0;
}
