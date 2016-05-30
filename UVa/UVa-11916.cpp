#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<cctype>
#include<iostream>
#include<algorithm>
#include<queue>
#include<string>
#include<utility>
#include<map>
#include<set>
#include<vector>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define MP(a,b) make_pair(a,b)
#define LL long long
#define pii pair<int,int>
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)

const int MD = 100000007;

int n,m,kk,B,R;

set< pii > ndset;

LL mul_mod(LL a, LL b)
{
	LL res = a*b;
	return res < MD ? res : res%MD;
}

LL pow_mod(LL a, LL b)
{
	LL res = 1, tmp=a;
	while(b>0)
	{
		if(b&(LL)1) res = mul_mod(res, tmp);
		b >>= 1;
		tmp = mul_mod(tmp, tmp);
	}
	return res;
}

int log_mod(int a, LL b)
{
	//printf("a = %d, b = %lld\n",a, b);
	int len = sqrt(MD) + 1;
	LL tmp = 1;
	LL vv = pow_mod(pow_mod(a,len), MD-2);
	map<LL, int> shank;
	FOR(i,0,len)
	{
		if(!shank.count(tmp)) shank[tmp] = i;
		tmp = mul_mod(tmp, a);
	}
	FOR(i,0,len)
	{
		if(shank.count(b)) return (LL)i*len + shank[b];
		b = mul_mod(b,vv);
	}
}

LL cal()
{
	int sum = m;
	for(set< pii >::iterator it = ndset.begin(); it != ndset.end(); ++it)
	{
		if(it->first == 1) --sum;
		if(it->first + 1 > n) continue;
		if(!ndset.count( MP(it->first+1, it->second) )) ++sum;
	}
	//printf("sum = %d\n",sum);
	LL t1 = pow_mod(kk, sum);
	LL t2 = pow_mod(kk-1, (LL)n*m - B - sum);
	//printf("t1 = %lld, t2 = %lld\n",t1, t2);
	LL hehe = (LL)n*m - B - sum;
	//printf("hehe = %lld\n",hehe);
	return mul_mod( pow_mod(kk, sum), pow_mod(kk-1, (LL)n*m - B - sum) );
}

int init()
{
	int x, y, cont;
	cin>>m>>kk>>B>>R;
	ndset.clear();
	n = 1;
	cont = 0;
	for(int i=1;i<=B;++i)
	{
		scanf("%d%d",&x,&y);
		if(x > n)
		{
			n = x; cont = 1;
		}
		else if(x==n) ++cont;
		ndset.insert( MP(x, y) );
	}
	LL res = cal();
	//printf("res = %lld\n",res);
	if(res == R) return n;
	res = mul_mod(res, mul_mod(pow_mod(kk, cont), pow_mod(kk-1, m-cont)) );
	//printf("res = %lld\n",res);
	if(res == R) return n+1;
	//printf("res^-1 = %lld\n",pow_mod(res, 5));
	return n+1 + log_mod(pow_mod(kk-1, m), mul_mod(R, pow_mod(res, MD-2)));
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int t;
	cin>>t;
	for(int i=1;i<=t;++i)
		printf("Case %d: %d\n",i,init());
	return 0;
}
