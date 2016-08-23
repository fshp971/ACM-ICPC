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

const int md = 1e9 + 7;
const int maxn = 100010;

int n, pp, inv_pp;
LL pp0[maxn+2], inv_pp0[maxn+2];
int h[maxn+2], e[maxn*2+2], wi[maxn*2+2], nex[maxn*2+2];
char vis[maxn+2];

struct Node
{
	int dep;
	LL sum, inv_sum;
}tree[maxn+2];

LL mul_mod(LL a, LL b)
{
	if(a>=md) a %= md;
	if(b>=md) b %= md;
	a = a*b;
	if(a>=md) a %= md;
	return a;
}

LL pow_mod(LL a, LL b)
{
	LL res = 1, tmp = a;
	while(b)
	{
		if(b&1) res = mul_mod(res, tmp);
		b >>= 1, tmp = mul_mod(tmp, tmp);
	}
	return res;
}

void dfs(int x)
{
	vis[x] = 1;
	for(int i=h[x]; i; i=nex[i])
	{
		if(vis[e[i]]) continue;
		tree[e[i]].dep = tree[x].dep+1;
		tree[e[i]].sum = (tree[x].sum + mul_mod(wi[i], pp0[tree[x].dep])) % md;
		tree[e[i]].inv_sum = (tree[x].inv_sum + mul_mod(wi[i], inv_pp0[tree[x].dep])) % md;
		dfs(e[i]);
	}
}

struct Ques
{
	int des, type, id;
	Ques(): des(0), type(0), id(0){}
	Ques(int _des, int _type, int _id)
	{
		des = _des, type = _type, id = _id;
	}
};

int fat[maxn+2];
LL ans[maxn+2];
vector< Ques > G[maxn+2];

int find_fat(int x){ return fat[x] == x ? x : fat[x] = find_fat(fat[x]); }

LL calc(int u, int v, int lca)
{
	LL dis1, dis2;
	int dt = tree[u].dep - tree[lca].dep;
	dis2 = (tree[v].sum + md - tree[lca].sum) % md;
	dis2 = mul_mod(dis2, inv_pp0[tree[lca].dep]);
	dis2 = mul_mod(dis2, pp0[dt]);

	dis1 = (tree[u].inv_sum + md - tree[lca].inv_sum) % md;
	dis1 = mul_mod(dis1, pp0[tree[u].dep-1]);
	return (dis1 + dis2) % md;
}

void dfs2(int x)
{
	vis[x] = 1;
	for(int i=h[x]; i; i=nex[i])
	{
		if(vis[e[i]]) continue;
		dfs2(e[i]);
		fat[e[i]] = x;
	}
	int u, v, lca;
	for(int i=0; i<G[x].size(); ++i)
	{
		Ques &tmpQ = G[x][i];
		if(!vis[tmpQ.des]) continue;
		u = tmpQ.des, v = x;
		lca = find_fat(tmpQ.des);
		if(tmpQ.type == 1) swap(u, v);
		ans[tmpQ.id] = calc(u, v, lca);
	}
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int T;
	int u, v, w, top, qq;
	sf("%d", &T);
	for(int t=1; t<=T; ++t)
	{
		sf("%d%d", &n, &pp);
		inv_pp = pow_mod(pp, md-2);
		pp0[0] = 1, inv_pp0[0] = 1;
		REP(i,1,n)
		{
			pp0[i] = pp0[i-1]*pp % md;
			inv_pp0[i] = inv_pp0[i-1]*inv_pp % md;
		}
		top = 0;
		mem(h, 0);
		for(int i=1; i<n; ++i)
		{
			sf("%d%d%d", &u, &v, &w);
			e[++top] = v, wi[top] = w, nex[top] = h[u], h[u] = top;
			e[++top] = u, wi[top] = w, nex[top] = h[v], h[v] = top;
		}
		tree[1].dep = 0;
		tree[1].sum = tree[1].inv_sum = 0;
		mem(vis, 0);
		dfs(1);

		sf("%d", &qq);
		REP(i,1,n){ G[i].clear(); fat[i] = i; vis[i] = 0; }
		REP(i,1,qq)
		{
			sf("%d%d", &u, &v);
			G[u].push_back( Ques(v, 1, i) );
			G[v].push_back( Ques(u, 2, i) );
		}
		dfs2(1);
		printf("Case #%d:\n", t);
		REP(i,1,qq) pf("%lld\n", ans[i]);
	}
	return 0;
}
