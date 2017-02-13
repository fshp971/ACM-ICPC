#include<bits/stdc++.h>

using namespace std;

#define LL long long
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define mem(a,b) memset(a,b,sizeof(a))
#define pii pair<int,int>
#define MP make_pair
#define sf scanf
#define pf printf

const int maxn = 1e6;
const int md = 1000000009;

int n;
LL two[maxn+5], f[maxn+5], ans;

int main()
{
	two[0] = 1;
	REP(i,1,maxn) two[i] = two[i-1]*2 % md;
	sf("%d", &n);
	f[n] = 2;
	for(int i=n-1; i>=2; --i)
	{
		if(i&1)
			f[i] = (f[i+1]+2) % md;
		else
		{
			int k = i>>1;
			f[i] = ( 2 + ((two[k-1]-1+md)%md*4 + 1)*f[i+1] ) % md;
		}
	}
	f[1] = (1 + f[2]*f[2]) % md;
	ans = f[1]*2 % md;
	pf("%lld\n", ans);
	return 0;
}
