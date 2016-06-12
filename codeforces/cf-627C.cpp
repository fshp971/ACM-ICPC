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

const int maxm = 200000;

int n, dis, m;

map<int, int> Map;
map<int, int>::iterator it;

pii gas[maxm+10];

void init()
{
	cin >> dis >> n >> m;
	REP(i,1,m)
		sf("%d%d", &gas[i].first, &gas[i].second);
	sort(gas+1, gas+1+m);
	Map[0] = n;
	LL ans = 0;
	gas[0].first = 0; gas[m+1].first = dis;
	REP(i,1,m+1)
	{
		int del = gas[i].first - gas[i-1].first;
		int tmp = del;
		if(del > n){ pf("-1\n"); return; }
		while(del)
		{
			it = Map.begin();
			if(del >= it->second)
			{
				del -= it->second;
				ans += (LL)it->first * it->second;
				Map.erase(it);
			}
			else
			{
				ans += (LL)it->first * del;
				it->second -= del;
				del = 0;
			}
		}
		if(i == m+1) break;
		if(!Map.count(gas[i].second)) Map[gas[i].second] = tmp;
		else Map[gas[i].second] += tmp;
		while(1)
		{
			it = Map.end(); --it;
			if(it->first <= gas[i].second) break;
			Map[gas[i].second] += it->second;
			Map.erase(it);
		}
	}
	cout << ans << "\n";
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	init();
	return 0;
}
