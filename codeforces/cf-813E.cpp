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

#define lson (x << 1)
#define rson (x << 1 | 1)
#define mid ((l + r) >> 1)

const int maxn = 1e5;

int n, kk, arr[maxn + 2];
int seq[maxn + 2], nex[maxn + 2], h[maxn + 2], e[maxn + 2], dis[maxn + 2];

vector<int> nd[maxn * 4 + 2];

void build(int x, int l, int r) {
	if(l == r) {
		nd[x].push_back(seq[l]);
		return;
	}
	build(lson, l, mid);
	build(rson, mid + 1, r);
	int i = 0, j = 0;
	while(i < nd[lson].size() && j < nd[rson].size()) {
		if(nd[lson][i] < nd[rson][j])
			nd[x].push_back(nd[lson][i]), ++i;
		else nd[x].push_back(nd[rson][j]), ++j;
	}
	while(i < nd[lson].size())
		nd[x].push_back(nd[lson][i]), ++i;
	while(j < nd[rson].size())
		nd[x].push_back(nd[rson][j]), ++j;
	return;
}

int query(int x, int l, int r, int tl, int tr) {
	if(tl <= l && tr >= r)
		return lower_bound(nd[x].begin(), nd[x].end(), tl) - nd[x].begin();
	int res = 0;
	if(tl <= mid)
		res += query(lson, l, mid, tl, tr);
	if(tr >= mid + 1)
		res += query(rson, mid + 1, r, tl, tr);
	return res;
}

int main() {
	scanf("%d%d", &n, &kk);
	REP(i,1,n) scanf("%d", arr + i);
	for(int i = 1; i <= n; ++i) {
		if(h[arr[i]] == 0)
			h[arr[i]] = e[arr[i]] = i, seq[i] = 0, dis[arr[i]] = 0;
		else {
			nex[e[arr[i]]] = i, e[arr[i]] = i, ++dis[arr[i]];
			if(dis[arr[i]] > kk) {
				h[arr[i]] = nex[h[arr[i]]];
				--dis[arr[i]];
			}
			seq[i] = dis[arr[i]] == kk ? h[arr[i]] : 0;
		}
	}
	build(1, 1, n);
	int T, l, r, key = 0;
	scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &l, &r);
		l = ((l + key) % n) + 1;
		r = ((r + key) % n) + 1;
		if(l > r) swap(l, r);
		printf("%d\n", key = query(1, 1, n, l, r));
	}
	return 0;
}
