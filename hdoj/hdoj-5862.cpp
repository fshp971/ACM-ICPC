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

struct Node 
{
	//type: 1 = begin point; 2 = segment; 3 = end point;
	int xx, yy, ll, rr, type;

	bool operator<(const Node &a)
	{
		if(xx != a.xx) return xx < a.xx;
		return type < a.type;
	}
}arr[maxn*2+2];

int n, top2;
map<int, int> axis2;

int top;
int tree[maxn*2+2];

void update(int x, int dat)
{
	for(; x <= top; x += x&(-x)) tree[x] += dat;
}

int query(int x)
{
	int res = 0;
	for(; x; x -= x&(-x)) res += tree[x];
	return res;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int T, a, b, c, d;
	LL ans;
	map<int, int>::iterator it2;
	sf("%d", &T);
	while(T--)
	{
		sf("%d", &n);
		top2 = 0;
		axis2.clear();
		REP(i,1,n)
		{
			sf("%d%d%d%d", &a, &b, &c, &d);
			if(a > c || b > d){ swap(a, c); swap(b, d); }
			if(a == c)
			{
				arr[++top2].type = 2;
				arr[top2].xx = a;
				arr[top2].ll = b, arr[top2].rr = d;
			}
			else
			{
				arr[++top2].type = 1;
				arr[top2].xx = a, arr[top2].yy = b;
				arr[++top2].type = 3;
				arr[top2].xx = c, arr[top2].yy = d;
			}
			axis2[b] = 1; axis2[d] = 1;
		}
		top = 0;
		for(it2 = axis2.begin(); it2 != axis2.end(); ++it2)
			it2->second = (++top);
		mem(tree, 0);
		sort(arr+1, arr+1+top2);
		ans = 0;
		for(int i=1; i<=top2; ++i)
		{
			if(arr[i].type == 1) update(axis2[arr[i].yy], 1);
			else if(arr[i].type == 3) update(axis2[arr[i].yy], -1);
			else ans += query(axis2[arr[i].rr]) - query(axis2[arr[i].ll]-1);
		}
		cout << ans << "\n";
	}
	return 0;
}
