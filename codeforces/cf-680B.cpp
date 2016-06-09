#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
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
#define MP(a,b) make_pair(a,b)
#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define pii pair<int,int>
#define sf scanf
#define pf printf

int aa, n, tt[110];

int cal(int x)
{
	if(x<1 || x>n) return -1;
	return tt[x];
}

void init()
{
	cin >> n >> aa;
	REP(i,1,n) scanf("%d", tt+i);
	int ans = tt[aa];
	REP(i,1,n)
	{
		int tp1 = cal(aa-i);
		int tp2 = cal(aa+i);
		if(tp1 == -1 && tp2 == -1) break;
		if(tp1 == -1 || tp2 == -1) ans += max(tp1, tp2);
		else if(tp1 == 1 && tp2 == 1) ans += 2;
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
