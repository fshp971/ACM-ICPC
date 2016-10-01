#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<iostream>
#include<algorithm>
#include<string>
#include<queue>
#include<utility>
#include<map>
#include<set>
#include<bitset>
#include<vector>

using namespace std;

#define LL long long
#define mem(a,b) memset(a,b,sizeof(a))
#define MP make_pair
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define sf scanf
#define pf printf

const int maxn = 5e5;

int n, m;
LL lim, arr[maxn+5], temp[maxn+5];

bool check(int l, int r)
{
	if(r>n) return false;
	REP(i,l,r) temp[i] = arr[i];
	sort(temp+l, temp+r+1);
	LL res = 0;
	for(int i=l, j=r, tm=0; i<j && tm<m; ++i, --j, ++tm)
	{
		res += (temp[i]-temp[j]) * (temp[i]-temp[j]);
		if(res>lim) return false;
	}
	return true;
}

bool check2(int beg, int r, int len)
{
	LL res = 0;
	for(int i=beg, j=len, tm=m; i<j && tm; ++i, --j, --tm)
	{
		while(i<j && temp[i]>r) ++i;
		while(i<j && temp[j]>r) --j;
		if(i>=j) break;
		res += (arr[temp[i]]-arr[temp[j]]) * (arr[temp[i]]-arr[temp[j]]);
		if(res > lim) return false;
	}
	return true;
}

bool cmp(const int &a, const int &b)
{
	return arr[a] < arr[b];
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int T, ans, nex;
	sf("%d", &T);
	while(T--)
	{
		sf("%d%d%lld", &n, &m, &lim);
		REP(i,1,n) sf("%lld", arr+i);
		ans = 0;
		for(int i=1; i<=n; i=nex+1)
		{
			int k = 1;
			while(check(i, i+k-1))
				k <<= 1;
			k >>= 1;
			int l = i+k-1, r = min(n, i+k*2-1);
			int len = r;
			for(int t=i; t<=r; ++t)
				temp[t] = t;
			sort(temp+i, temp+1+r, cmp);
			while(l<=r)
			{
				int mid = (l+r)>>1;
				if(check2(i, mid, len))
					nex = mid, l = mid+1;
				else r = mid-1;
			}
			++ans;
		}
		pf("%d\n", ans);
	}
	return 0;
}
