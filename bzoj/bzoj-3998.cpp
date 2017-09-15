/**************************************************************
	Problem: 3998
	User: fshp971
	Language: C++
	Result: Accepted
	Time:7736 ms
	Memory:128736 kb
****************************************************************/

#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 5e5, c_sz = 26;
const int maxnode = maxn << 1;

struct State {
	int val, cnt;
	LL sum;
	int par, go[c_sz];
	void init() { val = cnt = sum = 0, par = -1, mem(go, -1); }
} que[maxnode + 5];
int tot, root, last;

void Extend(int w) {
	int p = last, np = tot++;
	que[np].init();
	que[np].val = que[p].val + 1, que[np].cnt = 1;
	while(p != -1 && que[p].go[w] == -1)
		que[p].go[w] = np, p = que[p].par;
	if(p == -1) que[np].par = root;
	else {
		int q = que[p].go[w];
		if(que[p].val + 1 == que[q].val) que[np].par = q;
		else {
			int nq = tot++;
			que[nq] = que[q];
			que[nq].val = que[p].val + 1, que[nq].cnt = 0;
			que[np].par = que[q].par = nq;
			while(p != -1 && que[p].go[w] == q)
				que[p].go[w] = nq, p = que[p].par;
		}
	}
	last = np;
}

int n, type, kk;
char str[maxn + 5];
int cont[maxn + 5], S[maxnode + 5];

bool vist[maxnode + 5];

int main() {
	scanf("%s", str), n = strlen(str);
	scanf("%d%d", &type, &kk);
	root = last = 0;
	tot = 1, que[0].init();
	for(int i = 0; i < n; ++i)
		Extend(str[i] - 'a');
	for(int i = 0; i <= n; ++i) cont[i] = 0;
	for(int i = 0; i < tot; ++i) ++cont[que[i].val];
	for(int i = 1; i <= n; ++i) cont[i] += cont[i-1];
	for(int i = tot - 1; i >= 1; --i) S[--cont[que[i].val]] = i;
	if(type == 0)
		for(int i = 1; i <= tot - 1; ++i)
			que[i].cnt = 1;
	else
		for(int i = tot - 1; i >= 1; --i)
			que[ que[S[i]].par ].cnt += que[ S[i] ].cnt;
	que[0].cnt = 0;
	for(int i = tot - 1; i >= 0; --i) {
		que[S[i]].sum = que[S[i]].cnt;
		for(int k = 0; k < 26; ++k) {
			if(que[S[i]].go[k] != -1)
				que[S[i]].sum += que[ que[S[i]].go[k] ].sum;
		}
	}
	if(que[0].sum < kk) {
		puts("-1");
		return 0;
	}
	int u = 0;
	while(kk > que[u].cnt) {
		kk -= que[u].cnt;
		for(int i = 0; i < 26; ++i) {
			if(que[u].go[i] == -1) continue;
			int &nx = que[u].go[i];
			if(que[nx].sum < kk) kk -= que[nx].sum;
			else {
				putchar(i + 'a'), u = nx;
				break;
			}
		}
	}
	puts("");
	return 0;
}
