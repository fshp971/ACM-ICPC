#include<bits/stdc++.h>

using namespace std;

#define LL long long
#define MP(a,b) make_pair(a,b)
#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define pii pair<int,int>
#define sf scanf
#define pf printf

const int maxn = 100000;

int n;
int arr[maxn+5];

void init()
{
	cin >> n;
	REP(i,1,n) sf("%d", arr+i);
	sort(arr+1, arr+1+n);
	int now = 1;
	REP(i,1,n)
		if(now <= arr[i]) ++now;
	pf("%d\n",now);
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	init();
	return 0;
}
