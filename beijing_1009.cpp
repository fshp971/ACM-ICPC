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
	LL poi, dam;
	char type; //type = 1 means open seg, type = 2 means close seg
	Node(): poi(0), dam(0), type(0){}
	Node(LL _poi, LL _dam, char _type){ poi = _poi, dam = _dam, type = _type; }
	bool operator<(const Node &a) const
	{
		if(poi != a.poi) return poi < a.poi;
		return type < a.type;
	}
}arr[maxn*6+5];
int top;

LL TA, TB, X;
int n, m;

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
			sf("%lld%lld%lld", &ai, &aci, &dai);
			if(ai+aci < X || ai+aci > TB) continue;
			LL l = ai+aci+aci;
			LL tmp = (TB+1-ai) / aci;
			if(tmp%2 == 0) ++tmp;
			if(tmp*aci + ai <= TB) tmp += 2;
			//pf("i = %d, tmp = %lld\n", i, tmp);
			LL r = ai + (tmp-1) * aci;
			sum += dai;
			if(r-l > TA)
				continue;
			arr[++top] = Node(l, -dai, 1);
			arr[++top] = Node(r, dai, 2);
		}
		REP(i,1,m)
		{
			sf("%lld%lld%lld", &ai, &aci, &dai);
			LL l = ai+aci;
			LL tmp = (TB+1-ai) / aci;
			if(tmp%2 == 1) ++tmp;
			if(tmp*aci + ai <= TB) tmp += 2;
			LL r = ai + (tmp-1) * aci;
			sum += dai;
			if(r-l > TA)
				continue;
			arr[++top] = Node(l, -dai, 1);
			arr[++top] = Node(r, dai, 2);
		}
		sort(arr+1, arr+1+top);

		/*
		pf("sum = %lld\n", sum);

		pf("top = %d\n", top);
		for(int i=1; i<=top; ++i)
		{
			pf("arr[%d]: poi = %lld, dam = %lld, type = %d\n", i, arr[i].poi, arr[i].dam, arr[i].type);
		}
		pf("\n----------------------------\n\n");
		*/

		ans = (LL)1 << 62;
		head = 1;
		for(int i=1; i<=top; ++i)
		{
			if(arr[i].type == 1)
			{
				sum += arr[i].dam;
				while(i<=top && arr[i+1].poi == arr[i].poi && arr[i+1].type == 1)
					sum += arr[++i].dam;
			}

			while(head<i && arr[i].poi-arr[head].poi > TA)
			{
				if(arr[head].type == 2)
					sum += arr[head].dam;
				++head;
			}

			if(arr[i].poi >= TA)
				ans = min(ans, sum);

			while(i<=top && arr[i+1].poi == arr[i].poi)
				++i;
		}
		//pf("after: sum = %lld\n", sum);
		ans = min(ans, sum);
		for(; head<=top; ++head)
		{
			if(arr[head].type == 2)
				sum += arr[head].dam;
			ans = min(ans, sum);
		}
		ans = min(ans, sum);
		pf("%lld\n", ans);
		//pf("ans = %lld\n", ans);
	}
	return 0;
}
