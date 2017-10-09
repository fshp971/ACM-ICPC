#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 3e5, c_size = 12;

struct Tire {
	int top;
	int nex[maxn + 2][c_size], par[maxn + 2];
	int fail[maxn + 2], last[maxn + 2];

	void init() { par[0] = -1, top = 1; }

	int insert(vector<int> &a) {
		int u = 0, t;
		for(int i = 0; i < a.size(); ++i) {
			t = a[i];
			if(!nex[u][t]) {
				nex[u][t] = top, par[top] = u;
				mem(nex[top++], 0);
			}
			u = nex[u][t];
		}
		return u;
	}

	void GetFail() {
		fail[0] = last[0] = 0;
		queue<int> q;
		for(int i = 0; i < c_size; ++i) if(int &t = nex[0][i]) {
			fail[t] = last[t] = 0;
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
				last[u] = fail[u];
			}
		}
	}
} AC;

int n, m, TP[maxn + 2], ans[maxn + 2], MaxLen[maxn + 2];
int STLen[maxn + 2];
vector<int> G[maxn + 2];
vector<pii> Query[maxn + 2];
char wd[maxn + 2];

int T = 0, Tin[maxn + 2], Tout[maxn + 2];

int level = 0, tree[maxn + 2], vist[maxn + 2];

void Add(int x, int d) {
	for(; x < AC.top; x += x&(-x)) {
		if(vist[x] != level)
			vist[x] = level, tree[x] = 0;
		tree[x] += d;
	}
}

int Sum(int x) {
	int res = 0;
	for(; x > 0; x -= x&(-x)) {
		if(vist[x] != level)
			vist[x] = level, tree[x] = 0;
		res += tree[x];
	}
	return res;
}

void Build(int x) {
	Tin[x] = T++;
	for(int i = 0; i < G[x].size(); ++i)
		Build(G[x][i]);
	Tout[x] = T - 1;
}

void Solve() {
	for(int i = 1; i < AC.top; ++i)
		G[AC.last[i]].push_back(i);
	Build(0);
	for(int i = 1; i <= n; ++i) {
		++level;
		int u = TP[i];
		while(u)
			Add(Tin[u], 1), u = AC.par[u];
		for(auto it = Query[i].begin(); it != Query[i].end(); ++it) {
			if(Sum(Tout[ TP[it->first] ]) - Sum(Tin[ TP[it->first] ] - 1) > 0)
				ans[it->second] = max(ans[it->second], STLen[it->first]);
		}
	}
	for(int i = 1; i <= n; ++i) {
		int u = TP[i], tl = STLen[i];
		set<pii> Set;
		for(auto it = Query[i].begin(); it != Query[i].end(); ++it)
			Set.insert( MP(Tin[ TP[it->first] ], it->second) );
		while(u) {
			while(1) {
				auto it = Set.lower_bound( MP(Tin[u], 0) );
				if(it == Set.end() || (it->first) > Tout[u])
					break;
				ans[it->second] = max(ans[it->second], tl);
				Set.erase(it);
			}
			u = AC.par[u], --tl;
		}
	}
	for(int i = 1; i <= m; ++i)
		printf("%d\n", MaxLen[i] - ans[i]);
}

void Init() {
	scanf("%d", &n);
	vector<int> wd2;
	int len, x, y;
	AC.init();
	REP(i,1,n) {
		scanf("%s", wd);
		len = strlen(wd);
		wd2.clear();
		FOR(k,0,len) {
			if(k+1 < len && wd[k+1] == '#') {
				if(wd[k] == 'C') x = 1;
				else if(wd[k] == 'D') x = 3;
				else if(wd[k] == 'F') x = 6;
				else if(wd[k] == 'G') x = 8;
				else if(wd[k] == 'A') x = 10;
				++k;
			}
			else {
				if(wd[k] == 'C') x = 0;
				else if(wd[k] == 'D') x = 2;
				else if(wd[k] == 'E') x = 4;
				else if(wd[k] == 'F') x = 5;
				else if(wd[k] == 'G') x = 7;
				else if(wd[k] == 'A') x = 9;
				else x = 11;
			}
			wd2.push_back(x);
		}
		STLen[i] = wd2.size();
		TP[i] = AC.insert(wd2);
	}
	scanf("%d", &m);
	REP(i,1,m) {
		scanf("%d%d", &x, &y);
		MaxLen[i] = STLen[x] + STLen[y];
		Query[x].push_back( MP(y, i) );
		Query[y].push_back( MP(x, i) );
	}
	AC.GetFail();
}

int main() {
	Init();
	Solve();
	return 0;
}
