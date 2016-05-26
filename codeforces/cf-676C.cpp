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

const int maxn = 100000;

int n,kk;

char arr[maxn+10];

void init()
{
	cin>>n>>kk;
	scanf("%s",arr);
	int head = 0, now = 0, ans = 0;
	FOR(i,0,n)
	{
		if(arr[i] == 'b')
		{
			if(now+1 > kk)
			{
				while(arr[head]!='b' && head<=i) ++head;
				if(head<=i && arr[head] == 'b') ++head;
			}
			else ++now;
		}
		ans = max(ans, i-head+1);
	}
	//printf("ans = %d\n",ans);

	head = now = 0;
	FOR(i,0,n)
	{
		if(arr[i] == 'a')
		{
			if(now+1 > kk)
			{
				while(arr[head]!='a' && head<=i) ++head;
				if(head<=i && arr[head] == 'a') ++head;
			}
			else ++now;
		}
		ans = max(ans, i-head+1);
	}
	cout<<ans<<"\n";
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	init();
	return 0;
}
