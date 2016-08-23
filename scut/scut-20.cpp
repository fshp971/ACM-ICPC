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

int n, m, kk;
LL dis[20][20];
LL f[1<<16][16];
char inq[1<<16][16];

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	queue< pii > que;
	int T, a, b, c, sta1[20], sta2[20];
	LL xx[20], yy[20], tmp;
	sf("%d", &T);
	while(T--)
	{
		sf("%d%d%d", &n, &m, &kk);
		FOR(i,0,n) sf("%lld%lld", xx+i, yy+i);
		FOR(i,0,n) FOR(k,i,n)
			dis[i][k] = dis[k][i] = (xx[i]-xx[k])*(xx[i]-xx[k]) + (yy[i]-yy[k])*(yy[i]-yy[k]);
		REP(i,1,m)
		{
			sf("%d%d%d", &a, &b, &c);
			sta1[0] = sta2[0] = 0;
			FOR(k,0,n)
			{
				tmp = xx[k]*a + yy[k]*b + c;
				if(tmp > 0) sta1[++sta1[0]] = k;
				else if(tmp < 0) sta2[++sta2[0]] = k;
			}
			REP(k,1,sta1[0]) REP(j,1,sta2[0])
				dis[sta1[k]][sta2[j]] += kk, dis[sta2[j]][sta1[k]] += kk;
		}
		mem(f, 0x7f); mem(inq, 0);
		que.push( MP(1, 0) );
		f[1][0] = 0, inq[1][0] = 1;
		while(!que.empty())
		{
			pii now = que.front();
			int &msk = now.first, &poi = now.second;
			que.pop(); inq[msk][poi] = 0;
			FOR(i,0,n)
			{
				if(msk & (1<<i)) continue;
				a = msk + (1<<i);
				tmp = f[msk][poi] + dis[poi][i];
				if(tmp < f[a][i])
				{
					f[a][i] = tmp;
					if(!inq[a][i])
					{
						inq[a][i] = 1;
						que.push( MP(a, i) );
					}
				}
			}
		}
		tmp = (LL)1 << 60;
		FOR(i,0,n) tmp = min(tmp, f[(1<<n)-1][i]+dis[i][0]);
		pf("%lld\n", tmp);
	}
	return 0;
}
