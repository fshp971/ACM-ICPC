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

const int maxn = 100000;

int n;
char arr[maxn+5];

void init()
{
	sf("%d %s", &n, arr);
	int res = 0, tot = 0;
	int level = 0, ok = 0;
	bool fg = false;
	char pre = '3';
	FOR(i,0,n)
	{
		if(arr[i] != pre)
		{
			++res, tot = 1;
			pre = arr[i];
			fg = true;
			//pf("pre = %c, i = %d\n", pre, i);
		}
		else
		{
			++tot;
			if(tot >= 3)
				++ok;
			if(fg && tot >= 2)
			{
				fg = false;
				++level;
			}
		}
	}
	if(ok)
		res += 2;
	else if(level)
		res += min(level, 2);
	else if(n>=2)
	{
		if(arr[0] == arr[1] || arr[n-1] == arr[n-2])
			++res;
	}
	cout << res << "\n";
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	init();
	return 0;
}
