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

const int maxn = 50000, maxm = 10000;
const int maxnode = (maxn+maxm) << 5;

int n, m, tot, range;
int arr[maxn+5], Hash[maxn+maxm+5];
int rot[maxn+5], suf[maxn+5];
int sum[maxnode+5], L[maxnode+5], R[maxnode+5];
int used[maxn+5]; 

struct Que
{
	char ord;
	int l, r, kk;
}que[maxm+5];

int build(int l, int r)
{
	int rt = tot++;
	sum[rt] = 0;
	if(l<r)
	{
		int mid = (l+r) >> 1;
		L[rt] = build(l, mid);
		R[rt] = build(mid+1, r);
	}
	return rt;
}

int update(int pre, int l, int r, int rank, int del)
{
	int rt = tot++;
	sum[rt] = sum[pre]+del, L[rt] = L[pre], R[rt] = R[pre];
	if(l<r)
	{
		int mid = (l+r) >> 1;
		if(rank <= mid)
			L[rt] = update(L[pre], l, mid, rank, del);
		else R[rt] = update(R[pre], mid+1, r, rank, del);
	}
	return rt;
}

void Add(int x, int rank, int del)
{
	for(; x <= n; x += x&(-x))
		suf[x] = update(suf[x], 1, range, rank, del);
}

int Sum(int x)
{
	int res = 0;
	for(; x; x -= x&(-x))
		res += sum[L[used[x]]];
	return res;
}

int query(int suf1, int suf2, int rt1, int rt2, int l, int r, int kk)
{
	if(l == r) return l;
	int tmp = sum[L[rt2]]-sum[L[rt1]] + Sum(suf2)-Sum(suf1);
	int mid = (l+r) >> 1;
	if(kk<=tmp)
	{
		for(int i = suf2; i; i -= i&(-i))
			used[i] = L[used[i]];
		for(int i = suf1; i; i -= i&(-i))
			used[i] = L[used[i]];
		return query(suf1, suf2, L[rt1], L[rt2], l, mid, kk);
	}
	else
	{
		for(int i = suf2; i; i -= i&(-i))
			used[i] = R[used[i]];
		for(int i = suf1; i; i -= i&(-i))
			used[i] = R[used[i]];
		return query(suf1, suf2, R[rt1], R[rt2], mid+1, r, kk-tmp);
	}
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int T;
	char oord[4];
	sf("%d", &T);
	while(T--)
	{
		sf("%d%d", &n, &m);
		range = 0;
		REP(i,1,n)
			sf("%d", arr+i), Hash[++range] = arr[i];
		REP(i,1,m)
		{
			sf("%s", oord);
			if(oord[0] == 'Q')
				sf("%d%d%d", &que[i].l, &que[i].r, &que[i].kk), que[i].ord = oord[0];
			else
				sf("%d%d", &que[i].l, &que[i].r), que[i].ord = oord[0], Hash[++range] = que[i].r;
		}
		sort(Hash+1, Hash+1+range);
		range = unique(Hash+1, Hash+1+range) - (Hash+1);
		tot = 0;
		suf[0] = rot[0] = build(1, range);
		REP(i,1,n)
		{
			suf[i] = rot[0];
			rot[i] = update(rot[i-1], 1, range, lower_bound(Hash+1, Hash+1+range, arr[i]) - Hash, 1);
		}
		REP(i,1,m)
		{
			if(que[i].ord == 'Q')
			{
				for(int k = que[i].l-1; k; k -= k&(-k))
					used[k] = suf[k];
				for(int k = que[i].r; k; k -= k&(-k))
					used[k] = suf[k];
				int id = query(que[i].l-1, que[i].r, rot[que[i].l-1], rot[que[i].r], 1, range, que[i].kk);
				pf("%d\n", Hash[id]);
			}
			else
			{
				Add(que[i].l, lower_bound(Hash+1, Hash+1+range, arr[que[i].l]) - Hash, -1);
				arr[que[i].l] = que[i].r;
				Add(que[i].l, lower_bound(Hash+1, Hash+1+range, arr[que[i].l]) - Hash, 1);
			}
		}
	}
	return 0;
}
