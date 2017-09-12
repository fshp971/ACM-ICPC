#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 2000, c_size = 26;

struct State {
	int val;
	State *par, *go[c_size];
	void init() { val = 0, par = NULL, mem(go, 0); }
} que[maxn * 2 + 5], *root, *last;
int tot;

int sum;
void Extend(int w) {
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
	last = np;
	sum += np->val - np->par->val;
}

int n, m;
int ans[int(1e4 + 5)];
char str[maxn + 5];
vector<pii> G[maxn + 5];

int main() {
	int T, l, r;
	scanf("%d", &T);
	while(T--) {
		scanf("%s", str), n = strlen(str);
		for(int i = 1; i <= n; ++i) G[i].clear();
		scanf("%d", &m);
		for(int i = 1; i <= m; ++i) {
			scanf("%d%d", &l, &r);
			G[l].push_back( MP(r,i) );
		}
		for(int i = 1; i <= n; ++i) {
			if(!G[i].size()) continue;
			sort(G[i].begin(), G[i].end());
			int pos = i - 1;
			sum = 0;
			root = last = que;
			tot = 1, que[0].init();
			for(auto it: G[i]) {
				while(pos < it.first)
					Extend(str[pos++] - 'a');
				ans[it.second] = sum;
			}
		}
		for(int i = 1; i <= m; ++i)
			printf("%d\n", ans[i]);
	}
	return 0;
}
