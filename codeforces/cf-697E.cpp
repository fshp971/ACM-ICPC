#include<bits/stdc++.h>

using namespace std;

#define LL long long
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define pii pair<int,int>
#define mem(a,b) memset(a,b,sizeof(a))
#define MP(a,b) make_pair(a,b)
#define sf scanf
#define pf printf

const int md = 1e9 + 7;

LL pow_mod(LL x, LL t)
{
	LL res = 1, tmp = x;
	while(t)
	{
		if(t&1) res = (res*tmp) % md;
		tmp = (tmp*tmp) % md;
		t >>= 1;
	}
	return res;
}

void init()
{
	LL n;
	cin >> n;
	LL res1 = 1, res2 = 2, ta;
	bool fg = true;
	for(int i=1;i<=n;++i)
	{
		cin >> ta;
		if(ta%2 == 0)
			fg = false;
		res2 = pow_mod(res2, ta);
		//cout << "res2 = " << res2 << endl;
	}
	res2 = res2 * pow_mod(2, md-2) % md;
	if(fg)
		res1 = (res2-1+md) % md;
	else
		res1 = (res2+1) % md;
	res1 = res1 * pow_mod(3, md-2) % md;
	cout << res1 << "/" << res2 << "\n";
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	init();
	return 0;
}
