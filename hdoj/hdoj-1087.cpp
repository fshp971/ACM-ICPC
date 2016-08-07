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

#define lld I64d

const int maxn = 1000;

map<int, int> Map;

int n, top;
int aa[maxn+5], bb[maxn+5];
LL tree[maxn+5];

void add(int x, LL dat)
{
	//if(tree[x] > dat) return;
	for(; x<=top; x += x&(-x)) tree[x] = max(tree[x], dat);
}

LL query(int x)
{
	LL res = 0;
	for(; x; x -= x&(-x)) res = max(tree[x], res);
	return res;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	LL tmp;
	while(sf("%d", &n), n)
	{
		REP(i,1,n) sf("%d", aa+i), bb[i] = aa[i];
		sort(bb+1, bb+1+n);
		Map.clear();
		Map[0] = (top=1);
		REP(i,1,n) if(bb[i]>0 && !Map.count(bb[i])) Map[bb[i]] = (++top);
		mem(tree, 0);
		for(int i=1; i<=n; ++i)
		{
			if(aa[i]<=0) continue;
			tmp = query(Map[aa[i]]-1) + aa[i];
			add(Map[aa[i]], tmp);
		}
		pf("%lld\n", query(top));
	}
	return 0;
}
