#include<stdio.h>
//#include<cstdio>
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

const int maxn = 1e5;

int fa[maxn + 5], tot = 1;
unordered_map<int, int> id;
unordered_set<int> ene[maxn + 5];

int find(int x) { return fa[x] == x ? x : fa[x] = find(fa[x]); }

int GetId(int x) {
	if(id.count(x)) return id[x];
	fa[tot] = tot;
	id[x] = tot;
	return tot++;
}

int main() {
	int T, x, y, op;
	int n1, n2;
	scanf("%d", &T);
	while(T--) {
		scanf("%d%d%d", &x, &y, &op);
		n1 = find(GetId(x)), n2 = find(GetId(y));
		if(op == 0) {
			if(n1 != n2) {
				ene[n1].insert(n2);
				ene[n2].insert(n1);
				printf("YES\n");
			}
			else printf("NO\n");
		}
		else {
			if(ene[n1].size() > ene[n2].size())
				swap(n1, n2);
			if(!ene[n1].count(n2)) {
				fa[n1] = n2;
				if(n1 != n2) {
					for(auto it: ene[n1]) {
						ene[it].erase(n1);
						ene[it].insert(n2);
						ene[n2].insert(it);
					}
					ene[n1].clear();
				}
				printf("YES\n");
			}
			else printf("NO\n");
		}
	}
	return 0;
}
