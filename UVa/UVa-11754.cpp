//UVa-11754

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

const int maxc = 3000;
const int maxk = 100;

set<LL> G[maxc+10];

int cc,ss;
LL xx[maxc+10], kk[maxc+10];
LL mmp[maxc+10][maxk+10];

void ex_gcd(LL a, LL b, LL &g, LL &x, LL &y)
{
	if(!b){ g=a; x=1; y=0; }
	else{ ex_gcd(b,a%b,g,y,x); y -= x*(a/b); }
}

LL GRT(int len, LL *Ai, LL *Mi)
{
	LL M = 1, x, y, g, res = 0;
	REP(i,1,len) M *= Mi[i];
	REP(i,1,len)
	{
		LL tmp = M/Mi[i];
		ex_gcd(tmp,Mi[i],g,x,y);
		x = (x+Mi[i]) % Mi[i];
		res = (res+x*tmp*Ai[i]) % M;
	}
	return res;
}

LL aa[maxc+10];
vector<LL> sol;

void dfs(int dep)
{
	if(dep>cc)
	{
		sol.push_back(GRT(cc,aa,xx));
		return;
	}
	REP(i,1,kk[dep])
	{
		aa[dep] = mmp[dep][i];
		dfs(dep+1);
	}
}

void sol_china()
{
	sol.clear();
	dfs(1);
	sort(sol.begin(),sol.end());
	LL M = 1;
	REP(i,1,cc) M *= xx[i];
	for(int t=0;ss;++t)
	{
		for(int i=0;i<sol.size();++i)
		{
			LL n = M*t + sol[i];
			if(!n) continue;
			printf("%lld\n",n);
			if(--ss == 0) break;
		}
	}
	printf("\n");
}

void init()
{
	LL tot = 1;
	int key=-1;
	REP(i,1,cc)
	{
		scanf("%lld%lld",xx+i,kk+i);
		if(key==-1 || xx[i]*kk[key]>kk[i]*xx[key]) key = i;
		tot *= kk[i];
		G[i].clear();
		REP(k,1,kk[i])
		{
			scanf("%lld",&mmp[i][k]);
			G[i].insert(mmp[i][k]);
		}
		sort(mmp[i]+1,mmp[i]+1+kk[i]);
	}
	if(tot <= 10000)
	{
		sol_china();
		return;
	}
	for(int t=0;ss;++t)
	{
		for(int nt=1;nt<=kk[key];++nt)
		{
			LL n = t * xx[key] + mmp[key][nt];
			if(!n) continue;
			bool ok = true;
			REP(i,1,cc)
			{
				if(i==key) continue;
				LL tmp = n%xx[i];
				if(!G[i].count(tmp))
				{
					ok = false;
					break;
				}
			}
			if(ok)
			{
				printf("%lld\n",n); --ss;
				if(!ss) break;
			}
		}
	}
	printf("\n");
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	while(~scanf("%d%d",&cc,&ss))
	{
		if(!cc && !ss) break;
		init();
	}
	return 0;
}
