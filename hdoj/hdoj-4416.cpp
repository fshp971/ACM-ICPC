//#include<bits/stdc++.h>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>

using namespace std;

#define LL long long
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define mem(a,b) memset(a,b,sizeof(a))
#define MP make_pair
#define pii pair<int,int>
#define sf scanf
#define pf printf

const int maxn = 1e5, c_size = 26;

struct State
{
	int val, par, go[c_size+1];
	void init() { val = 0,  par = -1, mem(go,-1); }
}que[maxn*2+5];
int root, last, tot;
int match[maxn*2+5];
int S[maxn*2+5], cont[maxn*2+5];

void Extend(int w)
{
	int p = last, np = tot++;
	que[np].init();
	que[np].val = que[p].val+1;
	while(p!=-1 && que[p].go[w]==-1)
		que[p].go[w] = np, p = que[p].par;
	if(p == -1) que[np].par = root;
	else
	{
		int q = que[p].go[w];
		if(que[p].val+1 == que[q].val)
			que[np].par = q;
		else
		{
			int nq = tot++;
			que[nq] = que[q];
			que[nq].val = que[p].val+1;
			que[q].par = que[np].par = nq;
			while(p!=-1 && que[p].go[w] == q)
				que[p].go[w] = nq, p = que[p].par;
		}
	}
	last = np;
}

char arr[maxn+5];

int main()
{
	int T, n, len, l;
	LL ans;
	sf("%d", &T);
	REP(t,1,T)
	{
		sf("%d", &n);
		sf("%s", arr);
		root = last = tot = 0, que[tot++].init();
		len = strlen(arr);
		FOR(i,0,len) Extend(arr[i]-'a');
		mem(match, 0);
		REP(i,1,n)
		{
			sf("%s", arr);
			l = strlen(arr);
			int p = root, w, tmp = 0;
			FOR(k,0,l)
			{
				w = arr[k]-'a';
				if(que[p].go[w] != -1)
				{
					p = que[p].go[w];
					match[p] = max(match[p], ++tmp);
				}
				else
				{
					while(p!=-1 && que[p].go[w]==-1)
						p = que[p].par;
					if(p == -1) { p = root, tmp = 0; }
					else
					{
						tmp = que[p].val+1;
						p = que[p].go[w];
						match[p] = max(match[p], tmp);
					}
				}
			}
		}
		for(int i=0; i<=len; ++i) cont[i] = 0;
		for(int i=0; i<tot; ++i) ++cont[que[i].val];
		for(int i=1; i<=len; ++i) cont[i] += cont[i-1];
		for(int i=tot-1; i>=0; --i)
			S[--cont[que[i].val]] = i;
		ans = 0;
		for(int i=tot-1; i>=1; --i)
		{
			int &si = S[i];
			match[que[si].par] = max(match[que[si].par], match[si]);
			if(match[si])
			{
				if(match[si] < que[si].val)
					ans += que[si].val - match[si];
			}
			else ans += que[si].val-que[que[si].par].val;
		}
		pf("Case %d: %lld\n", t, ans);
	}
	return 0;
}
