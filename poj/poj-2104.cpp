#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<queue>
#include<string>
#include<vector>
#include<utility>
#include<map>
#include<set>

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
const int maxnode = maxn<<5;

int n, m, arr[maxn+5];
int tot, Hash[maxn+5], rot[maxn+5];
int L[maxnode+5], R[maxnode+5], sum[maxnode+5];

inline int getint()
{
	char c;
	while(c=getchar(), c<'0' || c>'9');
	int x = c-48;
	while(c=getchar(), c>='0' && c<='9')
		x = x*10 + c-48;
	return x;
}

int build(int l, int r)
{
	int rt = tot++;
	sum[rt] = 0;
	if(l < r)
	{
		int mid = (l+r) >> 1;
		L[rt] = build(l, mid);
		R[rt] = build(mid+1, r);
	}
	return rt;
}

int update(int &pre, int l, int r, int &key)
{
	int rt = tot++;
	sum[rt] = sum[pre]+1, L[rt] = L[pre], R[rt] = R[pre];
	if(l<r)
	{
		int mid = (l+r) >> 1;
		if(key <= Hash[mid])
			L[rt] = update(L[pre], l, mid, key);
		else R[rt] = update(R[pre], mid+1, r, key);
	}
	return rt;
}

int query(int &rt1, int &rt2, int l, int r, int rank)
{
	if(l == r) return l;
	int mid = (l+r) >> 1, tmp = sum[L[rt2]] - sum[L[rt1]];
	if(rank <= tmp)
		return query(L[rt1], L[rt2], l, mid, rank);
	else return query(R[rt1], R[rt2], mid+1, r, rank-tmp);
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	//sf("%d%d", &n, &m);
	n = getint(), m = getint();
	REP(i,1,n) sf("%d", arr+i), Hash[i] = arr[i];
	sort(Hash+1, Hash+1+n);
	int range = unique(Hash+1, Hash+1+n) - (Hash+1);
	tot = 0;
	rot[0] = build(1, range);
	REP(i,1,n) rot[i] = update(rot[i-1], 1, range, arr[i]);
	int l, r, kk;
	REP(i,1,m)
	{
		//sf("%d%d%d", &l, &r, &kk);
		l = getint(), r = getint(), kk = getint();
		int id = query(rot[l-1], rot[r], 1, range, kk);
		pf("%d\n", Hash[id]);
	}
	return 0;
}
