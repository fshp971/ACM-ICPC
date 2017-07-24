#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 1e5;

int n, fa[maxn + 2], cont[maxn + 2];
int mx1[maxn + 2], mx2[maxn + 2], diameter[maxn + 2];
bool vist[maxn + 2];
vector<int> G[maxn + 2];
vector<LL> dist[maxn + 2];
map<pii, double> Map;

void dfs1(int x, int pre, int col) {
	vist[x] = 1, fa[x] = col;
	int aa[3];
	for(auto nx: G[x]) {
		if(nx == pre) continue;
		dfs1(nx, x, col);
		aa[0] = mx1[nx] + 1, aa[1] = mx1[x], aa[2] = mx2[x];
		sort(aa, aa + 3);
		mx1[x] = aa[2], mx2[x] = aa[1];
	}
}

void dfs2(int x, int pre, vector<LL> &ds, int di) {
	ds.push_back( max(di, mx1[x]) );
	for(auto nx: G[x]) {
		if(nx == pre) continue;
		if(mx1[nx] + 1 == mx1[x])
			dfs2(nx, x, ds, max(di, mx2[x]) + 1);
		else dfs2(nx, x, ds, max(di, mx1[x]) + 1);
	}
}

int BinSearch(vector<LL> &arr, LL key) {
	int l = 1, r = arr.size() - 1, res = 0;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(arr[mid] - arr[mid - 1] < key)
			res = mid, l = mid + 1;
		else r = mid - 1;
	}
	return res;
}

int main() {
	int m, T, u, v;
	scanf("%d%d%d", &n, &m, &T);
	REP(i,1,n) fa[i] = i;
	REP(i,1,m) {
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	REP(i,1,n) if(!vist[i]) {
		dfs1(i, 0, i);
		dfs2(i, 0, dist[i], 0);
		dist[i].push_back(0);
		sort(dist[i].begin(), dist[i].end());
		diameter[i] = dist[i][dist[i].size() - 1];
		for(int k = 1; k < dist[i].size(); ++k)
			dist[i][k] += dist[i][k-1];
	}

	while(T--) {
		scanf("%d%d", &u, &v);
		u = fa[u], v = fa[v];
		if(u == v) {
			printf("%d\n", -1);
			continue;
		}
		if(Map.count( MP(u,v) )) {
			printf("%f\n", Map[MP(u,v)]);
			continue;
		}
		if(dist[u].size() > dist[v].size())
			swap(u, v);
		LL mxd = max(diameter[u], diameter[v]), sum = 0;
		for(int i = 1; i < dist[u].size(); ++i) {
			int index = BinSearch(dist[v], mxd - (dist[u][i] - dist[u][i-1]) - 1);
			sum += (dist[v][dist[v].size() - 1] - dist[v][index]);
		   	sum += (dist[u][i] - dist[u][i-1] + 1) * (dist[v].size() - 1 - index);
			sum += mxd * index;
		}
		double ans = double(sum) / (dist[u].size() - 1) / (dist[v].size() - 1);
		Map[MP(u,v)] = Map[MP(v,u)] = ans;
		printf("%.10f\n", ans);
	}
	return 0;
}
