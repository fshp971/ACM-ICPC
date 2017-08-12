#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 1e5;

bool vist[maxn + 2];
vector<int> Pri[maxn + 2];
vector<pii> Val[maxn + 2];

void Init() {
	for(int i = 2; i <= maxn; ++i)
		if(!vist[i]) {
			for(int k = i; k <= maxn; k += i)
				vist[k] = 1, Pri[k].push_back(i);
		}
	int x, fg;
	for(int i = 1; i <= maxn; ++i) {
		for(int k = 0; k < (1 << int(Pri[i].size())); ++k) {
			x = 1, fg = 1;
			for(int j = 0; j < int(Pri[i].size()); ++j) {
				if(k & (1 << j))
					x *= Pri[i][j], fg = -fg;
			}
			Val[i].push_back( MP(x,fg) );
		}
	}
}

int n, m, pos[maxn + 2], arr[maxn + 2];
int cnt[maxn + 2];
vector<pii> Que[maxn + 2];
vector<int> Seg;
LL Ans[maxn + 2];

LL tree[maxn + 2];
void Add(int x, LL del) {
	for(; x <= n; x += x & (-x))
		tree[x] += del;
}

LL Sum(int x) {
	LL res = 0;
	for(; x > 0; x -= x & (-x))
		res += tree[x];
	return res;
}

int main() {
	Init();
	int T, u, v, cc;
	scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		for(int i = 1; i <= n; ++i) {
			scanf("%d", arr + i);
			pos[arr[i]] = i, tree[i] = 0;
			Que[i].clear();
		}
		for(int i = 1; i <= m; ++i) {
			scanf("%d%d", &u, &v);
			Que[v].push_back( MP(u,i) );
		}
		for(int i = 1; i <= n; ++i) {
			Seg.clear();
			for(int k = arr[i]; k <= n; k += arr[i])
				if(pos[k] < i)
					Seg.push_back(pos[k]);
			sort(Seg.begin(), Seg.end());
			for(int k = Seg.size() - 1; k >= 0; --k) {
				int tmp = arr[Seg[k]] / arr[i];
				cc = 0;
				for(auto it: Val[tmp]) {
					cc += cnt[it.first] * it.second;
					++cnt[it.first];
				}
				Add(1, LL(cc) * arr[i]);
				Add(Seg[k] + 1, LL(-cc) * arr[i]);
			}
			for(int k = Seg.size() - 1; k >= 0; --k) {
				int tmp = arr[Seg[k]] / arr[i];
				for(auto it: Val[tmp])
					--cnt[it.first];
			}
			for(auto it: Que[i])
				Ans[it.second] = Sum(it.first);
		}
		for(int i = 1; i <= m; ++i)
			printf("%lld\n", Ans[i]);
	}
	return 0;
}
