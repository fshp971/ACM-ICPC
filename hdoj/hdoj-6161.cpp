#include<bits/stdc++.h>

using namespace std;

#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define FOR(i,a,b) for(int i = a; i < b; ++i)
#define mem(a,b) memset(a,b,sizeof(a))
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

const int maxm = 1e5 + 10;
const int maxnode = maxm << 3;

int n, m;
int que[maxm + 5], ui[maxm + 5];
LL xi[maxm + 5];
set<int> Set;
map<int,int> Map;

struct Node {
	int l, r, par;
	LL key, res1, res2;
	Node(): key(0), l(0), r(0) {}
	Node(int num, LL _key, int _l, int _r, Node &nl, Node &nr) {
		key = _key, l = _l, r = _r, par = 0;
		if(l == 0)
			res1 = Calc(key * 2);
		else {
			res1 = max(nl.res1, nl.res2) + nl.key;
			nl.par = num;
		}

		if(r == 0)
			res2 = Calc(key * 2 + 1);
		else {
			res2 = max(nr.res1, nr.res2) + nr.key;
			nr.par = num;
		}
	}

	LL Calc(int x) {
		LL res = 0;
		while(x <= n)
			res += x, x = (x << 1) + 1;
		return res;
	}

	LL GetVal() {
		return max(res1, res2) + key;
	}
} tree[maxnode + 2];
int tot;

void Update(int x, int son) {
	if(x == 0) return;
	if(tree[x].l == son)
		tree[x].res1 = tree[son].GetVal();
	else
		tree[x].res2 = tree[son].GetVal();
	Update(tree[x].par, x);
}

LL Run(int x, int son) {
	if(x == 0) return 0;
	LL res = Run(tree[x].par, x);
	if(tree[x].l == son)
		res = max(res, tree[x].res2);
	else res = max(res, tree[x].res1);
	return res + tree[x].key;
}

LL Query(int x) {
	LL res = tree[x].key;
	res = max(res, tree[tree[x].l].GetVal() + tree[tree[x].r].GetVal() + tree[x].key);
	LL tmp = Run(tree[x].par, x);
	res = max(res, tmp + tree[x].res1 + tree[x].key);
	res = max(res, tmp + tree[x].res2 + tree[x].key);
	return res;
}

int main() {
	char ord[10];
	int x, l, r;
	while(~scanf("%d%d", &n, &m)) {
		Set.clear();
		Map.clear();
		Set.insert(1);
		Set.insert(n);
		for(int i = 1; i <= m; ++i) {
			scanf("%s", ord);
			scanf("%d", ui + i);
			if(ord[0] == 'q')
				que[i] = 1;
			else {
				que[i] = 2;
				scanf("%lld", xi + i);
			}
			Set.insert(ui[i]);
		}

		tot = 0;
		while(!Set.empty()) {
			auto it1 = Set.end();
			--it1;
			if(!Map.count(*it1)) {
				Map[*it1] = ++tot;
				tree[tot] = Node(tot, *it1, 0, 0, tree[0], tree[0]);
				r = tot;
			}
			else r = Map[*it1];

			x = (*it1) >> 1;
			if(Set.size() >= 2) {
				auto it2 = it1;
				--it2;
				if(((*it2) >> 1) == x) {
					if(!Map.count(*it2)) {
						Map[*it2] = ++tot;
						tree[tot] = Node(tot, *it2, 0, 0, tree[0], tree[0]);
						l = tot;
					}
					else l = Map[*it2];

					++tot;
					tree[tot] = Node(tot, x, l, r, tree[l], tree[r]);
					Map[x] = tot;
					Set.erase(it1);
					Set.erase(it2);
					Set.insert(x);
					continue;
				}
			}

			if(x > 0) {
				++tot;
				if(x * 2 == (*it1))
					tree[tot] = Node(tot, x, r, 0, tree[r], tree[0]);
				else tree[tot] = Node(tot, x, 0, r, tree[0], tree[r]);
				Map[x] = tot;
				Set.insert(x);
			}
			Set.erase(it1);
		}

		for(int i = 1; i <= m; ++i) {
			x = Map[ui[i]];
			if(que[i] == 1)
				printf("%lld\n", Query(x));
			else {
				tree[x].key = xi[i];
				Update(tree[x].par, x);
			}
		}
	}
	return 0;
}
