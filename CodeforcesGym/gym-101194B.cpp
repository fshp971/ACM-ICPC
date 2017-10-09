#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<iostream>
#include<algorithm>
#include<string>
#include<queue>
#include<utility>
#include<map>
#include<set>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define sf scanf
#define pf printf
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 1e5;

int n;
LL kk, two[70];
int arr[maxn+5];

void solve()
{
	int m, C_odd, C_even, odd, even;
	LL cont;
	C_odd = (n+1)/2, C_even = n-C_odd;
	odd = (C_odd+1)/2, even = (C_even+1)/2;
	m = odd+even;
	for(int i=1; i<=m; ++i)
	{
		if(i%2) --C_odd, --odd;
		else --C_even, --even;
		if(odd+C_even >= 62 || C_odd+even >= 62)
		{
			arr[i] = 0;
			continue;
		}
		cont = two[odd+C_even] - two[odd+even] + two[C_odd+even];
		if(kk <= cont) arr[i] = 0;
		else arr[i] = 1, kk -= cont;
	}
	int type = -1, last;
	for(int i=m+1; i<=n; ++i)
	{
		int reflex;
		if(n%2) reflex = n+1-i;
		else reflex = (i%2) ? (n-i) : (n+2-i);
		if(i%2) --C_odd;
		else --C_even;

		if(type == 0) {
			if(i%2 == 0) arr[i] = arr[reflex];
			else {
				if(C_odd >= 62) arr[i] = 0;
				else {
					cont = two[C_odd];
					if(kk <= cont) arr[i] = 0;
					else arr[i] = 1, kk -= cont;
				}
			}
		}

		else if(type == 1) {
			if(i%2 == 1) arr[i] = arr[reflex];
			else {
				if(C_even >= 62) arr[i] = 1;
				else {
					cont = two[C_even];
					if(kk <= cont) arr[i] = 0;
					else arr[i] = 1, kk -= cont;
				}
			}
		}

		else {

			if(arr[reflex] == 0) {
				if(C_odd >= 62 || C_even >= 62) {
					arr[i] = 0;
					continue;
				}
				cont = two[C_odd] - 1 + two[C_even];
				if(kk <= cont) arr[i] = 0;
				else {
					arr[i] = 1, kk -= cont;
					type = (i%2) ? 0 : 1;
				}
			}

			else {

				if(i%2) {
					if(C_odd >= 62) {
						arr[i] = 0, type = 0;
						continue;
					}
					cont = two[C_odd];
				}
				else {
					if(C_even >= 62) {
						arr[i] = 0, type = 1;
						continue;
					}
					cont = two[C_even];
				}

				if(kk <= cont) {
					arr[i] = 0;
					type = (i%2) ? 0 : 1;
				}
				else arr[i] = 1, kk -= cont;

			}
		}
	}
}

int main()
{
	int T;
	two[0] = 1;
	for(int i=1; i<=62; ++i)
		two[i] = two[i-1]*2;
	sf("%d", &T);
	REP(t,1,T)
	{
		sf("%d%lld", &n, &kk);
		pf("Case #%d: ", t);
		solve();
		if(kk == 1)
		{
			for(int i=1; i<=n; ++i)
				pf("%d", arr[i]);
			pf("\n");
		}
		else pf("NOT FOUND!\n");
	}
	return 0;
}
