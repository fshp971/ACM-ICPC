//O(n^2) + bitset, 理论上能被卡
//若采用手写bitset可以优化到O(n^2 / 64), 这样就能通过任意数据了
#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define FOR(i,a,b) for(int i = a; i < b; ++i)
#define MP make_pair
#define PB push_back
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 5e4, maxm = 5e5;

int tot, prime[maxm + 5], vist[maxm + 5];
vector<int> deco[maxm + 5];
void GetPrime() {
	tot = 0;
	for(int i = 2; i <= maxm; ++i)
		if(!vist[i]) {
			prime[++tot] = i;
			for(int k = i; k <= maxm; k += i)
				vist[k] = 1, deco[k].PB(i);
		}
	mem(vist, 0);
	for(int i = 1; i <= tot; ++i)
		vist[prime[i]] = i;
}

int n, m, aa[maxn + 5];
int seg[maxn + 5];
bitset<maxn> bt[maxn + 5], tmp;

int main() {
	GetPrime();
	scanf("%d%d", &n, &m);
	for(int i = 1; i <= n; ++i)
		scanf("%d", aa + i);
	for(int i = 1; i <= maxn; ++i) {
		bt[i].flip();
		bt[i] >>= maxn - n;
	}
    seg[n + 1] = n + 1;
	for(int i = n; i >= 1; --i) {
		if(aa[i] == 1) { seg[i] = i + 1; continue; }
		tmp.reset(); tmp.flip();
		for(auto it : deco[aa[i]]) {
			tmp &= bt[vist[it]];
			bt[vist[it]].flip(i-1);
		}
		seg[i] = n + 1;
        for(int k = i + 1; k <= n; ++k)
            if(tmp[k-1]) { seg[i] = k; break; }
        seg[i] = min(seg[i], seg[i + 1]);
	}
	for(int i = 1; i <= m; ++i) {
		int l, r;
		scanf("%d%d", &l, &r);
        printf(seg[l] <= r ? "S\n" : "N\n");
	}
	return 0;
}
