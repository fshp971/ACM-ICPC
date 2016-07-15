#include<bits/stdc++.h>

using namespace std;

#define LL long long
#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define MP(a,b) make_pair(a,b)
#define pii pair<int,int>
#define sf scanf
#define pf printf

struct Node
{
	int q_num, ti, period;
	
	void init(int a, int b){ q_num = a, ti = period = b; }
	bool operator<(const Node a) const
	{
		return ti != a.ti ? ti > a.ti : q_num > a.q_num;
	}
};

priority_queue<Node> que;

int n, kk;

void init()
{
	string ord;
	int a, b;
	while(cin >> ord, ord != "#")
	{
		sf("%d%d", &a, &b);
		Node tmp;
		tmp.init(a, b);
		que.push(tmp);
	}
	cin >> kk;
	FOR(i,0,kk)
	{
		Node tmp = que.top();
		que.pop();
		pf("%d\n", tmp.q_num);
		tmp.ti += tmp.period;
		que.push(tmp);
	}
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	init();
	return 0;
}
