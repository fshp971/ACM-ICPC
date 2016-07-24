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

int n, cnt[70];
char arr[maxn+5];

inline int c_id(char c)
{
	if('a'<=c && c<='z') return c - 'a';
	return c - 'A' + 26;
}

void init()
{
	sf("%d%s", &n, arr);
	int head = 0, ans = n;
	mem(cnt, 0);
	FOR(i,0,n)
	{
		int t = c_id(arr[i]);
		//pf("t = %d\n", t);
		if(!cnt[t])
			ans = i-head+1;
		++cnt[t];
		while(cnt[t = c_id(arr[head])] > 1) --cnt[t], ++head;
		ans = min(ans, i-head+1);
		//pf("head = %d, i = %d, ans = %d\n", head, i, ans);
	}
	pf("%d\n", ans);
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	init();
	return 0;
}
