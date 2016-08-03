#include<bits/stdc++.h>

using namespace std;

#define LL long long
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define pii pair<int,int>
#define mem(a,b) memset(a,b,sizeof(a))
#define MP(a,b) make_pair(a,b)
#define sf scanf
#define pf printf

const int maxn = 1e7;

bool vis[maxn+5];
int G[maxn+5], cnt[maxn+5];

void init()
{
	mem(cnt, 0);
	mem(vis, 0);
	mem(G, 0);
	G[1] = 1;
	for(int i=2; i<=maxn; ++i) if(!vis[i])
	{
			G[i] = -1;
		}
	}
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	init();
	return 0;
}
