#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<queue>
#include<string>
#include<utility>
#include<map>
#include<set>
#include<vector>

using namespace std;

#define LL long long
#define MP(a,b) make_pair(a,b)
#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define pii pair<int,int>
#define sf scanf
#define pf printf

const int MD = 1e9 + 7;
const int maxn = 100000;

map<int, int> wd;

void run()
{
	REP(i,0,9) wd[i+48] = i;
	REP(i,10,35) wd[i+55] = i;
	REP(i,36,61) wd[i+61] = i;
	wd['-'] = 62;
	wd['_'] = 63;
	return;
}

int n;
char arr[maxn+10];

int cal(int x)
{
	int res = 0;
	while(x>0)
	{
		if(x&1) ++res;
		x >>= 1;
	}
	return res;
}

void init()
{
	scanf("%s",arr);
	//printf("arr = %s\n",arr);
	n = strlen(arr);
	LL ans = 1;
	FOR(i,0,n)
	{
		int t = 6 - cal(wd[arr[i]]);
		ans *= pow(3,t);
		ans %= MD;
	}
	cout<<ans<<"\n";
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	run();
	init();
	return 0;
}
