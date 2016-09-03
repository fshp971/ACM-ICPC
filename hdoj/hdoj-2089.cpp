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

int f[10];
int number[10];

int dfs(int poi, char flag1, char flag2)
{
	if(poi == 0) return 1;
	if(flag1 && flag2 && f[poi]!=-1) return f[poi];
	int range = flag1 ? 9 : number[poi];
	int res = 0;
	for(int i=0; i<=range; ++i)
	{
		if(i == 4) continue;
		if(!flag2 && i==2) continue;
		res += dfs(poi-1, flag1 || i!=number[poi], i!=6);
	}
	if(flag1 && flag2) f[poi] = res;
	return res;
}

int calc(int x)
{
	if(!x) return 1;
	int top = 0;
	while(x) number[++top] = x%10, x /= 10;
	dfs(top, 0, 1);
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	mem(f, -1);
	int l, r;
	while(sf("%d%d", &l, &r), l&&r)
		pf("%d\n", calc(r) - calc(l-1));
	return 0;
}
