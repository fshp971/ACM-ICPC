//#include<bits/stdc++.h>
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

const int maxn = 100000;

int n, m, kk;
int arr[maxn+5], type[maxn+5];
int sa[maxn+5], rank[maxn+5], height[maxn+5];
int tx[maxn+5], ty[maxn+5], tc[maxn+5];

void BuildSA(int *a, int len, int size = 50010)
{
	int i, k, p;
	for(i=0; i<size; ++i) tc[i] = 0;
	for(i=0; i<len; ++i) ++tc[tx[i] = a[i]];
	for(i=1; i<size; ++i) tc[i] += tc[i-1];
	for(i=len-1; i>=0; --i) sa[--tc[tx[i]]] = i;
	for(k=1; k<=len; k<<=1)
	{
		p = 0;
		for(i=len-k; i<len; ++i) ty[p++] = i;
		for(i=0; i<len; ++i) if(sa[i]>=k) ty[p++] = sa[i]-k;
		for(i=0; i<size; ++i) tc[i] = 0;
		for(i=0; i<len; ++i) ++tc[tx[ty[i]]];
		for(i=1; i<size; ++i) tc[i] += tc[i-1];
		for(i=len-1; i>=0; --i) sa[--tc[tx[ty[i]]]] = ty[i];
		swap(tx, ty);
		p = 1, tx[sa[0]] = 0;
		for(i=1; i<len; ++i)
			tx[sa[i]] = ty[sa[i]] == ty[sa[i-1]] && ty[min(sa[i]+k,len-1)] == ty[min(sa[i-1]+k,len-1)] ? p-1 : p++;
		if(p >= len) break;
		size = p;
	}
}

void GetHeight(int *a, int len)
{
	int i, j, k = 0;
	for(i=0; i<len; ++i) rank[sa[i]] = i;
	for(int i=0; i<len-1; ++i)
	{
		if(k) --k;
		j = sa[rank[i]-1];
		while(a[i+k] == a[j+k]) ++k;
		height[rank[i]] = k;
	}
}

int CalcPair(int *a, int len, int lim)
{
	int res, tot1, tot2;
	res = tot1 = tot2 = 0;
	for(int i=1; i<=len; ++i)
	{
		if(height[i] < lim)
		{
			if(tot2) res += tot1;
			tot1 = tot2 = 0;
		}
		if(type[sa[i]] == 1) ++tot1;
		else if(type[sa[i]] == 2) ++tot2;
	}
	if(tot2) res += tot1;
	return res;
}

int main()
{
	int len, ans;
	while(~sf("%d%d%d", &n, &m, &kk))
	{
		len = 0;
		REP(i,1,n)
			sf("%d", arr+len), ++arr[len], type[len++] = 1;
		arr[len] = 50005, type[len++] = 0;
		REP(i,1,m)
			sf("%d", arr+len), ++arr[len], type[len++] = 2;
		arr[len] = 0, type[len++] = 0;
		BuildSA(arr, len, 50005+1);
		GetHeight(arr, len);
		ans = CalcPair(arr,len,kk) - CalcPair(arr,len,kk+1);
		pf("%d\n", ans);
	}
	return 0;
}
