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

const int maxn = 1000, maxq = 1e5;

struct Node
{
	int n, m, res;
	int mmp[1010][1010], sum[1010], type[1010];
	
	void clear()
	{
		n = m = res = 0;
		mem(mmp, 0); mem(sum, 0); mem(type, 0);
	}

	bool empty(int i, int j){ return mmp[i][j] == type[i]; }

	void op1(int i, int j)
	{
		if(mmp[i][j] == type[i])
			mmp[i][j] = type[i]^1, ++sum[i], ++res;
	}
	
	void op2(int i, int j)
	{
		if(mmp[i][j] != type[i])
			mmp[i][j] = type[i], --sum[i], --res;
	}

	void op3(int i)
	{
		res = res - sum[i] + (m-sum[i]);
		type[i] ^= 1;
		sum[i] = m-sum[i];
	}
}tour;

struct Order
{
	int ord, ii, jj;
}inst[maxq+2];

int que;
int h[maxq+2], e[maxq+2], dat[maxq+2], nex[maxq+2];
int poi[maxq+2];
int anss[maxq+2];
vector<int> G[maxq+2];

void dfs(int now)
{
	for(int i=0; i<G[now].size(); ++i)
		anss[G[now][i]] = tour.res;
	for(int i=h[now]; i!=-1; i=nex[i])
	{
		char fg = 1;
		Order &ins = inst[dat[i]];
		if(ins.ord == 1)
		{
			if(!tour.empty(ins.ii, ins.jj)) fg = 0;
			else tour.op1(ins.ii, ins.jj);
		}
		else if(ins.ord == 2)
		{
			if(tour.empty(ins.ii, ins.jj)) fg = 0;
			else tour.op2(ins.ii, ins.jj);
		}
		else tour.op3(ins.ii);
		dfs(e[i]);
		if(ins.ord == 1)
		{
			if(fg) tour.op2(ins.ii, ins.jj);
		}
		else if(ins.ord == 2)
		{
			if(fg) tour.op1(ins.ii, ins.jj);
		}
		else tour.op3(ins.ii);
	}
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	tour.clear();
	sf("%d%d%d", &tour.n, &tour.m, &que);
	REP(i,0,maxq) h[i] = -1;
	int top = 0, next = 0;
	int now = 0, a;
	REP(i,1,que)
	{
		sf("%d", &inst[i].ord);
		if(inst[i].ord <= 3)
		{
			if(inst[i].ord == 3) sf("%d", &inst[i].ii);
			else sf("%d%d", &inst[i].ii, &inst[i].jj);
			e[++top] = (++next), dat[top] = i, nex[top] = h[now], h[now] = top;
			now = next;
			G[now].push_back(i);
			poi[i] = now;
		}
		else
		{
			sf("%d", &a);
			now = poi[a];
			G[now].push_back(i);
			poi[i] = now;
		}
	}
	mem(anss, 0);
	dfs(0);
	for(int i=1; i<=que; ++i) pf("%d\n", anss[i]);
	return 0;
}
