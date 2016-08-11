#include<bits/stdc++.h>

using namespace std;

#define LL long long
#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define MP(a,b) make_pair(a,b)
#define pii pair<int,int>
#define sf scanf
#define pf printf

const int maxn = 20000;

int vis[maxn+5];
int prime[maxn+5], tot;

void init()
{
	mem(vis, 0);
	prime[tot=1] = 2;
	for(int i=3; i <= maxn; i+=2)
	{
		if(!vis[i])
		{
			prime[++tot] = i;
			for(int k=i+i; k<=maxn; k+=i)
				vis[k] = true;
		}
	}
	return;
}

int check_prime(LL x)
{
	for(int i=1; i<=tot && prime[i]<x; ++i)
	{
		if(x%prime[i] == 0)
			return 0;
	}
	return 1;
}

int check_div(int x)
{
	int t1, t2;
	for(int i=0; 2*i*i<=x; ++i)
	{
		t1 = x-2*i*i;
		t2 = sqrt(t1);
		if(t2 * t2 == t1) return 1;
	}
	return 0;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	init();
	int T, a, b, fg;
	sf("%d", &T);
	while(T--)
	{
		sf("%d%d", &a, &b);
		if(a)
			fg = check_prime( (LL)a*a + (LL)2*b*b );
		else
			fg = !check_div(b);
		pf(fg ? "Yes\n" : "No\n");
	}
	return 0;
}
