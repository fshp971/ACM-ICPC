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

const int max_len = 41;

LL ss, xx;
LL ans = 1, res = 0;
LL arr[70], sped[70];
int top, two;

void dfs(int now, LL sum)
{
	if(ss == sum)
	{
		++res;
		return;
	}
	if(sum>ss || now<1 || sum+sped[now]<ss) return;
	for(int i=now;i>=1;--i)
		dfs(i-1, sum+arr[i]);
	return;
}

void init()
{
	cin >> ss >> xx;
	two = ss==xx ? 2 : 0;
	ss -= xx;
	if(ss%2)
	{
		pf("0\n");
		return;
	}
	ss /= 2;
	//printf("ss = %lld\n",ss);
	top = 0;
	LL hehe = 1;
	sped[0] = 0;
	for(int i=0; i<=max_len; ++i)
	{
		if(xx & hehe) ans *= 2;
		else if(hehe <= ss)
		{
			arr[++top] = hehe;
			sped[top] = sped[top-1] + arr[top];
		}
		hehe *= 2;
	}
	/*printf("ans = %lld\n", ans);
	printf("top = %d\n", top);
	REP(i,1,top) pf("arr[%d] = %lld\n",i,arr[i]);*/
	dfs(top, 0);
	cout << ans*res - two << "\n";
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	init();
	return 0;
}
