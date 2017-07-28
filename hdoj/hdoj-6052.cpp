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

const int maxn = 100;

int n, m, mmp[maxn + 2][maxn + 2];
vector<pii> G[maxn * maxn + 2];
int sta[maxn + 2][2], f[maxn + 2][maxn + 2];

LL Run1(int x) {
	mem(f[0], 0);
	int top, tmp;
	LL sum, res = 0;
	for(int i = 1; i <= n; ++i) {
		top = 0, sum = 0;
		for(int k = 1; k <= m; ++k) {
			if(mmp[i][k] != x)
				f[i][k] = f[i-1][k] + 1;
			else f[i][k] = 0;
			tmp = 1;
			while(top && sta[top][0] >= f[i][k]) {
				tmp += sta[top][1];
				sum -= sta[top][0] * sta[top][1];
				--top;
			}
			++top;
			sta[top][0] = f[i][k];
			sta[top][1] = tmp;
			sum += f[i][k] * tmp;
			res += sum;
		}
	}
	return res;
}

LL Run2(int x) {
	int cnt = G[x].size(), ln, lm, rn, rm, fg;
	LL res = 0;
	for(int i = 1; i < (1 << cnt); ++i) {
		ln = n + 10, lm = m + 10, rn = 0, rm = 0, fg = -1;
		for(int k = 0; k < cnt; ++k)
			if(i & (1 << k)) {
				fg = -fg;
				ln = min(ln, G[x][k].first);
				lm = min(lm, G[x][k].second);
				rn = max(rn, G[x][k].first);
				rm = max(rm, G[x][k].second);
			}
		res += LL(fg) * ln * (n - rn + 1) * lm * (m - rm + 1);
	}
	return res;
}

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &m);
		FOR(i,0,maxn * maxn) G[i].clear();
		LL all = 0, sum = 0;
		REP(i,1,n) REP(k,1,m) {
			scanf("%d", &mmp[i][k]);
			G[mmp[i][k]].push_back( MP(i,k) );
			all += LL(n - i + 1) * (m - k + 1);
		}
		FOR(i,0,maxn * maxn) {
			if(!G[i].size()) continue;
			if(G[i].size() > 10)
				sum += all - Run1(i);
			else
				sum += Run2(i);
		}
		printf("%.9f\n", double(sum) / all);
	}
	return 0;
}
