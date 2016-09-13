#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<string>
#include<queue>
#include<vector>
#include<utility>
#include<map>
#include<set>
#include<bitset>

using namespace std;

#define LL long long
#define mem(a,b) memset(a,b,sizeof(a))
#define MP(a,b) make_pair(a,b)
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define sf scanf
#define pf printf

const int md = 1e9+7;
const int maxn = 2*1e5;

int n, key, cont;
int h[maxn+5], e[maxn*2+5], nex[maxn*2+5];
int fat[maxn+5];
char vis[maxn+5];

int sta[maxn+5], all[maxn+5], cyc[maxn+5];

int find_fat(int x){ return fat[x] == x ? x : fat[x] = find_fat(fat[x]); }

int dfs(int x, int pre)
{
	if(vis[x])
	{
		key = x;
		++cont;
		return 1;
	}
	vis[x] = 1;
	int type;
	for(int i=h[x]; i; i=nex[i])
	{
		if(e[i] == pre) continue;
		type = dfs(e[i], x);
		if(type == 2) return 2;
		if(type == 1)
		{
			if(key == x) return 2;
			++cont;
			return 1;
		}
	}
	return 0;
}

LL pow_mod(LL a, LL b)
{
	LL res = 1, tmp = a;
	while(b)
	{
		if(b&1) res = (res*tmp) % md;
		b >>= 1;
		tmp = (tmp*tmp) % md;
	}
	return res;
}

int main()
{
	int a, top = 0;
	sf("%d", &n);
	REP(i,1,n) fat[i] = i;
	REP(i,1,n)
	{
		sf("%d", &a);
		e[++top] = a, nex[top] = h[i], h[i] = top;
		e[++top] = i, nex[top] = h[a], h[a] = top;
		fat[find_fat(i)] = find_fat(a);
	}
	for(int i=1; i<=n; ++i)
	{
		++all[find_fat(i)];
		if(vis[find_fat(i)]) continue;
		sta[++sta[0]] = find_fat(i);
		key = cont = 0;
		dfs(find_fat(i), 0);
		cyc[find_fat(i)] = cont;
	}
	//pf("cont = %d\n", cont);
	LL ans = 1, tmp;
	REP(i,1,sta[0])
	{
		tmp = (pow_mod( 2, cyc[sta[i]] ) - 2 + md) % md;
		tmp = tmp * pow_mod( 2, all[sta[i]]-cyc[sta[i]] ) % md;
		ans = ans*tmp % md;
	}
	pf("%lld\n",ans);
	return 0;
}
