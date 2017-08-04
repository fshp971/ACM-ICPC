#include<bits/stdc++.h>

using namespace std;

#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define FOR(i,a,b) for(int i = a; i < b; ++i)
#define mem(a,b) memset(a,b,sizeof(a))
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

#define lson (x << 1)
#define rson (x << 1 | 1)
#define mid ((l + r) >> 1)

const int maxn = 60000;
const int maxnode = maxn << 2;

double tree[maxnode + 2];
int lazy[maxnode + 2];

void Build(int x, int l, int r, double dat) {
	lazy[x] = 0;
	if(l == r)
		tree[x] = dat * l;
	else {
		Build(lson, l, mid, dat);
		Build(rson, mid + 1, r, dat);
		tree[x] = min(tree[lson], tree[rson]);
	}
}

void Inc(int x, int l, int r, int ll, int rr) {
	if(ll <= l && r <= rr)
		++lazy[x];
	else {
		if(lazy[x] != 0)
			lazy[lson] += lazy[x], lazy[rson] += lazy[x], lazy[x] = 0;
		if(ll <= mid)
			Inc(lson, l, mid, ll, rr);
		if(mid + 1 <= rr)
			Inc(rson, mid + 1, r, ll, rr);
		if(lazy[lson] == lazy[rson])
			lazy[x] = lazy[lson], lazy[lson] = lazy[rson] = 0;
		tree[x] = min(tree[lson] + lazy[lson], tree[rson] + lazy[rson]);
	}
}

double Query(int x, int l, int r, int ll, int rr) {
	if(ll <= l && r <= rr)
		return tree[x] + lazy[x];
	double res = 1 << 30;
	if(ll <= mid)
		res = min(res, Query(lson, l, mid, ll, rr));
	if(mid + 1 <= rr)
		res = min(res, Query(rson, mid + 1, r, ll, rr));
	return res + lazy[x];
}

int n;
int las[maxn + 2], pre[maxn + 2];

bool check(double x) {
	Build(1, 1, n, x);
	for(int i = 1; i <= n; ++i) {
		Inc(1, 1, n, pre[i] + 1, i);
		if(Query(1, 1, n, 1, i) <= x * (i + 1))
			return true;
	}
	return false;
}

int main() {
	int T, a;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i)
			las[i] = 0;
		for(int i = 1; i <= n; ++i) {
			scanf("%d", &a);
			pre[i] = las[a], las[a] = i;
		}
		double l = 0.0, r = 1.0, md, ans = 1.0;
		while(r - l > 5e-5) {
			md = (l + r) / 2;
			if(check(md))
				ans = md, r = md;
			else l = md;
		}
		printf("%.10f\n", ans);
	}
	return 0;
}
