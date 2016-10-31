#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<queue>
#include<string>
#include<vector>
#include<utility>
#include<map>
#include<set>
#include<bitset>

using namespace std;

#define LL long long
#define pii pair<int,int>
#define MP make_pair
#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define sf scanf
#define pf printf

const int maxnode = 100, c_size = 6;
const double pi = 1.0 / 6.0;

double A[maxnode+5][maxnode+5];

struct Tire
{
	int top;
	int nex[maxnode+5][c_size+5], val[maxnode+5];
	int fail[maxnode+5];

	void clear()
	{
		top = val[0] = 0;
		mem(nex[0], 0);
	}

	void insert(int *a, int len, int vv)
	{
		int u = 0;
		for(int i=0; i<len; ++i)
		{
			int t = a[i]-1;
			if(!nex[u][t])
			{
				nex[u][t] = (++top), val[top] = 0;
				mem(nex[top], 0);
			}
			u = nex[u][t];
		}
		val[u] = vv;
	}

	void get_fail()
	{
		fail[0] = 0;
		queue<int> q;
		for(int i=0; i<c_size; ++i) if(int &t = nex[0][i])
		{
			fail[t] = 0;
			q.push(t);
		}
		while(!q.empty())
		{
			int x = q.front(); q.pop();
			for(int i=0; i<c_size; ++i)
			{
				int u = nex[x][i];
				if(!u) { nex[x][i] = nex[fail[x]][i]; continue; }
				q.push(u);
				int v = fail[x];
				while(v && !nex[v][i]) v = fail[v];
				fail[u] = nex[v][i];
			}
		}
	}

	void calc()
	{
		mem(A, 0);
		A[0][top+1] = 1.0;
		for(int i=1; i<=top; ++i)
		{
			A[i][i] = -1.0;
			if(val[i]) A[0][i] = 1.0;
		}
		for(int i=0; i<=top; ++i)
		{
			if(val[i]) continue;
			for(int k=0; k<c_size; ++k) if(nex[i][k])
			{
				A[nex[i][k]][i] += pi;
			}
		}
	}
}AC;

void Gauss(int n)
{
	for(int i=0; i<n; ++i)
	{
		int r = i;
		for(int j=i+1; j<n; ++j)
			if(fabs(A[r][i]) < fabs(A[j][i])) r = j;
		if(r != i)
			for(int j=0; j<=n; ++j) swap(A[i][j], A[r][j]);
		for(int j=i+1; j<n; ++j)
		{
			for(int k=n; k>=i; --k)
				A[j][k] -= A[i][k]/A[i][i] * A[j][i];
		}
	}
	for(int i=n-1; i>=0; --i)
	{
		for(int j=i+1; j<n; ++j)
			A[i][n] -= A[j][n] * A[i][j];
		A[i][n] /= A[i][i];
	}
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int T;
	int aa[20], n, L;
	double ans[20];
	sf("%d", &T);
	while(T--)
	{
		sf("%d%d", &n, &L);
		AC.clear();
		REP(i,1,n)
		{
			FOR(k,0,L) sf("%d", aa+k);
			AC.insert(aa, L, i);
		}
		AC.get_fail();
		AC.calc();
		Gauss(AC.top+1);
		for(int i=0; i<=AC.top; ++i)
			ans[AC.val[i]] = A[i][AC.top+1];
		for(int i=1; i<=n; ++i)
		{
			if(i>1) pf(" ");
			pf("%.6f", ans[i]);
		}
		pf("\n");
	}
	return 0;
}
