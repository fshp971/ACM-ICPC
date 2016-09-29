#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<iostream>
#include<algorithm>
#include<string>
#include<queue>
#include<utility>
#include<map>
#include<set>
#include<bitset>

using namespace std;

#define LL long long
#define mem(a,b) memset(a,b,sizeof(a))
#define MP make_pair
#define pii pair<int, int>
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define sf scanf
#define pf printf

const int maxn = 1e5;
const int step = 20;

int n, depth[maxn+5], two[25];
int h[maxn+5], e[maxn*2+5], nex[maxn*2+5];
int dest[maxn+5][step+5];
string name[maxn+5];

map<string, pii> surname;

void build(int x, int pre, int dep)
{
	depth[x] = dep;
	mem(dest[x], 0);
	dest[x][0] = pre;
	for(int i=1; dest[x][i-1] && dest[dest[x][i-1]][i-1]; ++i)
		dest[x][i] = dest[dest[x][i-1]][i-1];
	for(int i=h[x]; i; i=nex[i])
		if(e[i] != pre)
			build(e[i], x, dep+1);
}

int cal_dist(int u, int v)
{
	int res = 0;
	if(depth[u] < depth[v]) swap(u, v);
	for(int i=step; i>=0; --i)
	{
		if(!dest[u][i]) continue;
		if(depth[dest[u][i]] < depth[v]) continue;
		res += two[i];
		u = dest[u][i];
	}
	for(int i=step; i>=0; --i)
	{
		if(!dest[u][i] || dest[u][i] == dest[v][i]) continue;
		res += two[i]*2;
		u = dest[u][i], v = dest[v][i];
	}
	if(u != v)
	{
		res += two[0]*2;
		u = dest[u][0], v = dest[v][0];
	}
	return res+1;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	two[0] = 1;
	for(int i=1; i<=step; ++i) two[i] = two[i-1] * 2;
	int que, top, u, v;
	char temp[10];
	string temp1, temp2;
	while(~sf("%d%d", &n, &que))
	{
		REP(i,1,n)
		{
			sf("%s", temp);
			name[i] = string(temp);
		}
		top = 0, mem(h, 0);
		FOR(i,1,n)
		{
			sf("%d%d", &u, &v);
			e[++top] = v, nex[top] = h[u], h[u] = top;
			e[++top] = u, nex[top] = h[v], h[v] = top;
		}
		build(1, 0, 0);
		surname.clear();
		for(int i=1; i<=n; ++i)
		{
			if(!surname.count(name[i]))
				surname[name[i]] = MP(i, 0);
			else
			{
				pii &tmp = surname[name[i]];
				if(!tmp.second) tmp.second = i;
				else
				{
					int dis1 = cal_dist(tmp.first, tmp.second);
					int dis2 = cal_dist(tmp.first, i);
					int dis3 = cal_dist(tmp.second, i);
					if(dis3>dis2 && dis3>dis1)
						tmp.first = i;
					else if(dis2>dis1)
						tmp.second = i;
				}
			}
		}
		REP(i,1,que)
		{
			sf("%s", temp), temp1 = string(temp);
			sf("%s", temp), temp2 = string(temp);
			if(!surname.count(temp1) || !surname.count(temp2))
			{
				pf("-1\n");
				continue;
			}
			pii &tmp1 = surname[temp1];
			pii &tmp2 = surname[temp2];
			int ans = cal_dist(tmp1.first, tmp2.first);
			if(tmp2.second) ans = max(ans, cal_dist(tmp1.first, tmp2.second));
			if(tmp1.second) ans = max(ans, cal_dist(tmp1.second, tmp2.first));
			if(tmp1.second && tmp2.second)
				ans = max(ans, cal_dist(tmp1.second, tmp2.second));
			pf("%d\n", ans);
		}
	}
	return 0;
}
