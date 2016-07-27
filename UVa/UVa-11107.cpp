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

const int maxn = 101 * 1000, c_size = 150;

struct SuffixArray
{
	int len;
	int sa[maxn+5], rank[maxn+5], cont[maxn+5], tmp[maxn+5];
	int height[maxn+5], type[maxn+5];
	char ss[maxn+5];

	void clear()
	{
		len = 0;
		mem(ss, 0);
	}
	
	void build_sa(int m = c_size)
	{
		for(int i=0; i<m; ++i) cont[i] = 0;
		for(int i=0; i<len; ++i) ++cont[rank[i] = ss[i]];
		for(int i=1; i<m; ++i) cont[i] += cont[i-1];
		for(int i=len-1; i>=0; --i) sa[--cont[rank[i]]] = i;
		for(int k=1; k<=len; k<<=1)
		{
			int p = 0;
			for(int i=len-k; i<len; ++i) tmp[p++] = i;
			for(int i=0; i<len; ++i) if(sa[i]>=k) tmp[p++] = sa[i]-k;
			for(int i=0; i<m; ++i) cont[i] = 0;
			for(int i=0; i<len; ++i) ++cont[rank[tmp[i]]];
			for(int i=1; i<m; ++i) cont[i] += cont[i-1];
			for(int i=len-1; i>=0; --i) sa[--cont[rank[tmp[i]]]] = tmp[i];
			swap(rank, tmp);
			p = 1, rank[sa[0]] = 0;
			for(int i=1; i<len; ++i)
				rank[sa[i]] = tmp[sa[i]] == tmp[sa[i-1]] && tmp[min(len, sa[i]+k)] == tmp[min(len, sa[i-1]+k)] ? p-1 : p++;
			if(p == len) break;
			m = p;
		}
	}

	void build_height()
	{
		int k = 0, j;
		for(int i=0; i<len; ++i)
		{
			if(k) k--;
			if(rank[i] == 0)
			{
				height[rank[i]] = (k=0);
				continue;
			}
			//if(rank[i] == 0) pf("true\n");
			//pf("sa[%d] = %d\n", rank[i]-1, sa[rank[i]-1]);
			j = sa[rank[i]-1];
			while(ss[i+k] == ss[j+k]) ++k;
			height[rank[i]] = k;
		}
		height[len] = -1;
	}

	/*void output()
	{
		for(int i=0; i<=len; ++i)
			pf("height[%d] = %d, type[%d] = %d, rank[%d] = %d, sa[%d] = %d\n", i, height[i], i, type[i], i, rank[i], i, sa[i]);
		pf("\n");
	}*/
}SA;

int n, sta[maxn+5];
bool vis[c_size+5];
char arr[1010];

void init()
{
	SA.clear();
	FOR(i,0,n)
	{
		sf("%s", arr);
		if(i) SA.ss[SA.len] = i, SA.type[SA.len++] = c_size;
		FOR(k,0,strlen(arr))
			SA.ss[SA.len] = arr[k] + 4, SA.type[SA.len++] = i;
	}
	if(n == 1)
	{
		pf("%s\n", arr);
		return;
	}
	SA.type[SA.len] = c_size;
	SA.build_sa(); SA.build_height();
	int l = 1, r = SA.len, ans = 0, top = 0;
	bool fg;
	while(l <= r)
	{
		int mid = (l+r) >> 1, tot = 0;
		fg = false;
		mem(vis, 0);
		REP(i,1,SA.len)
		{
			if(SA.height[i] >= mid && !vis[SA.type[SA.sa[i-1]]])
			{
				++tot, vis[SA.type[SA.sa[i-1]]] = true;
			}
			else if(SA.height[i] < mid)
			{
				//pf("i = %d, tot = %d\n", i, tot);
				if(!vis[SA.type[SA.sa[i-1]]])
					++tot;
				if(tot > n/2)
				{
					//pf("tot = %d\n", tot);
					//pf("tot = %d\n", tot);
					//pf("ans = %d, top = %d\n", ans, top);
					//for(int pp = 1; pp <= top; ++pp) pf("sta[%d] = %d\n", pp, sta[pp]);
					if(!fg) top = 0;
					sta[++top] = SA.sa[i-1];
					fg = true;
				}
				tot = 0;
				mem(vis, 0);
			}
		}
		if(fg)
		{
			ans = mid;
			l = mid+1;
		}
		else r = mid-1;
	}
	//SA.output();
	if(!ans) pf("?\n");
	else
	{
		REP(i,1,top)
		{
			for(int k=0; k<ans; ++k)
				pf("%c", SA.ss[sta[i]+k]-4);
			pf("\n");
		}
		/*REP(i,1,top)
		{
			pf("sta[%d] = %d\n", i, sta[i]);
		}*/
	}
	return;
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	bool fg = false;
	while(sf("%d", &n), n)
	{
		if(fg) pf("\n");
		fg = true;
		init();
	}
	return 0;
}
