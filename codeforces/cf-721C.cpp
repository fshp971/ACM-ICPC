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

const int maxn = 5000;

int n, m, lim;
int h[maxn+5], e[maxn+5], cost[maxn+5], nex[maxn+5];
int dis[maxn+3][maxn+3];
char inq[maxn+3][maxn+3];
int pre[maxn+3][maxn+3];
int sta[maxn+3];

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int u, v, w;
	sf("%d%d%d", &n, &m, &lim);
	REP(i,1,m)
	{
		sf("%d%d%d", &u, &v, &w);
		e[i] = v, cost[i] = w, nex[i] = h[u], h[u] = i;
	}
	pii tmp, tmp2;
	int dist;
	queue<pii> que;
	mem(dis, 0x7f);
	dis[1][1] = 0, inq[1][1] = 1, pre[1][1] = 0;
	que.push( MP(1,1) );
	while(!que.empty())
	{
		tmp = que.front(); que.pop();
		inq[tmp.first][tmp.second] = 0;
		int &x = tmp.first;
		for(int i=h[x]; i; i=nex[i])
		{
			tmp2.first = e[i];
			tmp2.second = tmp.second+1;
			dist = dis[x][tmp.second] + cost[i];
			if(dist > lim) continue;
			if(dist < dis[tmp2.first][tmp2.second])
			{
				dis[tmp2.first][tmp2.second] = dist;
				pre[tmp2.first][tmp2.second] = x;
				if(!inq[tmp2.first][tmp2.second])
				{
					inq[tmp2.first][tmp2.second] = 1;
					que.push(tmp2);
				}
			}
		}
	}
	int ans, now;
	for(int i=n; i>=2; --i)
		if(dis[n][i] <= lim)
		{
			pf("%d\n", ans=i);
			break;
		}
	now = n;
	while(now)
	{
		sta[++sta[0]] = now;
		now = pre[now][ans--];
	}
	for(int i=sta[0]; i>=1; --i)
	{
		if(i<sta[0]) pf(" ");
		pf("%d", sta[i]);
	}
	pf("\n");
	return 0;
}
