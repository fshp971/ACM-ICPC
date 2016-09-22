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

const int maxn = 3000;

int n, m;

struct Tree
{
	struct TreeArray
	{
		LL node[maxn+5][maxn+5];
		void add(int x, int y, LL msk)
		{
			for(int i=x; i<=n; i+=i&(-i))
				for(int k=y; k<=n; k+=k&(-k)) node[i][k] ^= msk;
		}
		LL sum(int x, int y)
		{
			LL res = 0;
			for(int i=x; i; i-=i&(-i))
				for(int k=y; k; k-=k&(-k)) res ^= node[i][k];
			return res;
		}
	}T1, T2, T3, T4;

	void _update(int x, int y, LL msk)
	{
		T1.add(x, y, msk);
		if(x&1) T2.add(x, y, msk);
		if(y&1) T3.add(x, y, msk);
		if((x*y)&1) T4.add(x, y, msk);
	}

	void update(int x1, int y1, int x2, int y2, LL msk)
	{
		_update(x2+1, y2+1, msk);
		_update(x1, y2+1, msk);
		_update(x2+1, y1, msk);
		_update(x1, y1, msk);
	}

	LL _sum(int x, int y)
	{
		LL res = T4.sum(x, y);
		if((y+1)&1) res ^= T2.sum(x, y);
		if((x+1)&1) res ^= T3.sum(x, y);
		if( ((x+1)*(y+1)) & 1) res ^= T1.sum(x, y);
		return res;
	}

	LL sum(int x1, int y1, int x2, int y2)
	{
		return _sum(x2,y2) ^ _sum(x1-1,y2) ^ _sum(x2,y1-1) ^ _sum(x1-1,y1-1);
	}
}tree;

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int x1, y1, x2, y2, kk, a, b;
	char ord[3];
	sf("%d%d", &n, &m);
	REP(t,1,m)
	{
		sf("%s%d%d%d%d", ord, &x1, &y1, &x2, &y2);
		if(ord[0] == 'P')
		{
			sf("%d", &kk);
			LL msk = 0;
			REP(i,1,kk)
			{
				sf("%d%d", &a, &b);
				if(b&1) msk ^= (LL)1<<(a-1);
			}
			tree.update(x1, y1, x2, y2, msk);
		}
		else
		{
			LL msk = tree.sum(x1, y1, x2, y2);
			for(int i=0; i<50; ++i)
			{
				pf("%d ", (int)(msk&1) + 1);
				msk >>= 1;
			}
			pf("\n");
		}
	}
	return 0;
}
