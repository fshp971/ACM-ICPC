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

const int maxn = 5000;

int n, ss, ee, xx[maxn+5];
int aa[maxn+5], bb[maxn+5], cc[maxn+5], dd[maxn+5];

int vis[2][maxn+5];
LL f[2][maxn+5];

inline void update(LL &x, LL y, int &vs)
{
	x = vs ? min(x,y) : y;
	vs = 1;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	sf("%d%d%d", &n, &ss, &ee);
	REP(i,1,n) sf("%d", xx+i);
	REP(i,1,n) sf("%d", aa+i);
	REP(i,1,n) sf("%d", bb+i);
	REP(i,1,n) sf("%d", cc+i);
	REP(i,1,n) sf("%d", dd+i);
	int now = 0, nex;
	mem(vis[now], 0);
	vis[now][1] = 1;
	if(ss == 1)
		f[now][1] = dd[1]-xx[1];
	else if(ee == 1)
		f[now][1] = bb[1]-xx[1];
	else
		f[now][1] = bb[1]+dd[1]-(LL)2*xx[1];
	REP(i,1,n-1)
	{
		nex = (now+1)%2;
		mem(vis[nex], 0);
		for(int j=i; j; --j) if(vis[now][j])
		{
			if(ss<=i && ee<=i && j==1)
				continue;
			if(i+1 == ss)
			{
				update(f[nex][j], f[now][j]+cc[i+1]+xx[i+1], vis[nex][j]);
				update(f[nex][j+1], f[now][j]+dd[i+1]-xx[i+1], vis[nex][j+1]);
			}
			else if(i+1 == ee)
			{
				update(f[nex][j], f[now][j]+aa[i+1]+xx[i+1], vis[nex][j]);
				update(f[nex][j+1], f[now][j]+bb[i+1]-xx[i+1], vis[nex][j+1]);
			}
			else
			{
				if(j>=2 || ee>i)
					update(f[nex][j], f[now][j]+dd[i+1]+aa[i+1], vis[nex][j]);
				if(j>=2 || ss>i)
					update(f[nex][j], f[now][j]+cc[i+1]+bb[i+1], vis[nex][j]);
				update(f[nex][j+1], f[now][j]+dd[i+1]+bb[i+1]-(LL)2*xx[i+1], vis[nex][j+1]);
				if(j>=2)
					update(f[nex][j-1], f[now][j]+aa[i+1]+cc[i+1]+(LL)2*xx[i+1], vis[nex][j-1]);
			}
		}
		now = nex;
	}
	pf("%lld\n", f[now][1]);
	return 0;
}
