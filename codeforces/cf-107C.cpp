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

const int maxn = 16;

int n, m;
LL T;
int cnt[maxn+5];

int used[maxn+5], ans[maxn+5];
LL f[2][1<<18];

LL run()
{
	int poi = 0;
	mem(f[poi],0);
	f[poi][0] = 1;
	for(int i=0; i<n; ++i)
	{
		mem(f[poi^1],0);
		for(int k=(1<<n)-1; k>=0; --k)
		{
			if(!f[poi][k]) continue;
			if(used[i] != -1)
			{
				if( (k&(1<<used[i])) == 0 )
					f[poi^1][k+(1<<used[i])] += f[poi][k];
				continue;
			}
			for(int j=0; j<n; ++j)
			{
				if( (k&(1<<j)) || (k&cnt[j]) ) continue;
				f[poi^1][k+(1<<j)] += f[poi][k];
			}
		}
		poi ^= 1;
	}
	return f[poi][(1<<n)-1];
}

int main()
{
	sf("%d%lld%d", &n, &T, &m);
	T -= 2000;
	int a, b, tot = 0;
	REP(i,1,m)
	{
		sf("%d%d", &a, &b);
		--a, --b;
		cnt[a] |= 1<<b;
	}
	mem(used,-1), mem(ans,-1);
	if(run() < T)
	{
		pf("The times have changed\n");
		return 0;
	}
	int now = 0;
	for(int i=0; i<n; ++i)
	{
		now = now*2 + 1;
		for(int k=0; k<n; ++k)
		{
			if(used[k] != -1) continue;
			used[k] = i, ans[i] = k;
			LL tmp = run();
			if(tmp >= T) break;
			T -= tmp;
			used[k] = ans[i] = -1;
		}
	}
	for(int i=0; i<n; ++i)
	{
		if(i) pf(" ");
		pf("%d", ans[i]+1);
	}
	pf("\n");
	return 0;
}
