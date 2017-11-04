//#include<cstdio>
#include<stdio.h>
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
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,int> pli;

const int maxn = 1e5;

int n, m;
int nex[maxn + 5], pre[maxn + 5];
bool vis[maxn + 5], dead[maxn + 5];
LL ai[maxn + 5], seg[maxn + 5];

priority_queue<pli> que;

int main() {
	scanf("%d%d", &n, &m);
	REP(i,1,n) scanf("%lld", ai + i);
	int tot = 0, blo = 0;
	LL ans = 0;
	for(int i = 1, nx = 0; i <= n; i = nx) {
		LL tmp = 0;
		for(nx = i; nx <= n; ++nx) {
			if(ai[i] > 0 && ai[nx] <= 0) break;
			if(ai[i] <= 0 && ai[nx] > 0) break;
			tmp += ai[nx];
		}
		seg[++tot] = tmp, vis[tot] = (ai[i] > 0);
		if(vis[tot]) ++blo,ans += seg[tot];
	}
	if(tot > 1 && !(vis[1] ^ vis[tot])) {
		seg[1] += seg[tot--];
		if(vis[1]) --blo;
	}
	nex[tot] = 1, pre[1] = tot;
	for(int i = 1; i <= tot; ++i) {
		if(i < tot) nex[i] = i + 1, pre[i+1] = i;
		if(vis[i]) que.push(MP(-seg[i], i));
		else que.push(MP(seg[i], i));
	}
	while(blo > m) {
		pii x = que.top(); que.pop();
		if(dead[x.se]) continue;
		int u = nex[x.se], v = pre[x.se];
		pre[nex[u]] = x.se,  nex[pre[v]] = x.se;
		nex[x.se] = nex[u], pre[x.se] = pre[v];
		dead[u] = dead[v] = 1;
		if(vis[x.se]) {
			ans -= seg[x.se];
			seg[x.se] += seg[u] + seg[v];
			vis[x.se] = 0;
			que.push(MP(seg[x.se], x.se));
		}
		else {
			ans += seg[x.se];
			seg[x.se] += seg[u] + seg[v];
			vis[x.se] = 1;
			que.push(MP(-seg[x.se], x.se));
		}
		--blo;
	}
	printf("%lld\n", ans);
	return 0;
}
