#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<queue>
#include<string>
#include<vector>
#include<utility>
#include<map>
#include<set>

using namespace std;

#define LL long long
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define pii pair<int,int>
#define mem(a,b) memset(a,b,sizeof(a))
#define MP(a,b) make_pair(a,b)
#define sf scanf
#define pf printf

const int maxn = 10000;

struct Node
{
	LL poi;
	int id;
	char type; //type = 1 means open seg, type = 2 means close seg
	Node(): poi(0), type(0), id(0){}
	Node(LL _poi, char _type, int _id){ poi = _poi, type = _type; id = _id; }
	bool operator<(const Node &a) const
	{
		if(poi != a.poi) return poi < a.poi;
		return type < a.type;
	}
}arr[maxn*6+5];
int top;

LL TA, TB, X;
LL dam[maxn*2+5];
int n, m;
char vis[maxn*2+5];

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	LL ai, aci, dai;
	LL ans, sum;
	int head;
	while(~sf("%lld%lld", &TA, &TB))
	{
		top = 0;
		sf("%lld", &X);
		TB = X+TB;
		//pf("X = %lld, TB = %lld\n", X, TB);
		sf("%d%d", &n, &m);
		sum = 0;
		REP(i,1,n)
		{
			sf("%lld%lld%lld", &ai, &aci, dam+i);
			if(ai+aci < X || ai+aci > TB) continue;
			LL l = ai+aci+aci;
			LL tmp = (TB+1-ai) / aci;
			if(tmp%2 == 0) ++tmp;
			if(tmp*aci + ai <= TB) tmp += 2;
			LL r = ai + (tmp-1) * aci;
			sum += dam[i];
			if(r-l > TA)
				continue;
			if(r<l) r = l;
			arr[++top] = Node(l, 1, i);
			arr[++top] = Node(r, 2, i);
		}
		REP(i,1,m)
		{
			sf("%lld%lld%lld", &ai, &aci, dam+n+i);
			LL l = ai+aci;
			LL tmp = (TB+1-ai) / aci;
			if(tmp%2 == 1) ++tmp;
			if(tmp*aci + ai <= TB) tmp += 2;
			LL r = ai + (tmp-1) * aci;
			sum += dam[n+i];
			if(r-l > TA)
				continue;
			//pf("l = %lld, r = %lld\n", l, r);
			if(r<l) r = l;
			arr[++top] = Node(l, 1, n+i);
			arr[++top] = Node(r, 2, n+i);
		}

		/*
		for(int i=1; i<=top; ++i)
		{
			pf("arr[%d]: poi = %lld, dam = %lld, type = %d, id = %d\n", i, arr[i].poi, dam[arr[i].id], arr[i].type, arr[i].id);
		}
		pf("\n----------------------------\n\n");
		*/

		sort(arr+1, arr+1+top);

		/*
		pf("X = %lld, TB = %lld\n", X, TB);
		pf("sum = %lld\n", sum);
		pf("top = %d\n", top);
		for(int i=1; i<=top; ++i)
		{
			pf("arr[%d]: poi = %lld, dam = %lld, type = %d, id = %d\n", i, arr[i].poi, dam[arr[i].id], arr[i].type, arr[i].id);
		}
		pf("\n----------------------------\n\n");
		*/

		ans = (LL)1 << 62;
		head = 1;
		mem(vis, 0);
		for(int i=1; i<=top; ++i)
		{
			while(head<i && arr[i].poi - arr[head].poi > TA)
			{
				if(arr[head].type == 1)
					sum += dam[arr[head].id];
				++head;
			}
			if(arr[i].type == 2)
				sum -= dam[arr[i].id];
			ans = min(ans, sum);
		}
		pf("%lld\n", ans);
		//pf("ans = %lld\n", ans);
	}
	return 0;
}
