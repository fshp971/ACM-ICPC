#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<cctype>
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
#define mem(a,b) memset(a,b,sizeof(a))
#define MP(a,b) make_pair(a,b)
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define sf scanf
#define pf printf
#define pii pair<int,int>

const int maxn = 4000000;

LL phi[maxn+10], f[maxn+10];
LL res[maxn+10];
bool vis[maxn+10];

void phi_table()
{
	phi[1] = 0;
	mem(vis,0);
	REP(i,2,maxn)
	{
		if(!vis[i])
		{
			for(int k=i;k<=maxn;k+=i)
			{
				if(!vis[k])
				{
					vis[k] = true;
					phi[k] = k;
				}
				phi[k] = phi[k] / i * (i-1);
			}
		}
	}
	/*REP(i,1,30)
	{
		pf("phi[%d] = %lld\n",i,phi[i]);
	}*/
	return;
}

void run()
{
	mem(f,0);
	REP(i,1,maxn)
	{
		for(int k=2; k*i<=maxn; ++k)
		{
			f[k*i] += phi[k] * i;
		}
	}
	res[1] = f[1];
	REP(i,2,maxn)
		res[i] = res[i-1] + f[i];
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	phi_table();
	run();
	int n;
	while(cin>>n)
	{
		if(!n) break;
		cout<<res[n]<<"\n";
	}
	return 0;
}
