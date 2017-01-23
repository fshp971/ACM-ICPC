#include<bits/stdc++.h>

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
			q->par = np->par = nq;
			while(p!=NULL && p->go[w]==q)
				p->go[w] = nq, p = p->par;
		}
	}
	last = np;
}

LL dfs(State *p)
{
	if(*p->cont != -1) return *p->cont;
	*p->cont = 0, *p->sum = 1;
	bool fg = 0;
	LL tmp1, tmp2;
	for(int i=1; i<c_size; ++i)
		if(p->go[i] != NULL)
		{
			fg = 1;
			tmp1 = dfs(p->go[i]);
			tmp2 = *(p->go[i])->sum;
			*p->sum += tmp2;
			if(tmp1 == -2) *p->cont += i;
			else *p->cont += tmp1*10 + tmp2*i;
			*p->cont %= 2012;
		}
	if(p->go[0] != NULL)
	{
		tmp1 = dfs(p->go[0]);
		tmp2 = *(p->go[0])->sum;
		if(tmp1 != -2)
		{
			fg = 1;
			*p->sum += tmp2-1;
			*p->cont += tmp1*10;
			*p->cont %= 2012;
		}
	}
	if(!fg) *p->cont = -2;
	return *p->cont;
}

int n;
char arr[maxn+5];

int main()
{
	int l;
	while(~sf("%d", &n))
	{
		tot = 0;
		root = last = &que[tot++];
		root->cont = &cont[0], root->sum = &sum[0];
		REP(i,1,n)
		{
			sf("%s", arr);
			int l = strlen(arr);
			for(int k=l-1; k>=0; --k)
				Extend(arr[k]-'0');
			//pf("i = %d\n", i);
			Extend(c_size);
		}
		//return 0;
		//pf("asdf\n");
		mem(cont,-1);
		pf("%lld\n", dfs(root));
	}
	return 0;
}
