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
const int maxnode = maxn << 5;

int n, m, top;
int arr[maxn+5], Hash[maxn+5], rot[maxn+5];
int L[maxnode+5], R[maxnode+5], sum[maxnode+5];

int build(int l, int r)
{
	int rt = ++top;
	sum[rt] = 0;
	if(l<r)
	{
		int mid = (l+r) >> 1;
		L[rt] = build(l, mid);
		R[rt] = build(mid+1, r);
	}
	return rt;
}

int update(int pre, int l, int r, int rank)
{
	int rt = ++top;
	sum[rt] = sum[pre]+1, L[rt] = L[pre], R[rt] = R[pre];
	if(l<r)
	{
		int mid = (l+r) >> 1;
		if(rank <= mid) L[rt] = update(L[rt], l, mid, rank);
		else R[rt] = update(R[rt], mid+1, r, rank);
	}
	return rt;
}

int query(int &rt1, int &rt2, int l, int r, int &rank)
{
	if(rank >= r) return sum[rt2]-sum[rt1];
	int mid = (l+r) >> 1;
	int res = query(L[rt1], L[rt2], l, mid, rank);
	if(mid+1 <= rank)
		res += query(R[rt1], R[rt2], mid+1, r, rank);
	return res;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int T, tot, l, r, h;
	sf("%d", &T);
	for(int t=1; t<=T; ++t)
	{
		pf("Case %d:\n", t);
		sf("%d%d", &n, &m);
		REP(i,1,n) sf("%d", arr+i), Hash[i] = arr[i];
		sort(Hash+1, Hash+1+n);
		tot = unique(Hash+1, Hash+1+n) - (Hash+1);
		top = 0;
		rot[0] = build(1, tot);
		REP(i,1,n)
			rot[i] = update(rot[i-1], 1, tot, lower_bound(Hash+1, Hash+1+tot, arr[i]) - Hash);
		REP(i,1,m)
		{
			sf("%d%d%d", &l, &r, &h);
			++l, ++r;
			if(h<Hash[1]) { pf("0\n"); continue; }
			if(h>Hash[tot]) { pf("%d\n", r-l+1); continue; }
			int rank = lower_bound(Hash+1, Hash+1+tot, h) - Hash;
			if(h < Hash[rank]) --rank;
			int res = query(rot[l-1], rot[r], 1, tot, rank);
			pf("%d\n", res);
		}
	}
	return 0;
}
