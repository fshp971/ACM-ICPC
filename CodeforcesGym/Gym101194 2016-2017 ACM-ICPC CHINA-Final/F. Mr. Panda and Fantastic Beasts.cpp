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

const int maxn = 300000, c_size = 26;


struct State
{
	int val, match, poi;
	char c;
	State *par, *go[c_size+2];
	void init() { val = match = poi = 0, par = NULL, mem(go,0); }
}que[maxn*2+5], *root, *last;
int tot;

void Extend(int w, int poi)
{
	State *p = last, *np = que + (tot++);
	np->init();
	np->val = p->val+1, np->poi = poi;
	np->c = w+'a';
	while(p!=NULL && p->go[w]==NULL)
		p->go[w] = np, p = p->par;
	if(p == NULL) np->par = root;
	else
	{
		State *q = p->go[w];
		if(p->val+1 == q->val) np->par = q;
		else
		{
			State *nq = que + (tot++);
			*nq = *q; //q->match == 0
			nq->val = p->val+1;
			q->par = np->par = nq;
			while(p!=NULL && p->go[w]==q)
				p->go[w] = nq, p = p->par;
		}
	}
	last = np;
}

char arr[maxn+5], brr[maxn+5];
int cont[maxn*2+5], S[maxn*2+5];

void update(int &ans, int &tans, int &poi, int &tpoi)
{
	if(ans==0 || tans<ans)
	{
		ans = tans, poi = tpoi;
		return;
	}
	if(tans > ans) return;
	for(int i=0; i<ans; ++i)
		if(arr[tpoi+i-1] != arr[poi+i-1])
		{
			if(arr[tpoi+i-1] < arr[poi+i-1])
				poi = tpoi;
			return;
		}
}

int main()
{
	int T, n, len, tl;
	sf("%d", &T);
	REP(t,1,T)
	{
		sf("%d", &n);
		root = last = que;
		root->init(), tot = 1;
		sf("%s", arr);
		len = strlen(arr);
		for(int i=len-1; i>=0; --i)
			Extend(arr[i]-'a', i+1);
		REP(i,2,n)
		{
			sf("%s", brr);
			tl = strlen(brr);
			State *p = root;
			int tmp = 0, w;
			for(int k=tl-1; k>=0; --k)
			{
				int w = brr[k]-'a';
				if(p->go[w] != NULL)
				{
					p = p->go[w];
					p->match = max(p->match, ++tmp);
				}
				else
				{
					while(p!=NULL && p->go[w]==NULL)
						p = p->par;
					if(p == NULL) tmp = 0, p = root;
					else
					{
						tmp = p->val+1;
						p = p->go[w];
						p->match = max(p->match, tmp);
					}
				}
			}
		}
		for(int i=0; i<=len; ++i) cont[i] = 0;
		for(int i=0; i<tot; ++i) ++cont[que[i].val];
		for(int i=1; i<=len; ++i) cont[i] += cont[i-1];
		for(int i=tot-1; i>=0; --i) S[--cont[que[i].val]] = i;
		int ans = 0, poi;
		for(int i=tot-1; i>=1; --i)
		{
			int &si = S[i];
			que[si].par->match = max(que[si].par->match, que[si].match);
			int res = que[si].match+1;
			if(res <= que[si].val)
			{
				res = max(res, que[si].par->val+1);
				update(ans, res, poi, que[si].poi);
			}
		}
		pf("Case #%d: ", t);
		if(ans == 0) pf("Impossible\n");
		else
		{
			for(int i=0; i<ans; ++i)
				pf("%c", arr[poi+i-1]);
			pf("\n");
		}
	}
	return 0;
}
