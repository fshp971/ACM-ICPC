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

const int maxn = 500;

int n, kk;
int arr[maxn+5];

bool f[maxn+5][maxn+5];
bool vis[maxn+5];

void init()
{
	cin >> n >> kk;
	REP(i,1,n) sf("%d", arr+i);
	mem(f, 0); mem(vis, 0);
	//REP(i,0,maxn) f[i][0] = true;
	vis[0] = true;
	f[0][0] = true;
	REP(i,1,n)
	{
		for(int k=maxn; k>=arr[i]; --k)
		{
			if(!vis[k-arr[i]]) continue;
			for(int j=maxn; j>=0; --j)
			{
				if(j>=arr[i] && f[k-arr[i]][j-arr[i]])
					vis[k] = f[k][j] = true;
				if(f[k-arr[i]][j])
					f[k][j] = true;
			}
		}
	}
	int tot = 0;
	REP(i,0,maxn)
		if(f[kk][i])
			++tot;
	pf("%d\n", tot);
	REP(i,0,maxn) if(f[kk][i])
	{
		if(i) pf(" ");
		pf("%d", i);
	}
	pf("\n");
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	init();
	return 0;
}
