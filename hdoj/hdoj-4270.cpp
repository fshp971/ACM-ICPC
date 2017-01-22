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

const int maxn = 5e5, c_size = 26;

struct State
{
	int val, poi, vv;
	bool *del;
	State *par, *go[c_size];
	void init() { vv = val = poi = 0, par = NULL, mem(go,0); }
} *root, *last, que[maxn+5], *sta[maxn+5];
int tot;

int S_len;
char arr[maxn+5];

int D_top;
bool del[maxn+5];
bool IsDel(State *p) { return p==NULL || *(p->del); }

void Extend(int w)
{
	State *p = last, *np = &que[tot++];
	np->init();
	np->val = p->val+1, np->poi = ++S_len;
	sta[S_len] = np;
	np->del = del + (++D_top), *np->del = false;
	while(p!=NULL && IsDel(p->go[w]))
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

int dfs(State *p, int res, int fg, int lim)
{
	if(res == lim) return p->poi - res + 1;
	if(p->vv == fg) return S_len - res + 1;
	for(int i=0; i<c_size; ++i)
		if(!IsDel(p->go[i]))
			return dfs(p->go[i], res+1, fg, lim);
}

int main()
{
	int T, l, ord;
	while(~sf("%s", arr))
	{
		que[tot=0].init();
		root = last = &que[tot++];
		sta[S_len=0] = last;
		del[D_top=0] = false;
		l = strlen(arr);
		for(int i=0; i<l; ++i) Extend(arr[i]-'a');
		sf("%d", &T);
		REP(t,1,T)
		{
			sf("%d", &ord);
			if(ord == 1)
			{
				sf("%s", arr);
				l = strlen(arr);
				for(int i=0; i<l; ++i) Extend(arr[i]-'a');
			}
			else if(ord == 2)
			{
				sf("%d", &l);
				for(State *p=last; p!=root; p=p->par)
					p->vv = t;
				pf("%d\n", dfs(root, 0, t, l));
			}
			else
			{
				sf("%d", &l);
				while(l--)
					*(sta[S_len--]->del) = true;
				last = sta[S_len];
			}
		}
	}
	return 0;
}
