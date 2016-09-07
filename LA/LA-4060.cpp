#include<bits/stdc++.h>

using namespace std;

#define LL long long
#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define pii pair<int,int>
#define MP(a,b) make_pair(a,b)
#define sf scanf
#define pf printf

const int maxn = 1e6;

int prime[maxn+5];

void prime_maker()
{
	char vis[maxn+5];
	mem(vis, 0);
	prime[prime[0]=1] = 2;
	for(int i=3; i<=maxn; i+=2) if(!vis[i])
	{
		prime[++prime[0]] = i;
		for(int k=i+i; k<=maxn; k+=i)
			vis[k] = 1;
	}
}

LL n;
int top, num[50], cont[50];
LL mul[50];

struct Node
{
	LL t1, t2, t3;
	Node(): t1(0), t2(0), t3(0){}
	Node(LL _t1, LL _t2, LL _t3)
	{
		t1 = _t1, t2 = _t2, t3 = _t3;
		if(t1 > t2) swap(t1, t2);
		if(t2 > t3) swap(t2, t3);
		if(t1 > t2) swap(t1, t2);
	}
	bool operator<(const Node &a)
	{
		if(t1 != a.t1) return t1 < a.t1;
		if(t2 != a.t2) return t2 < a.t2;
		return t3 < a.t3;
	}
	bool operator!=(const Node &a)
	{
		return t1!=a.t1 || t2!=a.t2 || t3!=a.t3;
	}
	void output()
	{
		pf("%lld %lld %lld\n", t1, t2, t3);
	}
}ans[1000000 * 6];
int ans_len;

void dfs2(int poi, LL *tt)
{
	if(tt[0]>maxn || tt[1]>maxn || tt[2]>maxn) return;
	if(!poi)
	{
		Node &des = ans[ans_len+1];
		des = Node(tt[0], tt[1], tt[2]);
		if(des.t1 == des.t2 || des.t2 == des.t3) return;
		if(des.t3 - des.t1 <= 25) ++ans_len;
		return;
	}
	if(!cont[poi])
	{
		dfs2(poi-1, tt);
		return;
	}
	LL tmp = 1;
	for(int i=1; i<cont[poi]; ++i)
	{
		tmp *= num[poi];
		//x10
		tt[0] *= mul[poi], tt[1] *= tmp;
		dfs2(poi-1, tt);
		//x01
		tt[1] /= tmp, tt[2] *= tmp;
		dfs2(poi-1, tt);
		//0x1
		tt[0] /= mul[poi], tt[1] *= mul[poi];
		dfs2(poi-1, tt);
		//1x0
		tt[0] *= tmp, tt[2] /= tmp;
		dfs2(poi-1, tt);
		//10x
		tt[1] /= mul[poi], tt[2] *= mul[poi];
		dfs2(poi-1, tt);
		//01x
		tt[0] /= tmp, tt[1] *= tmp;
		dfs2(poi-1, tt);
		//end
		tt[1] /= tmp, tt[2] /= mul[poi];
	}
	//100
	tt[0] *= mul[poi];
	dfs2(poi-1, tt);
	//110
	tt[1] *= mul[poi];
	dfs2(poi-1, tt);
	//101
	tt[1] /= mul[poi], tt[2] *= mul[poi];
	dfs2(poi-1, tt);
	//001
	tt[0] /= mul[poi];
	dfs2(poi-1, tt);
	//011
	tt[1] *= mul[poi];
	dfs2(poi-1, tt);
	//010
	tt[2] /= mul[poi];
	dfs2(poi-1, tt);
	//end
	tt[1] /= mul[poi];
	return;
}

void dfs(int poi, LL now)
{
	if(!poi)
	{
		if(now == n) return;
		for(int i=1; i<=top; ++i)
		{
			mul[i] = 1;
			for(int k=1; k<=cont[i]; ++k)
				mul[i] *= num[i];
		}
		LL tt[3];
		tt[0] = tt[1] = tt[2] = now;
		dfs2(top, tt);
		return;
	}
	for(int i=0; i<=cont[poi]; ++i)
	{
		cont[poi] -= i;
		dfs(poi-1, now);
		cont[poi] += i;
		now *= num[poi];
		if(now > 25) break;
	}
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	prime_maker();
	int T = 0;
	LL tmp;
	while(sf("%lld", &n), n)
	{
		pf("Scenario %d:\n", ++T);
		tmp = n;
		top = 0;
		for(int i=1; i<=prime[0] && prime[i]<=tmp; ++i)
		{
			if(tmp%prime[i] == 0)
			{
				num[++top] = prime[i], cont[top] = 0;
				while(tmp%prime[i] == 0)
					++cont[top], tmp /= prime[i];
			}
		}
		if(tmp > 1)
		{
			pf("Such bells don't exist\n");
			pf("\n");
			continue;
		}
		ans_len = 0;
		dfs(top, 1);
		if(!ans_len)
			pf("Such bells don't exist\n");
		else
		{
			sort(ans+1, ans+1+ans_len);
			ans[1].output();
			for(int i=2; i<=ans_len; ++i)
				if(ans[i] != ans[i-1])
					ans[i].output();
		}
		pf("\n");
	}
	return 0;
}
