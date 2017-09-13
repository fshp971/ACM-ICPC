#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 5e4, maxm = 2e5;
const int maxnode = (maxn + maxm) << 1, c_sz = 26;

struct State {
	int val;
	int par, go[c_sz];
	void init() { val = 0, par = -1, mem(go, -1); }
} que[maxnode + 5];
int tot, root, last;

int cnt[maxnode + 5], fa[maxnode + 5], det[maxnode + 5];

int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

void Extend(int w) {
	int p = last, np = tot++;
	que[np].init();
	que[np].val = que[p].val + 1;
	cnt[np] = 1, det[np] = 0, fa[np] = np;
	while(p != -1 && que[p].go[w] == -1)
		que[p].go[w] = np, p = que[p].par;
	if(p == -1) que[np].par = root;
	else {
		int q = que[p].go[w];
		if(que[p].val + 1 == que[q].val) que[np].par = q;
		else {
			int nq = tot++;
			que[nq] = que[q];
			que[nq].val = que[p].val + 1;
			cnt[nq] = 0, det[nq] = 0, fa[nq] = nq;
			que[np].par = que[q].par = nq;
			while(p != -1 && que[p].go[w] == q)
				que[p].go[w] = nq, p = que[p].par;
		}
	}
	last = np;
}

int n, m, kk, ord[maxm + 5], idx[maxm + 5];
char str[maxn + 5];
vector<LL> ans;

int cont[maxnode + 5], S[maxnode + 5];

int main() {
	char aa[5];
	while(~scanf("%d%d%d", &n, &m, &kk)) {
		scanf("%s", str);
		root = last = 0;
		tot = 1, que[0].init();
		cnt[0] = det[0] = fa[0] = 0;
		for(int i = 0; i < n; ++i)
			Extend(str[i] - 'a');
		for(int i = 1; i <= m; ++i) {
			scanf("%d", ord + i);
			if(ord[i] == 1)
				scanf("%s", aa), Extend(aa[0] - 'a'), ++n, idx[i] = last;
		}
		for(int i = 0; i <= n; ++i) cont[i] = 0;
		for(int i = 0; i < tot; ++i) ++cont[que[i].val];
		for(int i = 1; i <= n; ++i) cont[i] += cont[i - 1];
		for(int i = tot - 1; i >= 1; --i) S[--cont[que[i].val]] = i;
		LL sum = 0;
		for(int i = tot - 1; i >= 1; --i) {
			cnt[que[S[i]].par] += cnt[S[i]];
			if(cnt[S[i]] >= kk)
				sum += que[S[i]].val - que[que[S[i]].par].val;
		}
		ans.clear();
		for(int i = m; i >= 1; --i) {
			if(ord[i] == 1) {
				int u = find(idx[i]);
				while(u != root && cnt[u] < kk) {
					fa[u] = find(que[u].par);
					u = fa[u];
				}
				u = find(idx[i]);
				++det[u];
				while(u != root && cnt[u] - det[u] < kk) {
					sum -= que[u].val - que[que[u].par].val;
					fa[u] = find(que[u].par);
					det[fa[u]] += det[u];
					u = fa[u];
				}
			}
			else ans.push_back(sum);
		}
		for(int i = ans.size() - 1; i >= 0; --i)
			printf("%lld\n", ans[i]);
	}
	return 0;
}
