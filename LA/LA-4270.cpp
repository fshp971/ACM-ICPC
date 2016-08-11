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

set<LL> ans;
set<LL>::iterator it;

void ex_gcd(LL a, LL b, LL &g, LL &x, LL &y)
{
	if(!b) g = a, x = 1, y = 0;
	else{ ex_gcd(b, a%b, g, y, x); y -= (a/b)*x; }
}

void run(LL A, LL B, LL C)
{
	LL gg, x, y;
	ex_gcd(A, B, gg, x, y);
	if(C%gg) return;
	LL tb = B/gg;
	x *= C/gg;
	x -= x/tb * tb, tb *= A;
	for(LL r2 = x*A - C/2; r2 < A*B; r2 += tb)
		if(r2 >= 0) ans.insert(r2);
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int T = 0;
	LL x, N, r;
	while(sf("%lld%lld%lld", &x, &N, &r), N)
	{
		ans.clear();
		for(int i=1; (LL)i*i <= N; ++i)
		{
			if(N%i == 0)
			{
				run(i, N/i, 2*r);
				run(N/i, i, 2*r);
			}
		}
		pf("Case %d:", ++T);
		for(it = ans.begin(); it != ans.end(); ++it)
			pf(" %lld", *it);
		pf("\n");
	}
	return 0;
}
