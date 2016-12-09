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
const int maxnode = (maxn<<5);

int n, m, arr[maxn+5], Hash[maxn+5];
int tot, rot[maxn+5];
int L[maxnode+5], R[maxnode+5], sum[maxnode+5];

void build(int l, int r, int &rt)
{
	rt = tot++, sum[rt] = 0;
	if(l<r)
	{
		int mid = (l+r) >> 1;
		build(l, mid, L[rt]);
		build(mid+1, r, R[rt]);
	}
}

void update(int l, int r, int &rt, int &pre, int &key)
{
	rt = tot++, sum[rt] = sum[pre]+1;
	L[rt] = L[pre], R[rt] = R[pre];
	if(l<r)
	{
		int mid = (l+r) >> 1;
		if(key <= Hash[mid])
			update(l, mid, L[rt], L[pre], key);
		else update(mid+1, r, R[rt], R[pre], key);
	}
}

int query(int l, int r, int &rt1, int &rt2, int rank)
{
	if(l == r) return l;
	int mid = (l+r) >> 1, tmp;
	tmp = sum[L[rt2]] - sum[L[rt1]];
	if(rank <= tmp)
		return query(l, mid, L[rt1], L[rt2], rank);
	else return query(mid+1, r, R[rt1], R[rt2], rank-tmp);
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int T, range, l, r, kk;
	sf("%d", &T);
	while(T--)
	{
		sf("%d%d", &n, &m);
		REP(i,1,n) sf("%d", arr+i), Hash[i] = arr[i];
		sort(Hash+1, Hash+1+n);
		range = unique(Hash+1, Hash+1+n) - (Hash+1);
		tot = 0;
		build(1, range, rot[0]);
		REP(i,1,n) update(1, range, rot[i], rot[i-1], arr[i]);
		REP(i,1,m)
		{
			sf("%d%d%d", &l, &r, &kk);
			int id = query(1, range, rot[l-1], rot[r], kk);
			pf("%d\n", Hash[id]);
		}
	}
	return 0;
}
