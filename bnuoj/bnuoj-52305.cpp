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
#define pii pair<int,int>
#define MP make_pair
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define sf scanf
#define pf printf

const int maxn = 1e5;
const int maxm = 2e6;
const int md = 1e9+7;

struct Node
{
	LL ans;
	int sum;
}tree[maxn+5];

int n;
int h[maxn+5], e[maxn*2+5], cc[maxn*2+5], nex[maxn*2+5];
LL jie[maxm+5], _inv_jie[maxm+5];

inline void update(LL &x){ if(x>=md) x %= md; }

LL pow_mod(LL a, LL b)
{
	LL res = 1;
	while(b)
	{
		if(b&1) res *= a, update(res);
		b >>= 1;
		a *= a, update(a);
	}
	return res;
}

inline LL inv_jie(int x)
{
	return _inv_jie[x] == -1 ? _inv_jie[x] = pow_mod(jie[x], md-2) : _inv_jie[x];
}

LL C(int cn, int cm)
{
	LL res = jie[cn] * inv_jie(cm);
	update(res);
	res *= inv_jie(cn-cm), update(res);
	return res;
}

void init()
{
	mem(_inv_jie, -1);
	jie[0] = 1;
	for(int i=1; i<=maxm; ++i)
		jie[i] = jie[i-1] * i, update(jie[i]);
}

LL dfs(int x, int fa)
{
	tree[x].ans = 1, tree[x].sum = 0;
	for(int i=h[x]; i; i=nex[i])
	{
		if(fa == e[i]) continue;
		tree[x].ans *= dfs(e[i], x), update(tree[x].ans);
		tree[x].ans *= C(cc[i]+tree[e[i]].sum-1, tree[e[i]].sum), update(tree[x].ans);
		tree[x].ans *= inv_jie(cc[i]), update(tree[x].ans);
		tree[x].sum += cc[i];
	}
	tree[x].ans *= jie[tree[x].sum];
	update(tree[x].ans);
	return tree[x].ans;
}

int main()
{
	init();
	int top = 0, u, v, ci;
	LL ans = 1;
	sf("%d", &n);
	FOR(i,1,n)
	{
		sf("%d%d%d", &u, &v, &ci);
		e[++top] = v, cc[top] = ci, nex[top] = h[u], h[u] = top;
		e[++top] = u, cc[top] = ci, nex[top] = h[v], h[v] = top;
		ans *= jie[2*ci], update(ans);
	}
	ans *= dfs(1, 0), update(ans);
	cout << ans << "\n";
	return 0;
}
