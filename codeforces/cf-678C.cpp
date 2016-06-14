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

LL n, aa, bb, pp ,qq;

LL gcd(LL a, LL b){ return b ? gcd(b, a%b) : a; }

void init()
{
	cin >> n >> aa >> bb >> pp >> qq;
	LL ta = n/aa, tb = n/bb;
	LL tc = aa / gcd(aa,bb) * bb;
	tc = n/tc;
	LL ans;
	if(pp > qq)
		ans = ta * pp + (tb-tc) * qq;
	else
		ans = (ta-tc) * pp + tb * qq;
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
