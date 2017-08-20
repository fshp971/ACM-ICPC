#include<bits/stdc++.h>

using namespace std;

#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define FOR(i,a,b) for(int i = a; i < b; ++i)
#define mem(a,b) memset(a,b,sizeof(a))
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

const int maxnode = 1e5, c_size = 26;

struct Tire {
	int tot;
	int nex[maxnode + 5][c_size], val[maxnode + 5];
	int fail[maxnode + 5];

	void clear() {
		tot = val[0] = 0;
		mem(nex[0], 0);
	}

	inline int c_id(char c) { return c - 'a'; }

	void insert(string &a, vector<int> &b) {
		b.clear();
		int u = 0, t;
		for(auto it: a) {
			t = c_id(it);
			if(!nex[u][t]) {
				nex[u][t] = (++tot), val[tot] = val[u] + 1;
				mem(nex[tot], 0);
			}
			u = nex[u][t];
			b.push_back(u);
		}
	}

	void GetFail() {
		fail[0] = 0;
		queue<int> q;
		for(int i = 0; i < c_size; ++i) if(int &t = nex[0][i]) {
			fail[t] = 0;
			q.push(t);
		}
		while(!q.empty()) {
			int x = q.front(); q.pop();
			for(int i = 0; i < c_size; ++i) {
				int u = nex[x][i];
				if(!u) { nex[x][i] = nex[fail[x]][i]; continue; }
				q.push(u);
				int v = fail[x];
				while(v && !nex[v][i]) v = fail[v];
				fail[u] = nex[v][i];
			}
		}
	}

	void BuildTree(vector<int> *G) {
		for(int i = 0; i <= tot; ++i)
			G[i].clear();
		for(int i = 1; i <= tot; ++i)
			G[fail[i]].push_back(i);
	}
} AC;

vector<int> G[maxnode + 2];
int st[maxnode + 2][20], DFN[maxnode + 2], dep[maxnode + 2];

void dfs(int x, int &dd, int pre) {
	mem(st[x], -1);
	st[x][0] = pre;
	DFN[x] = dd++;
	for(int i = 0; st[x][i] != -1; ++i)
		st[x][i+1] = st[st[x][i]][i];
	for(auto it: G[x]) {
		dep[it] = dep[x] + 1;
		dfs(it, dd, x);
	}
}

int LCA(int u, int v) {
	if(dep[u] < dep[v])
		swap(u, v);
	int del = dep[u] - dep[v];
	for(int i = 0; del > 0; ++i, del >>= 1) {
		if(del & 1)
			u = st[u][i];
	}
	for(int i = 18; i >= 0; --i) {
		if(st[u][i] != st[v][i])
			u = st[u][i], v = st[v][i];
	}
	if(u != v) u = st[u][0];
	return u;
}

int n;
char aa[maxnode + 2];
vector<int> num[maxnode + 2];

bool cmp(const int &a, const int &b) {
	return DFN[a] > DFN[b];
}

int main() {
	int T, dd, q, u, v;
	string str;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		AC.clear();
		for(int i = 1; i <= n; ++i) {
			scanf("%s", aa);
			str = string(aa);
			AC.insert(str, num[i]);
		}
		AC.GetFail();
		AC.BuildTree(G);
		dfs(0, dd = 0, -1);
		for(int i = 1; i <= n; ++i)
			sort(num[i].begin(), num[i].end(), cmp);
		scanf("%d", &q);
		while(q--) {
			scanf("%d%d", &u, &v);
			int pt1 = 0, pt2 = 0, l1 = num[u].size(), l2 = num[v].size();
			int ans = 0;
			while(pt1 < l1 && pt2 < l2) {
				while(pt1 < l1 && DFN[num[u][pt1]] >= DFN[num[v][pt2]])
					ans = max(ans, AC.val[ LCA(num[u][pt1++], num[v][pt2]) ]);
				if(pt1 >= l1) break;
				while(pt2 < l2 && DFN[num[v][pt2]] >= DFN[num[u][pt1]])
					ans = max(ans, AC.val[ LCA(num[u][pt1], num[v][pt2++]) ]);
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}
