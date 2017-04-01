#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<string>
#include<queue>
#include<utility>
#include<map>
#include<set>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define sf scanf
#define pf printf
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 1e5;

int n, m;
int pp[maxn+5];
pii seg[maxn+5];
priority_queue<int> que;

int main()
{
	int T, ans;
	sf("%d", &T);
	REP(t,1,T)
	{
		sf("%d%d", &n, &m);
		REP(i,1,n) sf("%d%d", &seg[i].first, &seg[i].second);
		REP(i,1,m) sf("%d", &pp[i]);
		sort(seg+1, seg+1+n);
		sort(pp+1, pp+1+m);
		while(!que.empty()) que.pop();
		ans = 0;
		for(int i=1, pt=1; i<=m; ++i)
		{
			while(pt<=n && seg[pt].first <= pp[i])
				que.push(-seg[pt++].second);
			while(!que.empty() && -que.top() < pp[i])
				que.pop();
			if(!que.size()) { ans = -1; break; }
			ans = max(ans, int(n - que.size() + 1));
			que.pop();
		}
		printf("Case #%d: ", t);
		if(~ans) printf("%d\n", ans);
		else printf("IMPOSSIBLE!\n");
	}
	return 0;
}
