#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define MP(a,b) make_pair(a,b)
#define LL long long
#define pii pair<int,int>
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define sf scanf
#define pf printf

const int maxn = 750;

int n;

LL res[maxn+5], arr[maxn+5];

struct Node
{
	LL sum;
	int id;
	Node(LL sum, int id):sum(sum), id(id) {}
	bool operator<(const Node &a) const
	{ return sum > a.sum; }
};

void merge(LL *aa, LL *bb)
{
	priority_queue<Node> que;
	for(int i=1;i<=n;++i)
		que.push(Node(aa[i]+bb[1], 1));
	for(int i=1;i<=n;++i)
	{
		Node tmp = que.top();
		que.pop();
		aa[i] = tmp.sum;
		if(tmp.id < n)
		{
			++tmp.id;
			tmp.sum += bb[tmp.id] - bb[tmp.id-1];
			que.push(tmp);
		}
	}
	return;
}

void init()
{
	REP(i,1,n) sf("%lld", res+i);
	sort(res+1, res+1+n);
	for(int i=2;i<=n;++i)
	{
		REP(k,1,n) sf("%lld", arr+k);
		sort(arr+1, arr+1+n);
		merge(res, arr);
	}
	REP(i,1,n)
	{
		if(i > 1) pf(" ");
		pf("%lld", res[i]);
	}
	pf("\n");
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	while(~sf("%d", &n))
		init();
	return 0;
}
