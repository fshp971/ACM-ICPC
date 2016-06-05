#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<queue>
#include<string>
#include<vector>
#include<utility>
#include<map>
#include<set>

using namespace std;

#define LL long long
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define pii pair<int,int>
#define mem(a,b) memset(a,b,sizeof(a))
#define MP(a,b) make_pair(a,b)
#define sf scanf
#define pf printf

const int maxn = 300;
const int INF = 1<<30;

int n,m,pp;
int mmp[maxn+10][maxn+10];

vector< pair< int, pii > > color[maxn*maxn+10];

int dist(pii a, pii b)
{
	return abs(a.first-b.first) + abs(a.second-b.second);
}

queue< pii > que;
int dis[maxn+10][maxn+10];
bool inq[maxn+10][maxn+10];
int walk[4][2] = {{0,1}, {0,-1}, {1,0}, {-1,0}};

void bfs(int col)
{
	while(!que.empty()) que.pop();
	mem(dis,0x7f); mem(inq,0);
	FOR(i,0,color[col-1].size())
	{
		pii &tmp = color[col-1][i].second;
		dis[tmp.first][tmp.second] = color[col-1][i].first;
		inq[tmp.first][tmp.second] = true;
		que.push(tmp);
	}
	while(!que.empty())
	{
		pii tmp = que.front();
		inq[tmp.first][tmp.second] = false; que.pop();
		FOR(i,0,4)
		{
			int xx = tmp.first + walk[i][0];
			int yy = tmp.second + walk[i][1];
			if(xx<1 || xx>n || yy<1 || yy>m) continue;
			int dd = dis[tmp.first][tmp.second]+dist(tmp, MP(xx,yy)); 
			if(dd < dis[xx][yy])
			{
				dis[xx][yy] = dd;
				if(!inq[xx][yy])
				{
					que.push( MP(xx,yy) );
					inq[xx][yy] = true;
				}
			}
		}
	}
	FOR(i,0,color[col].size())
	{
		pii &tmp = color[col][i].second;
		color[col][i].first = dis[tmp.first][tmp.second];
	}
	return;
}

void init()
{
	cin >> n >> m >> pp;
	REP(i,1,n) REP(k,1,m)
	{
		scanf("%d",&mmp[i][k]);
		//if(i==1 && k==1) color[mmp[i][k]].push_back( MP(0, MP(i,k)) );
		//else color[mmp[i][k]].push_back( MP(INF, MP(i,k)) );
		color[mmp[i][k]].push_back( MP(INF, MP(i,k)) );
	}
	color[0].push_back( MP(0, MP(1,1)) );
	REP(i,1,pp)
	{
		if(color[i].size() * color[i-1].size() <= n*m)
		{
			FOR(k,0,color[i].size()) FOR(j,0,color[i-1].size())
				color[i][k].first = min(color[i][k].first,
									 color[i-1][j].first + dist(color[i][k].second, color[i-1][j].second));
		}
		//else if(true) continue;
		else bfs(i);
	}
	cout << color[pp][0].first << "\n";
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	init();
	return 0;
}
