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

const int maxn = 100000;

int head;
string opt[maxn*10+10];
int num[maxn*10+10];

int n, top;
int tree[maxn*10+10];

void up(int x)
{
	while(x>1)
	{
		int t = x>>1;
		if(tree[x] < tree[t])
		{
			swap(tree[x], tree[t]);
			swap(x, t);
		}
		else break;
	}
}

void down(int x)
{
	while(x*2 <= top)
	{
		int t = x*2;
		if(t<top && tree[t+1]<tree[t]) ++t;
		if(tree[x] > tree[t])
		{
			swap(tree[x], tree[t]);
			swap(x, t);
		}
		else break;
	}
}

void init()
{
	cin >> n;
	top = head = 0;
	int tmp;
	string ord;
	REP(i,1,n)
	{
		cin >> ord;
		if(ord == "removeMin")
		{
			if(!top)
			{
				opt[++head] = "insert";
				num[head] = 1;
			}
			else
			{
				tree[1] = tree[top--];
				down(1);
			}
			opt[++head] = ord;
		}
		else if(ord == "insert")
		{
			sf("%d", &tmp);
			opt[++head] = ord;
			num[head] = tmp;
			tree[++top] = tmp; up(top);
		}
		else
		{
			sf("%d", &tmp);
			while(top && tmp>tree[1])
			{
				opt[++head] = "removeMin";
				tree[1] = tree[top--];
				down(1);
			}
			if(top==0 || tree[1] > tmp)
			{
				opt[++head] = "insert";
				num[head] = tmp;
				tree[++top] = tmp; up(top);
			}
			opt[++head] = ord; num[head] = tmp;
		}
	}

	cout << head << "\n";
	REP(i,1,head)
	{
		if(opt[i] == "removeMin") cout << opt[i] << "\n";
		else cout << opt[i] << " " << num[i] << "\n";
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
