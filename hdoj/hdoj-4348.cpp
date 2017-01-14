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
int arr[maxn+5];
int rot[maxn+5], T_top[maxn+5];
int L[maxnode+5], R[maxnode+5];
LL sum[maxnode+5], delt[maxnode+5];

int build(int l, int r)
{
	int rt = top++;
	delt[rt] = 0;
	if(l == r)
		sum[rt] = arr[l];
	else
	{
		int mid = (l+r) >> 1;
		L[rt] = build(l, mid);
		R[rt] = build(mid+1, r);
		sum[rt] = sum[L[rt]] + sum[R[rt]];
	}
	return rt;
}

int update(int pre, int l, int r, int tl, int tr, int td)
{
	int rt = top++;
	L[rt] = L[pre], R[rt] = R[pre];
	sum[rt] = sum[pre], delt[rt] = delt[pre];
	if(tl<=l && r<=tr)
		delt[rt] += td;
	else
	{
		int mid = (l+r) >> 1;
		if(tl <= mid)
			L[rt] = update(L[rt], l, mid, tl, tr, td);
		if(mid+1 <= tr)
			R[rt] = update(R[rt], mid+1, r, tl, tr, td);
		sum[rt] = sum[L[rt]] + sum[R[rt]];
		sum[rt] += delt[L[rt]] * (mid-l+1);
		sum[rt] += delt[R[rt]] * (r-mid);
	}
	return rt;
}

LL query(int rt, int l, int r, int tl, int tr)
{
	LL res = delt[rt] * (tr-tl+1);
	if(tl<=l && r<=tr) res += sum[rt];
	else
	{
		int mid = (l+r) >> 1;
		if(tr<=mid)
			res += query(L[rt], l, mid, tl, tr);
		else if(mid+1<=tl)
			res += query(R[rt], mid+1, r, tl, tr);
		else
		{
			res += query(L[rt], l, mid, tl, mid);
			res += query(R[rt], mid+1, r, mid+1, tr);
		}
	}
	return res;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	char ord[5];
	int T, l, r, d, t;
	while(~sf("%d%d", &n, &m))
	{
		REP(i,1,n) sf("%d", arr+i);
		top = T = 0;
		rot[0] = build(1, n), T_top[0] = top;
		REP(i,1,m)
		{
			sf("%s", ord);
			if(ord[0] == 'C')
			{
				sf("%d%d%d", &l, &r, &d);
				++T;
				rot[T] = update(rot[T-1], 1, n, l, r, d);
				T_top[T] = top;
			}
			else if(ord[0] == 'Q')
			{
				sf("%d%d", &l, &r);
				pf("%lld\n", query(rot[T], 1, n, l, r));
			}
			else if(ord[0] == 'H')
			{
				sf("%d%d%d", &l, &r, &t);
				pf("%lld\n", query(rot[t], 1, n, l, r));
			}
			else //ord[0] == 'B'
			{
				sf("%d", &t);
				top = T_top[ T=t ];
			}
		}
	}
	return 0;
}
