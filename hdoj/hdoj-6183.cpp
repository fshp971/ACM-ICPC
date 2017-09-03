#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 1e6;
const int maxnode = 150000 * 14 * 2;

int rot[55], tot;
int tree[maxnode + 5], L[maxnode + 5], R[maxnode + 5];

int NewNode() { L[tot] = R[tot] = -1, tree[tot] = 1 << 30; return tot++; }

void Insert(int x, int l, int r, int pos, int val) {
	if(l == r)
		tree[x] = min(tree[x], val);
	else {
		int mid = (l + r) >> 1;
		if(pos <= mid) {
			if(L[x] == -1)
				L[x] = NewNode();
			Insert(L[x], l, mid, pos, val);
			tree[x] = min(tree[x], tree[L[x]]);
		}
		else {
			if(R[x] == -1)
				R[x] = NewNode();
			Insert(R[x], mid + 1, r, pos, val);
			tree[x] = min(tree[x], tree[R[x]]);
		}
	}
}

int Query(int x, int l, int r, int ll, int rr) {
	if(ll <= l && r <= rr)
		return tree[x];
	int mid = (l + r) >> 1, res = 1 << 30;
	if(ll <= mid && L[x] != -1)
		res = min(res, Query(L[x], l, mid, ll, rr));
	if(mid + 1 <= rr && R[x] != -1)
		res = min(res, Query(R[x], mid + 1, r, ll, rr));
	return res;
}

void Reset() {
	tot = 0;
	for(int i = 0; i <= 50; ++i)
		rot[i] = NewNode();
}

int main() {
	int ord, x, y, y2, c;
	Reset();
	while(1) {
		scanf("%d", &ord);
		if(ord == 0)
			Reset();
		else if(ord == 1) {
			scanf("%d%d%d", &x, &y, &c);
			Insert(rot[c], 1, maxn, y, x);
		}
		else if(ord == 2) {
			scanf("%d%d%d", &x, &y, &y2);
			int ans = 0;
			for(int i = 0; i <= 50; ++i)
				if(x >= Query(rot[i], 1, maxn, y, y2))
					++ans;
			printf("%d\n", ans);
		}
		else break;
	}
	return 0;
}
