#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<queue>
#include<string>
#include<utility>
#include<map>
#include<set>
#include<vector>

using namespace std;

#define LL long long
#define MP(a,b) make_pair(a,b)
#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define pii pair<int,int>

int n,m;
int walk[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};
int mmp[1010][1010];
int sx,sy,tx,ty;

bool vis[1010][1010][4];
bool dir[4];

int mk_dir(int x, int type)
{
	return ((x << type) & 15) | (x >> (4-type));
}

void run()
{
	//dat: first = dis, second = type;
	pii poi, dat, poi2, dat2;
	queue< pair<pii, pii> > que;
	mem(vis,0);
	poi.first = sx; poi.second = sy;
	dat.first = 0; dat.second = 0;
	que.push(MP(poi,dat));
	vis[poi.first][poi.second][dat.second] = true;
	while(!que.empty())
	{
		pair<pii, pii> tmp = que.front(); que.pop();
		poi = tmp.first; dat = tmp.second;
		if(poi.first==tx && poi.second==ty)
		{
			printf("%d\n",dat.first);
			return;
		}
		dat2.first = dat.first+1; dat2.second = (dat.second+1)%4;
		if(!vis[poi.first][poi.second][dat2.second])
		{
			vis[poi.first][poi.second][dat2.second] = true;
			que.push(MP(poi,dat2));
		}
		int dt = mk_dir(mmp[poi.first][poi.second], dat.second);
		FOR(i,0,4)
		{
			if(!(dt & (1<<i))) continue;
			int xx = poi.first + walk[i][0];
			int yy = poi.second + walk[i][1];
			if(xx<1 || xx>n || yy<1 || yy>m) continue;
			if(vis[xx][yy][dat.second]) continue;
			int ft = mk_dir(mmp[xx][yy], dat.second);
			if(ft & (1 << (i ^ 2)))
			{
				vis[xx][yy][dat.second] = true;
				que.push( MP( MP(xx,yy), MP(dat.first+1,dat.second) ) );
			}
		}
	}
	printf("-1\n");
	return;
}

void init()
{
	cin>>n>>m;
	char a[1010];
	REP(i,1,n)
	{
		scanf("%s",a);
		REP(k,1,m)
		{
			if(a[k-1] == '+') mmp[i][k] = 15;
			else if(a[k-1] == '-') mmp[i][k] = 10;
			else if(a[k-1] == '|') mmp[i][k] = 5;
			else if(a[k-1] == '^') mmp[i][k] = 1;
			else if(a[k-1] == '>') mmp[i][k] = 2;
			else if(a[k-1] == '<') mmp[i][k] = 8;
			else if(a[k-1] == 'v') mmp[i][k] = 4;
			else if(a[k-1] == 'L') mmp[i][k] = 7;
			else if(a[k-1] == 'R') mmp[i][k] = 13;
			else if(a[k-1] == 'U') mmp[i][k] = 14;
			else if(a[k-1] == 'D') mmp[i][k] = 11;
			else if(a[k-1] == '*') mmp[i][k] = 0;
		}
	}
	cin>>sx>>sy>>tx>>ty;
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	init();
	run();
	return 0;
}
