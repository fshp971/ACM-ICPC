#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define sf scanf
#define pf printf
typedef long long LL;
typedef pair<int,int> pii;

const int md = 1000000007;
const int maxn = 5e6;
const int mo = 2070307;

LL phi[maxn+5];
int h[mo+5], nex[mo+5], e[mo+5], cont[mo+5], top;

void PhiMaker() {
	mem(phi, 0);
	phi[1] = 1;
	for(int i=2; i<=maxn; ++i) if(!phi[i])
			for(int k=i; k<=maxn; k+=i) {
				if(!phi[k]) phi[k] = k;
				phi[k] = phi[k] / i * (i-1);
			}
	for(int i=1; i<=maxn; ++i)
		phi[i] = (phi[i] + phi[i-1]) % md;
}

LL S(LL n)
{
	if(n <= maxn) return phi[n];
	int x = n % mo;
	for(int i = h[x]; i; i = nex[i])
		if(e[i] == n)
			return cont[i];
	LL res;
	if(n%2 == 0) res = n/2 % md * ((n+1)%md) % md;
	else res = (n+1)/2 % md * (n%md) % md;
	LL sum = 0;
	for(LL i = 2, nx = 0; i <= n; i = nx+1)
	{
		nx = n / (n/i);
		sum = (sum + (nx-i+1) * S(n/i) % md) % md;
	}
	res = (res + md - sum) % md;
	e[++top] = n, cont[top] = res, nex[top] = h[x], h[x] =top;
	return res;
}

int main()
{
	PhiMaker();
	LL n;
	sf("%lld", &n);
	top = 0;
	printf("%lld\n", S(n));
	return 0;
}
