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

int n;
int mmp[105][105];
char vis[105][105];

int walk[8][2] = { {1,0}, {-1,0}, {0,1}, {0,-1}, {1,1}, {1,-1}, {-1,-1}, {-1,1} };

void bfs(int xx, int yy)
{
	queue<int> que;
	int dat, tx, ty;
	que.push(xx*100 + yy);
	vis[xx][yy] = 1;
	while(!que.empty())
	{
		dat = que.front(); que.pop();
		xx = dat/100, yy = dat%100;
		for(int t=0; t<8; ++t)
		{
			tx = xx+walk[t][0];
			ty = yy+walk[t][1];
			if(tx<0 || tx>=n || ty<0 || ty>=n) continue;
			if(vis[tx][ty]) continue;
			if(mmp[tx][ty] == -1) continue;
			vis[tx][ty] = 1;
			if(!mmp[tx][ty])
				que.push(tx*100+ty);
		}
	}
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int ans;
	while(~sf("%d", &n))
	{
		FOR(i,0,n) FOR(k,0,n)
			sf("%d", &mmp[i][k]);
		mem(vis, 0);
		ans = 0;
		FOR(i,0,n) FOR(k,0,n)
			if(!mmp[i][k] && !vis[i][k])
			{
				++ans;
				bfs(i, k);
			}
		FOR(i,0,n) FOR(k,0,n)
			if(!vis[i][k] && mmp[i][k]!=-1) ++ans;
		pf("%d\n", ans);
	}
	return 0;
}
