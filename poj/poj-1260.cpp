//#include<bits/stdc++.h>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>

using namespace std;

#define LL long long
#define MP(a,b) make_pair(a,b)
#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define pii pair<int,int>
#define sf scanf
#define pf printf

const int maxn = 100;

int n, sum[maxn+5], pi[maxn+5];
int f[maxn+5], q[maxn+5];

inline int dy(int i, int j)
{
	return f[j] - f[i];
}

inline int dx(int i, int j)
{
	return sum[j] - sum[i];
}

int main()
{
	//freopen("in.txt","r",stdin);
	//freopen("out.txt","w",stdout);
	int l, r, T;
	sf("%d", &T);
	while(T--)
	{
		sf("%d", &n);
		REP(i,1,n) sf("%d%d", sum+i, pi+i), sum[i] += sum[i-1];
		l = r = 1;
		q[1] = 0;
		for(int i=1; i<=n; ++i)
		{
			while(l<r && dy(q[l], q[l+1]) <= pi[i] * dx(q[l], q[l+1]))
				++l;
			f[i] = f[q[l]] + (sum[i] - sum[q[l]] + 10) * pi[i];
			while(l<r && dy(q[r-1], q[r]) * dx(q[r], i) >= dy(q[r], i) * dx(q[r-1], q[r]))
				--r;
			q[++r] = i;
		}
		pf("%d\n", f[n]);
	}
	return 0;
}
