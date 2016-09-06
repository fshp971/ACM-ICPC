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

LL f[25][60000];

int number[25];

int update(int msk, int x)
{
	if(!x && !msk) return 0;
	int num[10];
	for(int i=0; i<=9; ++i)
		num[i] = msk%3, msk /= 3;
	if(!num[x]) num[x] = 1;
	else num[x] = num[x]%2 + 1;
	msk = 0;
	for(int i=9; i>=0; --i)
		msk = msk*3 + num[i];
	return msk;
}

int check(int msk)
{
	int tmp;
	for(int i=0; i<=9; ++i)
	{
		tmp = msk%3, msk /= 3;
		if(tmp)
		{
			if(i&1)
			{
				if(tmp == 1) return 0;
			}
			else
			{
				if(tmp == 2) return 0;
			}
		}
	}
	return 1;
}

LL dfs(int poi, int msk, char flag, char fg2)
{
	if(!poi)
	{
		if(!msk) return 0;
		return check(msk);
	}
	if(flag && f[poi][msk] != -1) return f[poi][msk];
	int res = 0;
	int range = flag ? 9 : number[poi];
	for(int i=0; i<=range; ++i)
	{
		res += dfs( poi-1, update(msk, i), flag || i<number[poi], fg2 || i);
	}
	if(flag && fg2) f[poi][msk] = res;
	return res;
}

LL calc(LL x)
{
	if(!x) return 0;
	int top = 0;
	while(x) number[++top] = x%10, x /= 10;
	return dfs(top, 0, 0, 0);
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	mem(f, -1);
	int T;
	LL l, r;
	sf("%d", &T);
	while(T--)
	{
		sf("%lld%lld", &l, &r);
		pf("%lld\n", calc(r) - calc(l-1));
	}
	return 0;
}
