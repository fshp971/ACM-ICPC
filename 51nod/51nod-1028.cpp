#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<complex>
#include<iostream>
#include<algorithm>
#include<string>
#include<queue>
#include<vector>
#include<utility>
#include<map>
#include<set>

using namespace std;

#define LL long long
#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a;i<=b;++i)
#define FOR(i,a,b) for(int i=a;i<b;++i)
#define MP make_pair
#define pii pair<int,int>
#define sf scanf
#define pf printf

const LL P = (479 << 21) + 1;
const LL G = 3;

LL pow_mod(LL a, LL b)
{
	LL res = 1;
	while(b)
	{
		if(b&1) res = res*a % P;
		a = a*a % P, b >>= 1;
	}
	return res;
}

void NTT(LL *a, int len, int type) {
	int i, j, k, l;
	for(i=1, j=len>>1; i<len-1; ++i) {
		if(i<j) swap(a[i], a[j]);
		k = len>>1;
		while(j>=k)
			j -= k, k >>= 1;
		j += k;
	}
	LL var, step, u, v;
	for(l=2; l<=len; l<<=1) {
		step = pow_mod(G, (P-1)/l);
		for(k=0; k<len; k+=l) {
			var = 1;
			for(i=k; i<k+l/2; ++i) {
				u = a[i], v = var*a[i+l/2] % P;
				a[i] = (u+v) % P;
				a[i+l/2] = (u-v+P) % P;
				var = var*step % P;
			}
		}
	}
	if(type == -1)
	{
		for(i=1; i<len/2; ++i) swap(a[i], a[len-i]);
		LL inv = pow_mod(len, P-2);
		for(i=0; i<len; ++i) a[i] = a[i]*inv % P;
	}
}

const int maxn = 1<<18;

int n, m;
char arr[maxn+5];
LL aa[maxn+5], bb[maxn+5];

int main() {
	sf("%s", arr);
	n = strlen(arr);
	for(int i=0; i<n; ++i)
		aa[i] = arr[n-1-i]-'0';
	sf("%s", arr);
	m = strlen(arr);
	for(int i=0; i<m; ++i)
		bb[i] = arr[m-1-i]-'0';
	m = n+m;
	n = 1;
	while(n<m) n <<= 1;
	NTT(aa, n, 1);
	NTT(bb, n, 1);
	for(int i=0; i<n; ++i)
		aa[i] = aa[i]*bb[i] % P;
	NTT(aa, n, -1);
	for(int i=0; i<n; ++i) if(aa[i]>=10)
	{
		aa[i+1] += aa[i]/10;
		aa[i] %= 10;
	}
	while(aa[n])
	{
		aa[n+1] = aa[n]/10;
		aa[n] %= 10;
		++n;
	}
	while(n && aa[n-1]==0) --n;
	if(!n) ++n;
	for(int i=n-1; i>=0; --i) pf("%lld", aa[i]);
	pf("\n");
	return 0;
}
