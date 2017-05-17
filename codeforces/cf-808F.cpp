#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<queue>
#include<utility>
#include<bitset>
#include<complex>
#include<map>
#include<set>
#include<unordered_map>
#include<unordered_set>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 100;
const int maxk = 2e5;

struct Card {
	int pi, ci, li;
} card[maxn+2];

int n, kk;
bool mmp[maxn+2][maxn+2];

bool prime[maxk+2];

void GetPrime() {
	REP(i,0,maxk) prime[i] = 1;
	prime[0] = prime[1] = 0;
	for(LL i = 2; i <= maxk; ++i)
		if(prime[i]) {
			for(LL k = i*i; k <= maxk; k += i)
				prime[k] = 0;
		}
}

int vist[maxn+2];

bool dfs(int x, int now, int rem, int level) {
	if(now >= kk) return true;
	if(now + rem < kk) return false;
	for(int i = x; i <= n; ++i) {
		if(card[i].li > level || vist[i])
			continue;

		rem -= card[i].pi;

		for(int k = i+1; k <= n; ++k)
			if(card[k].li <= level && prime[card[i].ci + card[k].ci]) {
				if(vist[k] == 0)
					rem -= card[k].pi;
				++vist[k];
			}

		if(dfs(i + 1, now + card[i].pi, rem, level))
			return true;

		for(int k = i+1; k <= n; ++k)
			if(card[k].li <= level && prime[card[i].ci + card[k].ci]) {
				--vist[k];
				if(vist[k] == 0)
					rem += card[k].pi;
			}
	}
	return false;
}

bool check(int level) {
	int rem = 0;
	for(int i = 1; i <= n; ++i)
		if(card[i].li <= level)
			rem += card[i].pi;
	mem(vist, 0);
	return dfs(1, 0, rem, level);
}

int main() {
	GetPrime();
	scanf("%d%d", &n, &kk);
	REP(i,1,n)
		scanf("%d%d%d", &card[i].pi, &card[i].ci, &card[i].li);
	int l = 1, r = 100, ans = -1;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(check(mid))
			ans = mid, r = mid - 1;
		else l = mid + 1;
	}
	printf("%d\n", ans);
	return 0;
}
