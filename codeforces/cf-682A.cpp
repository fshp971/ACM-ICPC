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

const int maxn = 1000000;

void cal(int n, int *res)
{
	mem(res,0);
	int a = n / 10, b = n%10;
	REP(i,0,9) res[i] = a;
	REP(i,1,b) ++res[i];
	return;
}

void init()
{
	int n, m;
	int f1[15], f2[15];
	cin >> n >> m;
	cal(n, f1);
	cal(m, f2);
	LL ans = 0;
	REP(i,0,9) REP(k,0,9) if((i+k)%5 == 0)
	{
		ans += (LL)f1[i] * f2[k];
	}
	cout << ans << "\n";
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	init();
	return 0;
}
