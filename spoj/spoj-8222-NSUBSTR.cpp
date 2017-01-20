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

const int maxn = 250000*2, c_size = 26;

struct State
{
	int val, num;
	State *go[c_size+2], *par;
	void init() { num = val = 0, par = NULL, mem(go,0); }
} *root, *last, sta[maxn*2+5];
int top;

void Extend(int w)
{
	State *p = last;
	sta[top].init();
	State *np = &sta[top++];
	np->num = top-1;
	np->val = p->val+1;
	while(p && p->go[w] == 0)
		p->go[w] = np, p = p->par;
	if(p == 0) np->par = root;
	else
	{
		State *q = p->go[w];
		if(p->val+1 == q->val) np->par = q;
		else
		{
			State *nq = &sta[top++];
			*nq = *q;
			nq->num = top-1;
			nq->val = p->val+1;
			q->par = np->par = nq;
			while(p && p->go[w] == q)
				p->go[w] = nq, p = p->par;
		}
	}
	last = np;
}

int n, ans[maxn+5], cont[maxn+5], Right[maxn+5];
int S[maxn+5];
char arr[maxn+5];

int main()
{
	sf("%s", arr);
	n = strlen(arr);
	sta[top = 0].init();
	root = last = &sta[top++];
	for(int i=0; i<n; ++i)
		Extend( arr[i]-'a' );
	State *tmp = root;
	for(int i=0; i<n; ++i)
		tmp = tmp->go[ arr[i]-'a' ], ++Right[tmp->num];
	for(int i=0; i<top; ++i) ++cont[sta[i].val];
	for(int i=1; i<=n; ++i) cont[i] += cont[i-1];
	for(int i=0; i<top; ++i) S[--cont[sta[i].val]] = i;
	for(int i=top-1; i>=1; --i)
		Right[(sta[S[i]].par)->num] += Right[S[i]];
	for(int i=0; i<top; ++i)
		ans[sta[i].val] = max(ans[sta[i].val], Right[i]);
	for(int i=n; i>=1; --i) ans[i] = max(ans[i], ans[i+1]);
	REP(i,1,n) pf("%d\n", ans[i]);
	return 0;
}
