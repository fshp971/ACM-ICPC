#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 1e5, c_size = 4;

struct PTree {
	int tot, last, S_len;
	int len[maxn + 2], fail[maxn + 2], S[maxn + 2];
	int nex[maxn + 2][c_size], par[maxn + 2];

	int NewNode(int l) {
		len[tot] = l, fail[tot] = 0;
		mem(nex[tot], 0), par[tot] = -1;
		return tot++;
	}

	void Init() {
		tot = 0;
		NewNode(0), NewNode(-1);
		fail[0] = 1, last = 0;
		S[S_len = 0] = -1;
	}

	int GetFail(int x) {
		while(S[S_len - len[x] - 1] != S[S_len])
			x = fail[x];
		return x;
	}

	void Add(int w) {
		S[++S_len] = w;
		last = GetFail(last);
		if(nex[last][w] == 0) {
			int u = NewNode(len[last] + 2);
			par[u] = last;
			fail[u] = nex[GetFail(fail[last])][w];
			nex[last][w] = u;
		}
		last = nex[last][w];
	}
} tree;

void ReFail() {
	tree.fail[0] = 0;
	for(int i = 1; i < tree.tot; ++i)
		while(tree.len[tree.fail[i]] % 2)
			tree.fail[i] = tree.fail[tree.fail[i]];
}

int MaxStep;
int go[maxn + 2][23];

void PreCalc() {
	MaxStep = 0;
	while((1 << MaxStep) < tree.tot) ++MaxStep;
	mem(go[0], -1);
	for(int i = 1; i < tree.tot; ++i) {
		mem(go[i], -1);
		go[i][0] = tree.fail[i];
		for(int k = 0; go[i][k] != -1; ++k)
			go[i][k + 1] = go[go[i][k]][k];
	}
}

int full[maxn + 2], half[maxn + 2];
char arr[maxn + 2];

int main() {
	int T, n, ans;
	scanf("%d", &T);
	while(T--) {
		scanf("%s", arr);
		n = strlen(arr);
		tree.Init();
		for(int i = 0; i < n; ++i) {
			if(arr[i] == 'A') tree.Add(0);
			else if(arr[i] == 'G') tree.Add(1);
			else if(arr[i] == 'C') tree.Add(2);
			else tree.Add(3);
		}
		ReFail();
		PreCalc();
		ans = n;
		full[0] = half[0] = 0;
		for(int i = 1; i < tree.tot; ++i) {
			if(tree.len[i] % 2) continue;
			int key = i, lim = tree.len[i] >> 1;
			for(int k = MaxStep; k >= 0; --k) {
				if(go[key][k] == -1) continue;
				if(tree.len[go[key][k]] > lim)
					key = go[key][k];
			}
			key = go[key][0];
			half[i] = half[tree.par[i]] + 1;
			half[i] = min(half[i], lim - tree.len[key] + full[key]);
			full[i] = half[i] + 1;
			full[i] = min(full[i], full[tree.par[i]] + 2);
			full[i] = min(full[i], tree.len[i] - tree.len[tree.fail[i]] + full[tree.fail[i]]);
			ans = min(ans, n - tree.len[i] + full[i]);
		}
		printf("%d\n", ans);
	}
	return 0;
}
