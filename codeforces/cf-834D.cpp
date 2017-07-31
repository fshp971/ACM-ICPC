#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<queue>
#include<utility>
#include<bitset>
#include<complex>
#include<map>
#include<set>
#include<unordered_map>
#include<unordered_set>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

#define mid ((l + r) >> 1)
#define lson (x << 1)
#define rson (x << 1 | 1)

const int maxn = 35000;
const int maxnode = (maxn << 2) + 10;

int n, kk, arr[maxn + 2], last[maxn + 2];
int f[2][maxnode + 2];
int lazy[2][maxnode + 2];
int tree[2][maxnode + 2];

void Build(int x, int l, int r, int *tr, int *la, int *aa) {
	la[x] = 0;
	if(l == r) tr[x] = aa[l - 1];
	else {
		Build(lson, l, mid, tr, la, aa);
		Build(rson, mid + 1, r, tr, la, aa);
		tr[x] = min(tr[lson], tr[rson]);
	}
}

void Inc(int x, int l, int r, int *tr, int *la, int ll, int rr) {
	if(ll <= l && r <= rr)
		++la[x];
	else {
		la[lson] += la[x], la[rson] += la[x], la[x] = 0;
		if(ll <= mid)
			Inc(lson, l, mid, tr, la, ll, rr);
		if(mid + 1 <= rr)
			Inc(rson, mid + 1, r, tr, la, ll, rr);
		tr[x] = max(tr[lson] + la[lson], tr[rson] + la[rson]);
	}
}

int Query(int x, int l, int r, int *tr, int *la, int ll, int rr) {
	if(ll <= l && r <= rr)
		return tr[x] + la[x];
	int res = 0;
	if(ll <= mid)
		res = max(res, Query(lson, l, mid, tr, la, ll, rr));
	if(mid + 1 <= rr)
		res = max(res, Query(rson, mid + 1, r, tr, la, ll, rr));
	return res;
}

int main() {
	int a, par = 0;
	scanf("%d%d", &n, &kk);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &a);
		arr[i] = last[a] + 1;
		last[a] = i;
	}
	while(kk--) {
		Build(1, 1, n, tree[par], lazy[par], f[par]);
		for(int i = 1; i <= n; ++i) {
			Inc(1, 1, n, tree[par], lazy[par], arr[i], i);
			f[par^1][i] = Query(1, 1, n, tree[par], lazy[par], 1, i);
		}
		par ^= 1;
	}
	printf("%d\n", f[par][n]);
	return 0;
}
