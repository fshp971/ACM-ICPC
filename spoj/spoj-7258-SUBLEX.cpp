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

const int maxn = 90000*2, c_size = 26;

struct State
{
	int val, par, go[c_size];
	void init(int _val = 0) { val = _val, par = -1, mem(go, -1); }
} que[maxn+5];
int root, last, tot;

int n, cont[maxn+5];
char arr[maxn+5];

void Extend(int w)
{
	int p = last, np = tot++;
	que[np].init(que[last].val+1);
	while(p != -1 && que[p].go[w] == -1)
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
			while(p != -1 && que[p].go[w] == q)
				que[p].go[w] = nq, p = que[p].par;
		}
	}
	last = np;
}

int dfs(int x)
{
	if(cont[x] != -1) return cont[x];
	cont[x] = 1;
	for(int i=0; i<c_size; ++i)
		if(que[x].go[i] != -1)
			cont[x] += dfs(que[x].go[i]);
	return cont[x];
}

char ans[maxn+5];

void dfs2(int x, int rem, int top)
{
	if(rem == 0) { ans[top] = '\0'; return; }
	int nx;
	for(int i=0; i<c_size; ++i)
	{
		nx = que[x].go[i];
		if(nx == -1) continue;
		if(rem > cont[nx]) rem -= cont[nx];
		else
		{
			ans[top] = i+'a';
			dfs2(nx, rem-1, top+1);
			return;
		}
	}
}

int main()
{
	sf("%s", arr);
	n = strlen(arr);
	que[0].init(), root = last = 0, tot = 1;
	for(int i=1; i<=n; ++i) Extend(arr[i-1] - 'a');
	mem(cont, -1);
	dfs(0);
	int T, q;
	sf("%d", &T);
	while(T--)
	{
		sf("%d", &q);
		dfs2(0, q, 0);
		pf("%s\n", ans);
	}
	return 0;
}
