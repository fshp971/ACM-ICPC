#include<bits/stdc++.h>

using namespace std;

#define LL long long
#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define MP(a,b) make_pair(a,b)
#define pii pair<int,int>
#define sf scanf
#define pf printf

const int maxn = 20000;
const int max_dat = 100000;

int n, arr[maxn+5], lim;
LL dat[max_dat+5];
LL sml[maxn+5], smr[maxn+5];

inline int lowbit(int x){ return x & (-x); }

LL cal_sum(int x)
{
	LL res = 0;
	while(x > 0)
	{
		res += dat[x];
		x -= lowbit(x);
	}
	return res;
}

void add(int x, int del)
{
	while(x <= lim)
	{
		dat[x] += del;
		x += lowbit(x);
	}
}

void init()
{
	cin >> n;
	lim = 0;
	REP(i,1,n) sf("%d", arr+i), lim = max(lim, arr[i]);

	mem(dat, 0);
	for(int i=1;i<=n;++i)
	{
		sml[i] = cal_sum(arr[i]);
		add(arr[i], 1);
	}

	mem(dat, 0);
	for(int i=n;i>=1;--i)
	{
		smr[i] = cal_sum(arr[i]);
		add(arr[i], 1);
	}

	LL ans = 0;
	REP(i,1,n)
		ans += sml[i] * (n-i-smr[i]) + (i-1-sml[i]) * smr[i];
	cout << ans << "\n";
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int t;
	cin >> t;
	while(t--)
		init();
	return 0;
}
