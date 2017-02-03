/**************************************************************
    Problem: 3238
    User: fshp971
    Language: C++
    Result: Accepted
    Time:2484 ms
    Memory:130684 kb
****************************************************************/

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

const int maxn = 5e5, c_size = 26;

struct State
{
	int val, right;
	State *par, *go[c_size+2];
	void init() { val = right = 0, par = NULL, mem(go,0); }
}que[maxn*2+5], *root, *last;
int tot;

void Extend(int w)
{
	State *p = last, *np = &que[tot++];
	np->init();
	np->val = p->val+1, np->right = 1;
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
			nq->right = 0;
			nq->val = p->val+1;
			np->par = q->par = nq;
			while(p!=NULL && p->go[w]==q)
				p->go[w] = nq, p = p->par;
		}
	}
	last = np;
}

char arr[maxn+5];
int cont[maxn*2+5], S[maxn*2+5];

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int len;
	LL ans;
	sf("%s", arr);
	len = strlen(arr);
	ans = (LL)len*(len-1) / 2 * (len+1);
	root = last = &que[0], tot = 1;
	root->init();
	for(int i=0; i<len; ++i) Extend(arr[i]-'a');
	for(int i=0; i<tot; ++i) ++cont[que[i].val];
	for(int i=1; i<=len; ++i) cont[i] += cont[i-1];
	for(int i=tot-1; i>=0; --i) S[--cont[que[i].val]] = i;
	for(int i=tot-1; i>=1; --i)
	{
		State *p = &que[S[i]];
		p->par->right += p->right;
		ans -= (LL)(p->right) * (p->right - 1) * (p->val - p->par->val);
	}
	pf("%lld\n", ans);
	return 0;
}
