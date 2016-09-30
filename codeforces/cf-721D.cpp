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

const int maxn = 200000;

struct Node
{
	LL dat;
	int sym, id;
	Node(): dat(0), sym(0){}
	Node(LL _dat, int _sym, int _id)
	{
		dat = _dat, sym = _sym, id = _id;
	}
	bool operator<(const Node &a)const
	{
		return dat > a.dat;
	}
};

priority_queue<Node> que;

int n, kk;
LL xx;
LL arr[maxn+5];

inline void output()
{
	for(int i=1; i<=n; ++i)
	{
		if(i>1) pf(" ");
		pf("%lld", arr[i]);
	}
	pf("\n");
}

void run(int type)
{
	Node tmp;
	while(kk)
	{
		--kk;
		tmp = que.top(); que.pop();
		if(type == 1)
			tmp.dat += xx;
		else tmp.dat -= xx;
		arr[tmp.id] = tmp.dat * tmp.sym;
		que.push(tmp);
	}
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	sf("%d%d%lld", &n, &kk, &xx);
	int cont1 = 0, cont2 = 0, zero = 0;
	int a;
	REP(i,1,n)
	{
		sf("%lld", arr+i);
		if(arr[i] < 0)
		{
			que.push( Node(abs(arr[i]),-1,i) );
			++cont1;
		}
		else if(arr[i] == 0)
		{
			que.push( Node(abs(arr[i]),0,i) );
			++zero;
		}
		else
		{
			que.push( Node(abs(arr[i]),1,i) );
			++cont2;
		}
	}
	Node tmp;
	if(zero)
	{
		if(kk < zero)
		{
			output();
			return 0;
		}
		if(cont1%2 == 0)
		{
			--zero, --kk;
			tmp = que.top(); que.pop();
			arr[tmp.id] = -xx;
			que.push( Node(xx, -1, tmp.id) );
		}
		while(zero)
		{
			--zero, --kk;
			tmp = que.top(); que.pop();
			arr[tmp.id] = xx;
			que.push( Node(xx, 1, tmp.id) );
		}
		run(1);
	}
	else
	{
		if(cont1%2)
			run(1);
		else
		{
			tmp = que.top(); que.pop();
			if(tmp.dat >= xx*kk)
			{
				que.push(tmp);
				run(2);
			}
			else
			{
				LL t = tmp.dat / xx;
				tmp.dat -= xx*t, kk -= t;
				if(tmp.dat>=0)
				{
					tmp.dat -= xx;
					--kk;
				}
				tmp.sym *= -1, tmp.dat *= -1;
				arr[tmp.id] = tmp.dat * tmp.sym;
				que.push(tmp);
				run(1);
			}
		}
	}
	output();
	return 0;
}
