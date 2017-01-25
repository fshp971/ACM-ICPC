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

const int maxn = 2e5, c_size = 10;

struct State 
{
	int val;
	LL *cont, *sum;
	State *par, *go[c_size+2];
	void init() { val = 0, cont = NULL, sum = NULL, par = NULL, mem(go,0); }
} *root, *last, que[maxn*2+5];
int tot;
LL cont[maxn*2+5], sum[maxn*2+5];

void Extend(int w)
{
	State *p = last, *np = &que[tot++];
	np->init();
	np->val = p->val+1, np->cont = &cont[tot-1], np->sum = &sum[tot-1];
	while(p!=NULL && p->go[w]==NULL)
		p->go[w] = np, p = p->par;
	if(p == NULL) np->par = root;
	else
	{
		State *q = p->go[w];
		if(p->val+1 == q->val) np->par = q;
		else
		{
			State *nq = &que[tot++];
			*nq = *q;
			nq->val = p->val+1;
			nq->cont = &cont[tot-1], nq->sum = &sum[tot-1]; //hhh
			q->par = np->par = nq;
			while(p!=NULL && p->go[w]==q)
				p->go[w] = nq, p = p->par;
		}
	}
	last = np;
}

LL dfs(State *p, int w)
{
	if((*p->cont) != -1) return *p->cont;
	*p->cont = 0, *p->sum = 0;
	LL res = 0;
	bool fg = 0;
	for(int i=0; i<c_size; ++i)
		if(p->go[i] != NULL)
		{
			res += dfs(p->go[i], i);
			*p->sum += *p->go[i]->sum;
		}
	if(w)
	{
		*p->sum += 1;
		*p->cont = res*10 + (*p->sum)*w;
	}
	else
		*p->cont = res*10;
	*p->cont %= 2012;
	return *p->cont;
}

int n;
char arr[maxn+5];

int main()
{
	int l;
	LL ans;
	while(~sf("%d", &n))
	{
		tot = 0;
		root = last = &que[tot++];
		root->init();
		root->cont = &cont[0], root->sum = &sum[0];
		REP(i,1,n)
		{
			sf("%s", arr);
			int l = strlen(arr);
			for(int k=l-1; k>=0; --k)
				Extend(arr[k]-'0');
			Extend(c_size);
		}
		mem(cont,-1);
		ans = 0;
		for(int i=0; i<c_size; ++i)
			if(root->go[i] != NULL)
			{
				ans += dfs(root->go[i], i);
				ans %= 2012;
			}
		pf("%lld\n", ans);
	}
	return 0;
}
