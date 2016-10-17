#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<string>
#include<queue>
#include<vector>
#include<utility>
#include<map>
#include<set>
#include<bitset>

using namespace std;

#define LL long long
#define mem(a,b) memset(a,b,sizeof(a))
#define MP(a,b) make_pair(a,b)
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define sf scanf
#define pf printf

const int maxn = 200000;

struct Node
{
	int col, fa;
}arr[maxn+5];

int n, m, kk;

int find(int x){ return arr[x].fa == x ? x : arr[x].fa = find(arr[x].fa); }
bool cmp(Node a, Node b)
{
	if(a.fa == b.fa) return a.col < b.col;
	return a.fa < b.fa;
}

int main()
{
	int l, r, cont, all, maxi, ans = 0;
	sf("%d%d%d", &n, &m, &kk);
	REP(i,1,n) sf("%d", &arr[i].col), arr[i].fa = i;
	REP(i,1,m)
	{
		sf("%d%d", &l, &r);
		arr[find(arr[l].fa)].fa = find(arr[r].fa);
	}
	REP(i,1,n) arr[i].fa = find(arr[i].fa);
	sort(arr+1, arr+1+n, cmp);
	arr[0].fa = 0;
	map<int, int> Map;
	cont = 0, all = 0, maxi = -(1<<30);
	for(int i=1; i<=n; ++i)
	{
		if(arr[i].fa != arr[i-1].fa)
		{
			maxi = max(cont, maxi);
			ans += all-maxi;
			all = 1, cont = 1, maxi = -(1<<30);
		}
		else
		{
			++all;
			if(arr[i].col == arr[i-1].col)
				++cont;
			else
			{
				maxi = max(cont, maxi);
				cont = 1;
			}
		}
	}
	maxi = max(cont, maxi);
	ans += all-maxi;
	cout << ans << "\n";
	return 0;
}
