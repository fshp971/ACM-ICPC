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

const int md = 1e9 + 7;

LL pow_mod(LL x, LL n)
{
	LL tmp = x, ans = 1;
	while(n > 0)
	{
		if(n & (LL)1) ans = ans * tmp % md;
		tmp = tmp * tmp % md;
		n >>= 1;
	}
	return ans;
}

void init()
{
	LL A, B, n, x;
	cin >> A >> B >> n >> x;
	LL An = pow_mod(A, n);
	LL ans;
	if(A == 1)
	{
		ans = An*x%md + n%md * B % md;
		ans %= md;
		//pf("done\n");
	}
	else
	{
		LL inv = pow_mod(A-1, md-2);
		ans = An*x%md;
		LL tmp = (An-1)*inv%md;
		ans = (ans + B*tmp%md) % md;
	}
	cout << ans << "\n";
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	init();
	return 0;
}
