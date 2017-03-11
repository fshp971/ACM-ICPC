#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define sf scanf
#define pf printf

typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,LL> pll;

const int maxn = 20000;
const int maxnode = maxn<<5;
const LL INF = 1LL << 50;

int n, m;
vector<pii> G[maxn+5];
LL X;
LL dist1[maxn+5], dist2[maxn+5];
LL cont1[maxn+5], cont2[maxn+5];
pll arr[maxn+5];

int root[maxn+5], tot;
int L[maxnode+5], R[maxnode+5], sum[maxnode+5];
LL Hash[maxn+5];

bool inq[maxn+5];
void Dij(int x, LL *dist, LL *cont)
{
	queue<int> que;
	for(int i=1; i<=n; ++i)
		dist[i] = INF, cont[i] = 0, inq[i] = 0;
	dist[x] = 0, cont[x] = 1, inq[x] = 1;
	que.push(x);
	while(!que.empty())
	{
		x = que.front(), inq[x] = 0, que.pop();
		for(int i=0; i<G[x].size(); ++i)
		{
			if(dist[x]+G[x][i].second < dist[G[x][i].first])
			{
				dist[G[x][i].first] = dist[x]+G[x][i].second;
				cont[G[x][i].first] = cont[x];
				if(!inq[G[x][i].first])
				{
					inq[G[x][i].first] = 1;
					que.push(G[x][i].first);
				}
			}
			else if(dist[x]+G[x][i].second == dist[G[x][i].first])
			{
				cont[G[x][i].first] += cont[x];
				if(cont[G[x][i].first] > X)
					cont[G[x][i].first] = X;

				if(!inq[G[x][i].first])
				{
					inq[G[x][i].first] = 1;
					que.push(G[x][i].first);
				}
			}
		}
	}
}

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

int update(int &rt2, int l, int r, int rank)
{
	int rt = tot++;
	sum[rt] = sum[rt2]+1, L[rt] = L[rt2], R[rt] = R[rt2];
	if(l<r)
	{
		int mid = (l+r) >> 1;
		if(rank <= mid)
			L[rt] = update(L[rt2], l, mid, rank);
		else R[rt] = update(R[rt2], mid+1, r, rank);
	}
	return rt;
}

int query(int &rt, int l, int r, int rank)
{
	if(r <= rank) return sum[rt];
	int mid = (l+r) >> 1;
	if(rank <= mid)
		return query(L[rt], l, mid, rank);
	return sum[L[rt]] + query(R[rt], mid+1, r, rank);
}

bool cmp(const pll &a, const pll &b) { return a.first >  b.first; }

int main()
{
	int u, v, w, range;
	while(sf("%d%d", &n, &m), n)
	{
		sf("%lld", &X);
		REP(i,1,n) G[i].clear();
		REP(i,1,m)
		{
			sf("%d%d%d", &u, &v, &w);
			G[u].push_back( MP(v,w) );
			G[v].push_back( MP(u,w) );
		}
		Dij(1, dist1, cont1);
		Dij(n, dist2, cont2);
		for(int i=1; i<=n; ++i)
		{
			LL t1 = dist1[n] - dist2[i] - 1;
			LL t2 = cont2[i] ? (X/cont2[i]) : INF;
			while(cont2[i] && t2*cont2[i]<X) ++t2;
			arr[i] = MP(t1, t2);
			Hash[i] = t2;
		}
		sort(arr+1, arr+1+n, cmp);
		sort(Hash+1, Hash+1+n);
		range = unique(Hash+1, Hash+1+n) - (Hash+1);
		tot = 0;
		root[0] = build(1, range);
		for(int i=1; i<=n; ++i)
		{
			int rank = lower_bound(Hash+1, Hash+1+range, arr[i].second) - Hash;
			root[i] = update(root[i-1], 1, range, rank);
		}
		LL ans = 0;
		for(int i=1; i<=n; ++i)
		{
			int l = 1, r = n, mid, lim = 0, rank;
			while(l<=r)
			{
				mid = (l+r) >> 1;
				if(dist1[i] <= arr[mid].first)
					lim = mid, l = mid+1;
				else r = mid-1;
			}
			if(cont1[i] >= Hash[range]) rank = range;
			else
				rank = upper_bound(Hash+1, Hash+1+range, cont1[i]) - Hash - 1;
			if(rank)
				ans += query(root[lim], 1, range, rank);

			for(int k=0; k<G[i].size(); ++k)
			{
				if( dist1[i]+dist2[G[i][k].first]+1 <= dist1[n]
					&& (LL)cont1[i]*cont2[G[i][k].first] >= X )
					--ans;
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
