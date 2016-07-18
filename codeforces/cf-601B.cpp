#include<bits/stdc++.h>

using namespace std;

#define LL long long
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define pii pair<int,int>
#define mem(a,b) memset(a,b,sizeof(a))
#define MP(a,b) make_pair(a,b)
#define sf scanf
#define pf printf

const int maxn = 1e5;

int n, que;
int aa[maxn+5], bb[maxn+5];
int arr[maxn+5];
int sta[maxn+5], poi[maxn+5], top;

void init()
{
	cin >> n >> que;
	REP(i,1,n) sf("%d", arr+i);
	REP(i,1,n-1) arr[i] = abs(arr[i+1] - arr[i]);

	arr[0] = 1<<30;

	sta[top=0] = 1<<30, poi[top] = 0;
	FOR(i,1,n)
	{
		aa[i] = i;
		int ll = 1, rr = top;
		while(ll <= rr)
		{
			int mid = (ll+rr) >> 1;
			if(sta[mid] <= arr[i])
			{
				aa[i] = poi[mid];
				rr = mid-1;
			}
			else ll = mid+1;
		}
		if(sta[top] > arr[i])
		{
			sta[++top] = arr[i];
			poi[top] = i;
		}
		else
		{
			while(sta[top] < arr[i]) --top;
			if(sta[top] > arr[i]) sta[++top] = arr[i];
		}
	}
	sta[top=0] = 1<<30, poi[top] = 0;
	for(int i=n-1; i>=1; --i)
	{
		bb[i] = i;
		int ll = 1, rr = top;
		while(ll <= rr)
		{
			int mid = (ll+rr) >> 1;
			if(sta[mid] < arr[i])
			{
				bb[i] = poi[mid];
				rr = mid-1;
			}
			else ll = mid+1;
		}
		if(sta[top] > arr[i])
		{
			sta[++top] = arr[i];
			poi[top] = i;
		}
		else
		{
			while(sta[top] < arr[i]) --top;
			if(sta[top] > arr[i]) sta[++top] = arr[i];
		}
	}
	/*for(int i=1;i<n;++i) pf("aa[%d] = %d\n", i, aa[i]);
	pf("\n");
	for(int i=1;i<n;++i) pf("bb[%d] = %d\n", i, bb[i]);
	pf("\n");*/
	REP(i,1,que)
	{
		int ll, rr;
		LL res = 0;
		sf("%d%d", &ll, &rr);
		FOR(k,ll,rr)
		{
			int ai = max(ll, aa[k]), bi = min(rr-1, bb[k]);
			res += (LL)(k-ai+1) * (LL)(bi-k+1) * arr[k];
		}
		pf("%lld\n", res);
	}
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	init();
	return 0;
}
