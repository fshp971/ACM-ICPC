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

const int maxn = 1e6;
int n, kk;
int sta[1010], top;
int dat[maxn+5];

void prime()
{
	sta[top=1] = 2;
	bool fg[1010];
	mem(fg, 0);
	for(int i=3; i<=1000; i+=2)
	{
		if(!fg[i])
		{
			sta[++top] = i;
			for(int k=i+i; k<=1000; k+=i)
				fg[k] = true;
		}
	}
	//pf("top = %d\n", top);
	//for(int i=1;i<=top;++i)
	//	pf("sta[%d] = %d\n", i, sta[i]);
	return;
}

void init()
{
	cin >> n >> kk;
	mem(dat, 0);
	int a;
	for(int i=1;i<=n;++i)
	{
		sf("%d", &a);
		for(int k=1; k<=top; ++k)
		{
			if(a < sta[k]) break;
			int tmp = 0;
			while(a % sta[k] == 0)
			{
				a /= sta[k];
				++tmp;
			}
			dat[sta[k]] = max(dat[sta[k]], tmp);
		}
		if(a > 1)
			dat[a] = 1;
	}
	/*for(int i=1;i<=maxn;++i)
	{
		if(dat[i])
		{
			pf("dat[%d] = %d\n", i, dat[i]);
		}
	}*/
	for(int i=1; i<=maxn; ++i)
	{
		if(kk < i) break;
		while(kk%i==0 && dat[i])
		{
			kk /= i; --dat[i];
		}
	}
	pf(kk==1 ? "Yes\n" : "No\n");
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	prime();
	init();
	return 0;
}
