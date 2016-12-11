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

const int maxn = 100000;
const int maxnode = maxn<<5;

struct Node
{
	int u, id, kk;
	Node(int _u, int _id, int _kk)
	{
		u = _u, id = _id, kk = _kk;
	}
};
vector<Node> Que[maxn+5];

int n, m, arr[maxn+5];
vector<int> G[maxn+5];
int tot, range, rot[maxn+5], Hash[maxn+5];
int L[maxnode+5], R[maxnode+5], sum[maxnode+5];
int fa[maxn+5], ance[maxn+5], ans[maxn+5];
char vis[maxn+5];

int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

int build(int l, int r)
{
	int rt = tot++;
	sum[rt] = 0;
	if(l<r)
	{
		int mid = (l+r) >> 1;
		L[rt] = build(l, mid);
		R[rt] = build(mid+1, r);
	}
	return rt;
}

int update(int &pre, int l, int r, int key)
{
	int rt = tot++;
	sum[rt] = sum[pre]+1, L[rt] = L[pre], R[rt] = R[pre];
	if(l<r)
	{
		int mid = (l+r) >> 1;
		if(key <= Hash[mid])
			L[rt] = update(L[pre], l, mid, key);
		else R[rt] = update(R[pre], mid+1, r, key);
	}
	return rt;
}

int query(int &rt1, int &rt2, int &rt3, int &rt4, int l, int r, int kk)
{
	if(l == r) return l;
	int tmp = sum[L[rt3]] + sum[L[rt4]] - sum[L[rt1]] - sum[L[rt2]];
	int mid = (l+r) >> 1;
	if(kk <= tmp)
		return query(L[rt1], L[rt2], L[rt3], L[rt4], l, mid, kk);
	else return query(R[rt1], R[rt2], R[rt3], R[rt4], mid+1, r, kk-tmp);
}

void dfs(int x, int pre)
{
	fa[x] = x, vis[x] = 1, ance[x] = pre;
	rot[x] = update(rot[pre], 1, range, arr[x]);
	for(int i=0; i<G[x].size(); ++i)
	{
		int &e = G[x][i];
		if(vis[e]) continue;
		dfs(e, x);
		fa[e] = x;
	}
	int lca;
	for(int i=0; i<Que[x].size(); ++i)
	{
		Node &tmp = Que[x][i];
		if(vis[tmp.u])
		{
			lca = find(tmp.u);
			ans[tmp.id] = Hash[query(rot[lca], rot[ance[lca]], rot[tmp.u], rot[x], 1, range, tmp.kk)];
		}
	}
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	sf("%d%d", &n, &m);
	REP(i,1,n) sf("%d", arr+i), Hash[i] = arr[i];
	int u, v, kk;
	FOR(i,1,n)
	{
		sf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	REP(i,1,m)
	{
		sf("%d%d%d", &u, &v, &kk);
		Que[u].push_back( Node(v, i, kk) );
		Que[v].push_back( Node(u, i, kk) );
	}
	sort(Hash+1, Hash+1+n);
	range = unique(Hash+1, Hash+1+n) - (Hash+1);
	tot = 0;
	rot[0] = build(1, range);
	dfs(1, 0);
	REP(i,1,m) pf("%d\n", ans[i]);
	return 0;
}
