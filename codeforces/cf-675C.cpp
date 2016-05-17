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

map<LL,int> Map;

int n,arr[100010];

void init()
{
	LL sum=0;
	cin>>n;
	REP(i,1,n)
	{
		scanf("%d",arr+i);
		sum += arr[i];
		if(!Map.count(sum)) Map[sum] = 1;
		else ++Map[sum];
	}
	int ans = 0;
	for(map<LL,int>::iterator it = Map.begin(); it != Map.end(); ++it)
		ans = max(ans, it->second);
	cout<<n-ans<<"\n";
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	init();
	return 0;
}
