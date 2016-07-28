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

const int maxn = 1e5, maxN = 2*maxn, c_size = 128;

struct SuffixArray
{
	int len;
	int rank[maxN+5], sa[maxN+5];
	int tmp[maxN+5], cont[maxN+5];
	char ss[maxN+5];

	void build_sa(int m = c_size)
	{
		for(int i=0; i<m; ++i) cont[i] = 0;
		for(int i=0; i<len; ++i) ++cont[rank[i] = ss[i]];
		for(int i=1; i<m; ++i) cont[i] += cont[i-1];
		for(int i=len-1; i>=0; --i) sa[--cont[rank[i]]] = i;
		for(int k=1; k<=len; k<<=1)
		{
			int p = 0;
			//for(int i=len-k; i<len; ++i) tmp[p++] = i;
			//for(int i=0; i<len; ++i) if(sa[i]>=k) tmp[p++] = sa[i]-k;
			for(int i=0; i<len; ++i) if(sa[i]>=k) tmp[p++] = sa[i]-k;
			for(int i=len-k; i<len; ++i) tmp[p++] = i;
			for(int i=0; i<m; ++i) cont[i] = 0;
			for(int i=0; i<len; ++i) ++cont[rank[tmp[i]]];
			for(int i=1; i<m; ++i) cont[i] += cont[i-1];
			for(int i=len-1; i>=0; --i) sa[--cont[rank[tmp[i]]]] = tmp[i];
			swap(rank, tmp);
			p = 1; rank[sa[0]] = 0;
			for(int i=1; i<len; ++i)
				rank[sa[i]] = tmp[sa[i]] == tmp[sa[i-1]] && tmp[min(len,sa[i]+k)] == tmp[min(len,sa[i-1]+k)] ? p-1 : p++;
			if(p==len) break;
			//pf("len = %d, m = %d, p = %d\n", len, m, p);
			m = p;
		}
	}
}SA;

void init()
{
	int n;
	sf("%d%s", &n, SA.ss);
	for(int i=n; i<2*n; ++i) SA.ss[i] = SA.ss[i-n];
	SA.len = 2*n;
	SA.build_sa();
	int rank = 1<<30, ans = -1;
	for(int i=0; i<n; ++i)
		if(rank > SA.rank[i])
			rank = SA.rank[i], ans = i;
	pf("%d\n", ans);
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
