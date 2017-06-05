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

const int maxn = 1e5;

map<int, LL> Map[2];
map<int, LL>::iterator it;
int n, aa[maxn + 2];
vector<int> G[maxn + 2];

int dfs(int x) {
	int col = 0;
	for(int i = 0; i < G[x].size(); ++i)
		col = dfs(G[x][i]);
	if(!Map[col].count(aa[x]))
		Map[col][aa[x]] = 1;
	else ++Map[col][aa[x]];
	return col ^ 1;
}

int main() {
	int u, S = 0;
	LL ans = 0;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i)
		scanf("%d", aa + i);
	for(int i = 2; i <= n; ++i)
		scanf("%d", &u), G[u].push_back(i);
	dfs(1);
	for(it = Map[0].begin(); it != Map[0].end(); ++it)
		S ^= (it->second & 1) ? it->first : 0;
	if(S == 0) {
		LL all = 0;
		for(it = Map[0].begin(); it != Map[0].end(); ++it) {
			if(Map[1].count(it->first))
				ans += Map[1][it->first] * it->second;
			all += it->second;
		}
		ans += all * (all - 1) / 2;
		all = n - all;
		ans += all * (all - 1) / 2;
	}
	else {
		for(it = Map[0].begin(); it != Map[0].end(); ++it)
			if(Map[1].count(it->first ^ S))
				ans += Map[1][it->first ^ S] * it->second;
	}
	printf("%lld\n", ans);
	return 0;
}
