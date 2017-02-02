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

const int maxn = 2e6, c_size = 26;

struct State
{
	int val, par, go[c_size+2];
	void init() { val = 0, par = -1, mem(go,-1); }
}que[maxn+5];
int tot, root, last;
int Right[maxn+5];

void Extend(int w)
{
	int p = last, np = tot++;
	Right[np] = 1;
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
			que[np].par = que[q].par = nq;
			while(p!=-1 && que[p].go[w]==q)
				que[p].go[w] = nq, p = que[p].par;
		}
	}
	last = np;
}

char arr[maxn+5];
int cont[maxn+5], S[maxn+5];
int vis[maxn+5];

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int len, tl, tl2, T;
	sf("%s", arr);
	len = strlen(arr);
	root = last = tot = 0;
	que[tot++].init();
	for(int i=0; i<len; ++i) Extend(arr[i]-'a');
	for(int i=0; i<tot; ++i) ++cont[que[i].val];
	for(int i=1; i<=len; ++i) cont[i] += cont[i-1];
	for(int i=tot-1; i>=0; --i) S[--cont[que[i].val]] = i;
	for(int i=tot-1; i>=1; --i)
		Right[que[S[i]].par] += Right[S[i]];
	sf("%d", &T);
	for(int t=1; t<=T; ++t)
	{
		sf("%s", arr);
		tl = strlen(arr);
		for(int i=0; i<tl-1; ++i) arr[i+tl] = arr[i];
		tl2 = tl*2-1;
		int p = root, now = 0, ans = 0;
		for(int i=0; i<tl2; ++i)
		{
			int nx = arr[i]-'a';
			if(que[p].go[nx] != -1)
			{
				p = que[p].go[nx];
				++now;
			}
			else
			{
				while(p!=-1 && que[p].go[nx]==-1)
					p = que[p].par;
				if(p == -1) { p = root, now = 0; continue; }
				else
				{
					now = que[p].val+1;
					p = que[p].go[nx];
				}
			}
			while(tl<=que[que[p].par].val)
			{
				p = que[p].par;
				now = que[p].val;
			}
			if(now >= tl && vis[p]!=t)
			{
				vis[p] = t;
				ans += Right[p];
			}
		}
		pf("%d\n", ans);
	}
	return 0;
}
