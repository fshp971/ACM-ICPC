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

const int maxn = 15;

int n, m;
char type[maxn+2][maxn+2];
char mmp[maxn+2][maxn+2];

queue< pii > que;
short dist[maxn+2][maxn+2][1<<maxn];
char inq[maxn+2][maxn+2][1<<maxn];
short walk[4][2] = { {0, 1}, {0, -1}, {1, 0}, {-1, 0} };

inline void update(int x, int y, int msk, int ene)
{
	if(dist[x][y][msk] < ene)
	{
		dist[x][y][msk] = ene;
		if(!inq[x][y][msk])
		{
			que.push( MP(x*100+y, msk) );
			inq[x][y][msk] = 1;
		}
	}
}

int bfs(pii now, int power, int bag)
{
	if((now.second&power) == 0) return 1;
	while(!que.empty()) que.pop();
	FOR(i,0,n) FOR(k,0,m) REP(j,0,now.second)
		dist[i][k][j] = inq[i][k][j] = 0;
	que.push(now);
	dist[now.first/100][now.first%100][now.second] = bag;
	inq[now.first/100][now.first%100][now.second] = 1;
	int x, y, nx, my, msk, ene;
	while(!que.empty())
	{
		now = que.front(); que.pop();
		nx = now.first/100, my = now.first%100;
		inq[nx][my][now.second] = 0;
		if(!dist[nx][my][now.second]) continue;
		for(int t=0; t<4; ++t)
		{
			x = nx + walk[t][0];
			y = my + walk[t][1];
			if(x<0 || x>=n || y<0 || y>=m) continue;
			msk = now.second;
			ene = dist[nx][my][now.second] - 1;
			if(mmp[x][y] == 'D') continue;
			if(mmp[x][y] == 'Y')
			{
				if(msk & (1<<type[x][y])) msk -= 1<<type[x][y];
				if((msk&power) == 0) return 1;
				update(x, y, msk, ene);
			}
			if(mmp[x][y] == 'G')
			{
				update(x, y, msk, ene);
				if(msk & (1<<type[x][y]))
				{
					msk -= 1<<type[x][y];
					update(x, y, msk, bag);
				}
			}
			else update(x, y, msk, ene);
		}
	}
	return 0;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int msk, poi, top, power;
	int ans, l, r;
	while(sf("%d%d", &n, &m), n)
	{
		top = power = msk = 0;
		mem(type, -1);
		FOR(i,0,n)
		{
			sf("%s", mmp[i]);
			FOR(k,0,m)
			{
				if(mmp[i][k] == 'G' || mmp[i][k] == 'Y')
				{
					type[i][k] = top;
					msk += 1<<top;
					if(mmp[i][k] == 'Y')
						power += 1<<top;
					++top;
				}
				else if(mmp[i][k] == 'F')
					poi = i*100 + k;
			}
		}
		ans = -1, l = 0, r = n*m;
		while(l <= r)
		{
			int mid = (l+r) >> 1;
			if( bfs(MP(poi,msk), power, mid) )
				ans = mid, r = mid-1;
			else l = mid+1;
		}
		pf("%d\n", ans);
	}
	return 0;
}
