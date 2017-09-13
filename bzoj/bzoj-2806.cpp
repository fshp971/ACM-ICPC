/**************************************************************
	Problem: 2806
	User: fshp971
	Language: C++
	Result: Accepted
	Time:1240 ms
	Memory:58224 kb
****************************************************************/
 
#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 1100000;
const int maxnode = maxn << 1, c_sz = 3;

struct State {
	int val;
	State *par, *go[c_sz];
	void init() { val = 0, par = NULL, mem(go, 0); }
} que[maxnode + 5], *root, *last;
int tot;

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
}

int n, m, len, lim;
char str[maxn + 5];
int match[maxn + 5], f[maxn + 5];

int qq[maxn + 5];
bool Check(int L, int lim) {
	int pt = 0, head = 0, tail = -1;
	for(int i = 1; i <= len; ++i) {
		f[i] = f[i - 1];
		while(pt <= i - L) {
			while(head <= tail && f[pt] - f[qq[tail]] >= pt - qq[tail])
				--tail;
			qq[++tail] = pt++;
		}
		while(head <= tail && qq[head] < i - match[i])
			++head;
		if(head <= tail)
			f[i] = max(f[i], f[qq[head]] + i - qq[head]);
	}
	return f[len] >= lim;
}

int main() {
	scanf("%d%d", &n, &m);
	root = last = que;
	tot = 1, que[0].init();
	for(int i = 1; i <= m; ++i) {
		scanf("%s", str);
		for(int k = 0; str[k] != '\0'; ++k)
			Extend(str[k] - '0');
		Extend(2);
	}
	for(int i = 1; i <= n; ++i) {
		scanf("%s", str);
		len = strlen(str), lim = ceil(len * 0.9);
		State *p = root;
		int now = 0;
		for(int k = 0; str[k] != '\0'; ++k) {
			int w = str[k] - '0';
			if(p->go[w] != NULL)
				p = p->go[w], ++now;
			else {
				while(p != NULL && p->go[w] == NULL)
					p = p->par;
				if(p == NULL) p = root, now = 0;
				else {
					now = p->val + 1;
					p = p->go[w];
				}
			}
			match[k + 1] = now;
		}

		int ans = 0, l = 1, r = len, mid;
		while(l <= r) {
			mid = (l + r) >> 1;
			if(Check(mid, lim))
				ans = mid, l = mid + 1;
			else r = mid - 1;
		}
		printf("%d\n", ans);
	}
	return 0;
}
