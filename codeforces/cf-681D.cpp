#include<bits/stdc++.h>

using namespace std;

#define LL long long
#define MP(a,b) make_pair(a,b)
#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define pii pair<int,int>
#define sf scanf
#define pf printf

const int maxn = 100000;

int n, m;
int h[maxn+10], e[maxn*2+10], nex[maxn*2+10], vis[maxn+10];
int cnt[maxn+10];
int sta[maxn+10];
int arr[maxn+10], head, tail;

int dfs(int x, int now)
{
	if(cnt[x] && x!=now)
	{
		arr[++tail] = x;
		return 0;
	}
	int sum = 1;
	for(int i=h[x]; i; i=nex[i])
		sum += dfs(e[i], now);
	return sum;
}

void init()
{
	cin >> n >> m;
	mem(h,0); mem(vis,0); mem(cnt,0);
	int top = 0, a, b;
	REP(i,1,m)
	{
		sf("%d%d", &a, &b);
		e[++top] = b; nex[top] = h[a]; h[a] = top;
		++vis[b];
	}
	head = 1; tail = 0;
	REP(i,1,n)
	{
		sf("%d", &a);
		++cnt[a];
		if(!vis[i]) arr[++tail] = i;
	}
	sta[0] = 0;
	while(head<=tail)
	{
		//cnt[arr[head]] -= dfs(arr[head]);
		int tmp = dfs(arr[head], arr[head]);
		//pf("x = %d, tmp = %d\n", arr[head], tmp);
		cnt[arr[head]] -= tmp;
		if(cnt[arr[head]])
		{
			pf("-1\n");
			return;
		}
		sta[++sta[0]] = arr[head];
		++head;
	}
	pf("%d\n", sta[0]);
	for(int i=sta[0]; i>=1; --i) pf("%d\n", sta[i]);
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	init();
	return 0;
}
