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

const int maxn = 2e5;

int n, m, kk;
int sa[maxn+5], rank[maxn+5], height[maxn+5];
int tx[maxn+5], ty[maxn+5], tc[maxn+5];
int type[maxn+5];
char arr[maxn+5], ss[maxn+5];

void BuildSA(char *a, int len, int size)
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

void GetHeight(char *a, int len)
{
	int i, j, k = 0;
	for(i=0; i<len; ++i) rank[sa[i]] = i;
	for(i=0; i<len-1; ++i)
	{
		if(k) --k;
		j = sa[rank[i]-1];
		while(a[i+k] == a[j+k]) ++k;
		height[rank[i]] = k;
	}
}

LL sta[maxn+5][2];

LL Run(int len, int lim)
{
	//type1
	int top = 0;
	LL ans = 0, tot = 0, sum = 0;
	for(int i=1; i<len; ++i)
	{
		if(height[i] < lim)
		{
			top = tot = sum = 0;
			if(type[sa[i]] == 2) ++tot;
			continue;
		}
		while(top && sta[top][0] >= height[i])
		{
			sum -= sta[top][1] * (sta[top][0]-lim+1);
			tot += sta[top--][1];
		}
		sta[++top][0] = height[i], sta[top][1] = tot;
		sum += tot * (height[i]-lim+1), tot = 0;
		if(type[sa[i]] == 1) ans += sum;
		else ++tot;
	}
	//type2
	top = 0, tot = 0, sum = 0;
	for(int i=1; i<len; ++i)
	{
		if(height[i] < lim)
		{
			top = tot = sum = 0;
			if(type[sa[i]] == 1) ++tot;
			continue;
		}
		while(top && sta[top][0] >= height[i])
		{
			sum -= sta[top][1] * (sta[top][0]-lim+1);
			tot += sta[top--][1];
		}
		sta[++top][0] = height[i], sta[top][1] = tot;
		sum += tot * (height[i]-lim+1), tot = 0;
		if(type[sa[i]] == 2) ans += sum;
		else ++tot;
	}
	return ans;
}

int main()
{
	int len, t;
	while(sf("%d", &kk), kk)
	{
		len = 0;
		sf("%s", ss), t = strlen(ss);
		for(int i=0; i<t; ++i)
			arr[len] = ss[i], type[len++] = 1;
		arr[len] = 127, type[len++] = 0;
		sf("%s", ss), t = strlen(ss);
		for(int i=0; i<t; ++i)
			arr[len] = ss[i], type[len++] = 2;
		arr[len] = 0, type[len++] = 0;
		BuildSA(arr, len, 127+1);
		GetHeight(arr, len);
		pf("%lld\n", Run(len, kk));
	}
	return 0;
}
