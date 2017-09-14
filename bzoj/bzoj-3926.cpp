/**************************************************************
	Problem: 3926
	User: fshp971
	Language: C++
	Result: Accepted
	Time:3836 ms
	Memory:197984 kb
****************************************************************/

#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 1e5;
const int maxnode = maxn * 20 * 2, c_sz = 10;

struct State {
	int val;
	State *par, *go[c_sz];
	void init() { val = 0, par = NULL, mem(go, 0); }
} que[maxnode + 5], *root;
int tot;

State* Extend(int w, State *last) {
	State *p = last, *np = que + (tot++);
	np->init();
	np->val = p->val + 1;
	while(p != NULL && p->go[w] == NULL)
		p->go[w] = np, p = p->par;
	if(p == NULL) np->par = root;
	else {
		State *q = p->go[w];
		if(p->val + 1 == q->val) np->par = q;
		else {
			State *nq = que + (tot++);
			*nq = *q;
			nq->val = p->val + 1;
			np->par = q->par = nq;
			while(p != NULL && p->go[w] == q)
				p->go[w] = nq, p = p->par;
		}
	}
	return np;
}

int n;
int col[maxn + 5];
vector<int> G[maxn + 5];

void dfs(int x, int pre, State *last) {
	last = Extend(col[x], last);
	for(int i = 0; i < G[x].size(); ++i)
		if(G[x][i] != pre)
			dfs(G[x][i], x, last);
}

int main() {
	int u, v;
	scanf("%d%d", &n, &u);
	for(int i = 1; i <= n; ++i) scanf("%d", col + i);
	for(int i = 1; i < n; ++i) {
		scanf("%d%d", &u, &v);
		G[u].push_back(v);
		G[v].push_back(u);
	}
	root = que;
	tot = 1, que[0].init();
	for(int i = 1; i <= n; ++i) {
		if(G[i].size() == 1)
			dfs(i, 0, root);
	}
	LL ans = 0;
	for(int i = 1; i < tot; ++i)
		ans += que[i].val - que[i].par->val;
	printf("%lld\n", ans);
	return 0;
}
