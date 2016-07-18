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

const int maxn = 400;

int n, m, dis[maxn+5];
bool inq[maxn+5];
bool G[maxn+5][maxn+5];

void init()
{
	cin >> n >> m;
	mem(G, 0); mem(dis, 0x7f); mem(inq, 0);
	int a, b;
	REP(i,1,m)
	{
		sf("%d%d", &a, &b);
		G[a][b] = G[b][a] = true;
	}
	bool fg = G[1][n] ^ 1;
	//pf("fg = %d\n", fg);
	queue<int> que;
	que.push(1);
	inq[1] = true; dis[1] = 0;
	while(!que.empty())
	{
		int x = que.front(); que.pop();
		inq[x] = false;
		REP(i,1,n) if(G[x][i] == fg)
		{
			if(dis[x]+1 < dis[i])
			{
				dis[i] = dis[x]+1;
				if(!inq[i])
				{
					inq[i] = true;
					que.push(i);
				}
			}
		}
	}
	pf("%d\n", dis[n]>1000000 ? -1 : dis[n]);
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	init();
	return 0;
}
