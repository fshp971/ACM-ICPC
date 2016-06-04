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
#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define MP(a,b) make_pair(a,b)
#define pii pair<int,int>
#define sf scanf
#define pf printf

const int maxn = 300;

int gcd(int a,int b){ return b ? gcd(b,a%b) : a; }

int G[maxn+10][maxn+10];
int n,m;

LL init()
{
	LL res = 0;
	FOR(i,1,n) FOR(k,1,m)
	{
		int tmp = (n-i) * (m-k);
		if(G[i][k] == 1) res += tmp;
		else if(G[i][k] == 2) res -= tmp;
	}
	return res*2;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	REP(i,1,maxn) REP(k,1,maxn) G[i][k] = gcd(i,k);
	while(~scanf("%d%d",&n,&m))
	{
		if(!n && !m) break;
		cout << init() << "\n";
	}
	return 0;
}
