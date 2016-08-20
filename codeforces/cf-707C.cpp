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

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	LL a, b, c;
	cin >> a;
	if(a <= 2)
	{
		pf("-1\n");
		return 0;
	}
	b = a*a;
	if(a%2)
	{
		c = (b+1) / 2;
		cout << c-1 << " " << c << "\n";
	}
	else
	{
		c = (b+4) / 4;
		cout << c-2 << " " << c << "\n";
	}
	return 0;
}
