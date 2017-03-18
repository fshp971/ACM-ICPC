#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define sf scanf
#define pf printf
typedef long long LL;
typedef pair<int,int> pii;

LL power[15];
int arr[10], col[10];

LL Calc(int len, int n)
{
	mem(col, 0);
	for(int i=1; i<=6; ++i)
	{
		if(arr[i]%len) return 0;
		col[i] = arr[i]/len;
	}
	LL ans = power[n/len];
	for(int i=1; i<=6; ++i)
		ans /= power[col[i]];
	return ans;
}

int main()
{
	power[0] = 1;
	REP(i,1,12) power[i] = power[i-1]*i;
	int T, a;
	LL ans;
	sf("%d", &T);
	while(T--)
	{
		mem(arr,0);
		REP(i,1,12) sf("%d", &a), ++arr[a];
		ans = Calc(1,12) + Calc(2,12)*3 + Calc(3,12)*8 + Calc(4,12)*6;
		for(int i=1; i<=6; ++i)
			for(int k=1; k<=6; ++k)
			{
				if(!arr[i] || !arr[k]) continue;
				--arr[i], --arr[k];
				ans += Calc(2,10)*6;
				++arr[i], ++arr[k];
			}
		ans /= 24;
		pf("%lld\n", ans);
	}
	return 0;
}
