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

const int maxn = 100000;

int calc(int n, int *xx, int pp)
{
	if(!n) return 0;
	if(pp <= xx[0]) return xx[n-1] - pp;
	if(pp >= xx[n-1]) return pp - xx[0];
	int len = xx[n-1] - xx[0];
	return min(pp-xx[0], xx[n-1]-pp) + len;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int n, aa, xx[maxn+5];
	sf("%d%d", &n, &aa);
	FOR(i,0,n) sf("%d", xx+i);
	sort(xx, xx+n);
	pf("%d\n", min( calc(n-1,xx,aa), calc(n-1,xx+1,aa) ));
	return 0;
}
