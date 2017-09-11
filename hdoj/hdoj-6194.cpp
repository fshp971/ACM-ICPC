#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 1e5, c_size = 26;

struct State {
	int val;
	int par, go[c_size];
	void init() { val = 0, par = -1, mem(go, -1); }
} que[maxn * 2 + 5];
int tot, root, last;

void Extend(int w) {
	int p = last, np = tot++;
	que[np].init();
	que[np].val = que[p].val + 1;
	while(p != -1 && que[p].go[w] == -1)
		que[p].go[w] = np, p = que[p].par;
	if(p == -1) que[np].par = root;
	else {
		int q = que[p].go[w];
		if(que[p].val + 1 == que[q].val) que[np].par = q;
		else{
			int nq = tot++;
			que[nq] = que[q];
			que[nq].val = que[p].val + 1;
			que[np].par = que[q].par = nq;
			while(p != -1 && que[p].go[w] == q)
				que[p].go[w] = nq, p = que[p].par;
		}
	}
	last = np;
}

char str[maxn + 5];
int cont[maxn + 5], S[maxn * 2 + 5], cnt[maxn * 2 + 5];

int main() {
	int T, n, kk;
	scanf("%d", &T);
	while(T--) {
		root = last = 0;
		tot = 1, que[0].init();
		scanf("%d%s", &kk, str);
		n = strlen(str);
		for(int i = 0; i < n; ++i)
			Extend(str[i] - 'a');
		for(int i = 0; i <= n; ++i) cont[i] = 0;
		for(int i = 0; i < tot; ++i) ++cont[que[i].val], cnt[i] = 0;
		for(int i = 1; i <= n; ++i) cont[i] += cont[i - 1];
		for(int i = tot - 1; i >= 1; --i) S[--cont[que[i].val]] = i;
		int u = root;
		for(int i = 0; i < n; ++i)
			++cnt[u = que[u].go[str[i] - 'a']];
		LL ans = 0;
		for(int i = tot - 1; i >= 1; --i) {
			cnt[que[S[i]].par] += cnt[S[i]];
			if(cnt[S[i]] == kk) {
				ans += que[S[i]].val - que[que[S[i]].par].val;
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}
