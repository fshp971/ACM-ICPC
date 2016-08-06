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

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int T;
	int xx, kk, p, q, t;
	sf("%d", &T);
	while(T--)
	{
		sf("%d%d", &xx, &kk);
		t = xx/kk;
		//pf("t = %d\n", t);
		if(!t)
		{
			p = 0;
			q = xx;
		}
		else if(t*xx == kk)
		{
			p = 0;
			q = xx/t;
		}
		else
		{
			q = xx - (xx/t) * t;
			p = (xx/t) - q;
		}
		pf("%d %d\n", p, q);
	}
	return 0;
}
