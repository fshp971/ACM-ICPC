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

const int maxnode = 20e5;

struct Tire
{
	int top, cont[maxnode+5], nex[maxnode+5][2];

	void clear()
	{
		top = 0;
		mem(nex, 0);
	}

	void insert(LL x)
	{
		if(!x)
		{
			if(!nex[0][0]) nex[0][0] = ++top;
			++cont[top];
			return;
		}
		int poi = 0;
		while(x)
		{
			LL t = x&1;
			if(!nex[poi][t])
			{
				nex[poi][t] = ++top;
				cont[top] = 0;
			}
			poi = nex[poi][t];
			x /= 10;
		}
		++cont[poi];
	}

	void remove(LL x)
	{
		if(!x)
		{
			--cont[nex[0][0]];
			return;
		}
		LL poi = 0;
		while(x)
		{
			poi = nex[poi][x&1];
			x /= 10;
		}
		--cont[poi];
	}

	int calc(char *aa)
	{
		int len = strlen(aa);
		int ans = 0, poi = 0, i = len-1;
		for(; i>=0; --i)
		{
			poi = nex[poi][aa[i]-48];
			if(!poi) break;
			if(aa[i] != '0') ans = 0;
			ans += cont[poi];
		}
		if(i >= 0)
		{
			for(; i>=0; --i)
				if(aa[i] != '0')
				{
					ans = 0;
					break;
				}
		}
		else
		{
			while(poi = nex[poi][0])
				ans += cont[poi];
		}
		return ans;
	}
}tree;

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int n;
	LL a;
	char ord[3], partten[20];
	sf("%d", &n);
	tree.clear();
	REP(i,1,n)
	{
		sf("%s", ord);
		if(ord[0] == '+')
		{
			sf("%lld", &a);
			tree.insert(a);
		}
		else if(ord[0] == '-')
		{
			sf("%lld", &a);
			tree.remove(a);
		}
		else
		{
			sf("%s", partten);
			pf("%d\n", tree.calc(partten));
		}
	}
	return 0;
}
