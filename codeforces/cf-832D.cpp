#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 1e5;
const int MaxStep = 20;

int n;
int depth[maxn + 2], dest[maxn + 2][MaxStep + 2];
vector<int> G[maxn + 2];

void dfs(int x, int par) {
	depth[x] = depth[par] + 1;
	dest[x][0] = par;
	for(int i = 0; dest[x][i] != 0; ++i)
		dest[x][i+1] = dest[dest[x][i]][i];
	for(auto nx: G[x]) {
		if(nx != par)
			dfs(nx, x);
	}
}

int LCA(int u, int v) {
	if(depth[u] < depth[v]) swap(u, v);
	int del = depth[u] - depth[v];
	for(int i = MaxStep; i >= 0; --i) {
		if(del & (1 << i))
			u = dest[u][i];
	}
	if(u == v) return u;
	for(int i = MaxStep; i >= 0; --i) {
		if(dest[u][i] == dest[v][i])
			continue;
		u = dest[u][i], v = dest[v][i];
	}
	return dest[u][0];
}

int Dist(int u, int v) {
	return depth[u] + depth[v] - depth[LCA(u,v)] * 2 + 1;
}

int Run(int s, int f, int t) {
	int sf = LCA(s, f), st = LCA(s, t), tf = LCA(f, t);
	if((Dist(s, sf) + Dist(sf, t) - 1 == Dist(s, t)) && (Dist(f, sf) + Dist(sf, t) - 1 == Dist(f, t)))
		return Dist(sf, f);
	if((Dist(t, tf) + Dist(tf, s) - 1 == Dist(t, s)) && (Dist(f, tf) + Dist(tf, s) - 1 == Dist(s, f)))
		return Dist(tf, f);
	if((Dist(t, st) + Dist(st, f) - 1 == Dist(t, f)) && (Dist(s, st) + Dist(st, f) - 1 == Dist(s, f)))
		return Dist(st, f);
}

int main() {
	int T, u, a, b, c;
	scanf("%d%d", &n, &T);
	for(int i = 2; i <= n; ++i) {
		scanf("%d", &u);
		G[i].push_back(u), G[u].push_back(i);
	}
	dfs(1, 0);
	while(T--) {
		scanf("%d%d%d", &a, &b, &c);
		int ans = 0;
		ans = max(ans, Run(a, b, c));
		ans = max(ans, Run(b, a, c));
		ans = max(ans, Run(a, c, b));
		printf("%d\n", ans);
	}
	return 0;
}
