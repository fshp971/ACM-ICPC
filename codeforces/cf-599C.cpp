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

const int maxn = 1e5;

int n;
int aa[maxn+5], bb[maxn+5];

multiset<int> Set;
multiset<int>::iterator it;

void init()
{
	sf("%d", &n);
	FOR(i,0,n)
	{
		sf("%d", aa+i);
		bb[i] = aa[i];
	}
	sort(bb, bb+n);
	int tot = 0, head = 0;
	FOR(i,0,n)
	{
		Set.insert(bb[i]);
		while(Set.count(aa[head]))
		{
			it = Set.find(aa[head]);
			Set.erase(it);
			++head;
		}
		if(head > i)
			++tot;
	}
	pf("%d\n", tot);
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	init();
	return 0;
}
