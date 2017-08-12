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

const int maxn = 2e5;
const int maxnode = maxn << 2;

int n, m;
int arr[maxn + 2];
int tree[maxnode + 5];

void Build(int x, int l, int r) {
	if(l == r)
		tree[x] = arr[l];
	else {
		Build(lson, l, mid);
		Build(rson, mid + 1, r);
		tree[x] = max(tree[lson], tree[rson]);
	}
}

void Update(int x, int l, int r, int ps, int dat) {
	if(l == r)
		tree[x] = dat;
	else {
		if(ps <= mid)
			Update(lson, l, mid, ps, dat);
		else Update(rson, mid + 1, r, ps, dat);
		tree[x] = max(tree[lson], tree[rson]);
	}
}

int Query(int x, int l, int r, int ll, int rr) {
	if(ll <= l && r <= rr)
		return tree[x];
	int res = -1;
	if(ll <= mid)
		res = max(res, Query(lson, l, mid, ll, rr));
	if(mid + 1 <= rr)
		res = max(res, Query(rson, mid + 1, r, ll, rr));
	return res;
}

int main() {
	int a, b;
	char ord[5];
	while(~scanf("%d%d", &n, &m)) {
		for(int i = 1; i <= n; ++i)
			scanf("%d", arr + i);
		Build(1, 1, n);
		for(int i = 1; i <= m; ++i) {
			scanf("%s", ord);
			scanf("%d%d", &a, &b);
			if(ord[0] == 'Q')
				printf("%d\n", Query(1, 1, n, a, b));
			else Update(1, 1, n, a, b);
		}
	}
	return 0;
}
