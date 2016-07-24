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

const int maxn = 1e5;
const int maxnode = maxn*4;

int poi[maxn+5], inv_poi[(int)1e6 + 5];

struct Tree
{
	int dat[maxnode+5], ll[maxnode+5], rr[maxnode+5], del[maxnode+5];

	void build(int x, int l, int r)
	{
		ll[x] = l, rr[x] = r, dat[x] = 0, del[x] = 0;
		if(l+1 < r)
		{
			int mid = (l+r) >> 1;
			build(x*2, l, mid);
			build(x*2+1, mid, r);
		}
	}

	void maintain(int x, int delta)
	{
		del[x] += delta;
		dat[x] += (rr[x]-ll[x]) * delta;
	}

	void update(int x, int l, int r, int delta)
	{
		if(l == r) return;
		if(l<=ll[x] && rr[x]<=r)
			maintain(x, delta);
		else
		{
			int mid = (ll[x]+rr[x]) >> 1;
			if(del[x])
			{
				maintain(x*2, del[x]);
				maintain(x*2+1, del[x]);
				del[x] = 0;
			}
			if(l<mid) update(x*2, l, r, delta);
			if(r>mid) update(x*2+1, l, r, delta);
			dat[x] = dat[x*2] + dat[x*2+1];
			if(del[x*2] == del[x*2+1] && del[x*2])
			{
				del[x] = del[x*2];
				maintain(x*2, -del[x]);
				maintain(x*2+1, -del[x]);
			}
		}
	}

	int query(int x, double tar)
	{
		if(tar <= poi[ll[x]] || poi[rr[x]] <= tar) return 0;
		if(ll[x]+1 == rr[x]) return dat[x];
		int res = 0, mid = (ll[x]+rr[x]) >> 1;
		res += del[x];
		if(tar < poi[mid]) res += query(x*2, tar);
		else res += query(x*2+1, tar);
		return res;
	}
}tree1, tree2;


int fat[maxn+5], rangl[maxn+5], rangr[maxn+5], cont[maxn+5];
int arr[maxn+5];

int find_fat(int x){ return fat[x] == x ? x : fat[x] = find_fat(fat[x]); }

void init()
{
	int n, top = 0, que;
	char ord[5];
	sf("%d", &n);
	for(int i=1;i<=n;++i)
	{
		sf("%d%d", rangl+i, rangr+i);
		arr[i] = rangr[i], fat[i] = i;
	}
	sort(arr+1, arr+1+n);
	arr[0] = -1;
	for(int i=1;i<=n;++i)
		if(arr[i] != arr[i-1])
		{
			inv_poi[arr[i]] = (++top);
			poi[top] = arr[i];
		}
	for(int i=1;i<=n;++i)
		rangl[i] = rangr[i] = inv_poi[rangr[i]], cont[i] = 1;

	int a, b, u, v;
	double c;
	tree1.build(1,1,top); tree2.build(1,1,top);
	sf("%d", &que);
	for(int i=1;i<=que;++i)
	{
		sf("%s", ord);
		if(ord[0] == 'r')
		{
			sf("%d%d", &a, &b);
			u = find_fat(a+1), v = find_fat(b+1);
			if(u != v)
			{
				tree1.update(1,rangl[u], rangr[u], -1);
				tree2.update(1,rangl[u], rangr[u], -cont[u]);
				tree1.update(1,rangl[v], rangr[v], -1);
				tree2.update(1,rangl[v], rangr[v], -cont[v]);
				rangl[u] = min(rangl[u], rangl[v]);
				rangr[u] = max(rangr[u], rangr[v]);
				fat[v] = u, cont[u] += cont[v];
				tree1.update(1,rangl[u], rangr[u], 1);
				tree2.update(1,rangl[u], rangr[u], cont[u]);
			}
		}
		else
		{
			sf("%lf", &c);
			pf("%d %d\n",tree1.query(1,c), tree2.query(1,c));
		}
	}
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
