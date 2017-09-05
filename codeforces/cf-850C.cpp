#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 100;
const int maxa = 32000;

int tot, prime[maxa + 5];
int vist[maxa + 5];
void GetPrime() {
	prime[tot = 1] = 2;
	for(int i = 3; i <= maxa; i += 2)
		if(!vist[i]) {
			prime[++tot] = i;
			for(LL k = LL(i) * i; k <= maxa; k += i)
				vist[k] = 1;
		}
}

map<int,int> Map, SG;

int F(int x) {
	if(!x) return 0;
	if(SG.count(x)) return SG[x];
	vector<int> seg;
	int kk = 31, pre = -1, res = -1;
	while(!((x >> (kk - 1)) & 1)) --kk;
	for(int i = 1; i <= kk; ++i)
		seg.push_back(F((x >> i) | (x & (((unsigned int)1 << (i - 1)) - 1))));
	sort(seg.begin(), seg.end());
	for(auto it: seg) {
		if(pre == it) continue;
		if(pre + 1 < it) {
			res = pre + 1;
			break;
		}
		pre = it;
	}
	if(res == -1) res = pre + 1;
	SG[x] = res;
	return res;
}

int main() {
	GetPrime();
	int n, u, c;
	scanf("%d", &n);
	for(int i = 1; i <= n; ++i) {
		scanf("%d", &u);
		for(int k = 1; k <= tot && LL(prime[k]) * prime[k] <= u; ++k) {
			c = 0;
			while(u % prime[k] == 0)
				u /= prime[k], ++c;
			if(c) {
				if(!Map.count(prime[k])) Map[prime[k]] = 1 << (c - 1);
				else Map[prime[k]] |= 1 << (c - 1);
			}
		}
		if(u > 1) {
			if(!Map.count(u)) Map[u] = 1;
			else Map[u] |= 1;
		}
	}
	int ans = 0;
	for(auto it: Map)
		ans ^= F(it.second);
	printf(ans ? "Mojtaba\n" : "Arpa\n");
	return 0;
}
