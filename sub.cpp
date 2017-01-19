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

const int maxn = 250000, c_size = 26;

struct State
{
	int val;
	State *go[c_size+2], *par;
	void init() { val = 0, par = NULL, mem(go,0); }
} *root, *last, sta[maxn*2+5];
int top;

void Extend(int w)
{
	State *p = last;
	sta[top].init();
	State *np = &sta[top++];
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
			nq->val = p->val+1;
			q->par = np->par = nq;
			while(p && p->go[w] == q)
				p->go[w] = nq, p = p->par;
		}
	}
	last = np;
}

int n, ans[maxn+5];
char arr[maxn+5];
char st[maxn+5];

int dfs(State *now, int dep)
{
	int res = 0;
	for(int i=0; i<c_size; ++i)
		if(now->go[i] != NULL)
		{
			//st[++st[0]] = i+'a';
			res += dfs(now->go[i], dep+1);
		}
	/*
	if(res == 0)
	{
		st[st[0]+1] = 0;
		cout << st+1 << endl;
	}
	*/
	//pf("res = %d\n", res);
	if(res == 0) res = 1;
	ans[dep] = max(ans[dep], res);
	return res;
}

int main()
{
	sf("%s", arr);
	n = strlen(arr);
	sta[top = 0].init();
	root = last = &sta[top++];
	for(int i=0; i<n; ++i)
		Extend( arr[i]-'a' );
	mem(ans, 0);
	for(int i=0; i<c_size; ++i)
		if(root->go[i])
			dfs(root->go[i], 1);
	REP(i,1,n) pf("%d\n", ans[i]);
	return 0;
}
