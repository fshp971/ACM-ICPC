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

#define LL long long
#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define pii pair<int,int>
#define sf scanf
#define pf printf

const int md = 1e9+7;
const int maxn = 1e5;

LL ans[maxn+5], tot;
LL twf[maxn+5], jie[maxn+5], inv_jie[maxn+5];
char arr[maxn+5];

struct Node
{
	int n, id;
	Node(int _n, int _id) { n = _n, id = _id; }
};
bool operator<(const Node &a, const Node &b) { return a.n < b.n; }

vector<Node> G[maxn+5];

LL pow_mod(LL a, LL b)
{
	LL res = 1;
	while(b)
	{
		if(b&1) res = res*a % md;
		a = a*a % md, b >>= 1;
	}
	return res;
}

LL C(int n, int m)
{
	return jie[n] * inv_jie[m] % md * inv_jie[n-m] % md;
}

int main()
{
	twf[0] = jie[0] = inv_jie[0] = 1;
	REP(i,1,maxn)
	{
		twf[i] = twf[i-1]*25 % md;
		jie[i] = jie[i-1]*i % md;
		inv_jie[i] = pow_mod(jie[i], md-2);
	}
	int n, m, T, ord;
	tot = 0;
	sf("%d", &T);
	sf("%s", arr);
	m = strlen(arr);
	REP(i,1,T)
	{
		sf("%d", &ord);
		if(ord == 1)
		{
			sf("%s", arr);
			m = strlen(arr);
		}
		else
		{
			sf("%d", &n);
			G[m].push_back( Node(n, ++tot) );
		}
	}
	REP(_m,1,maxn)
	{
		if(!G[_m].size()) continue;
		sort(G[_m].begin(), G[_m].end());
		int len = _m;
		LL tmp = 1;
		for(int i=0; i<G[_m].size(); ++i)
		{
			while(len < G[_m][i].n)
			{
				tmp = tmp*26 % md + C(len,_m-1)*twf[len+1-_m] % md;
				tmp %= md, ++len;
			}
			if(G[_m][i].n < _m)
				ans[G[_m][i].id] = 0;
			else ans[G[_m][i].id] = tmp;
		}
	}
	REP(i,1,tot)
		pf("%lld\n", ans[i]);
	return 0;
}
