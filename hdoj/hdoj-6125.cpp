#include<bits/stdc++.h>

using namespace std;

#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define FOR(i,a,b) for(int i = a; i < b; ++i)
#define mem(a,b) memset(a,b,sizeof(a))
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 500;
const int md = 1e9 + 7;

vector<int> prime;
bool vist[maxn + 2];

void GetPrime() {
	prime.push_back(2);
	for(int i = 3; i <= maxn; i += 2) {
		if(!vist[i]) {
			prime.push_back(i);
			for(int k = i * i; k <= maxn; k += i)
				vist[k] = true;
		}
	}
}

int n, kk;
int sta1[maxn + 2], sta2[maxn + 2], tot1, tot2;
int f1[1 << 9][100 + 2][maxn + 2], f2[1 << 9][maxn + 2];
bool vis1[1 << 9][100 + 2][maxn + 2], vis2[1 << 9][maxn + 2];

int dfs2(int msk, int rem) {
	if(rem < 0) return 0;
	if(rem == 0) return 1;
	if(vis2[msk][rem])
		return f2[msk][rem];
	vis2[msk][rem] = 1;
	if(msk == 0)
		return f2[msk][rem] = 1;
	int pt = 10;
	while( !(msk & (1 << pt)) ) --pt;
	f2[msk][rem] = dfs2(msk ^ (1 << pt), rem);
	int tmp;
	for(int i = 0; i < (1 << pt); ++i)
		if( (i & msk) == i ) {
			tmp = sta1[pt];
			for(int j = 0; j < tot1; ++j) {
				if(i & (1 << j))
					tmp *= sta1[j];
				if(tmp > n) break; 
			}
			if(tmp <= n)
				f2[msk][rem] = (f2[msk][rem] + dfs2(msk ^ i ^ (1 << pt), rem - 1)) % md;
		}
	return f2[msk][rem];
}

int dfs1(int msk, int pt, int rem) {
	if(rem < 0) return 0;
	if(rem == 0) return 1;
	if(vis1[msk][pt][rem])
		return f1[msk][pt][rem];
	vis1[msk][pt][rem] = 1;
	if(pt == 0)
		return f1[msk][pt][rem] = dfs2(msk, rem) % md;
	int tmp;
	f1[msk][pt][rem] = dfs1(msk, pt - 1, rem);
	for(int i = 0; i < (1 << tot1); ++i)
		if( (i & msk) == i ) {
			tmp = sta2[pt];
			for(int j = 0; j < tot1; ++j) {
				if(i & (1 << j))
					tmp *= sta1[j];
				if(tmp > n) break;
			}
			if(tmp <= n)
				f1[msk][pt][rem] = (f1[msk][pt][rem] + dfs1(msk ^ i, pt - 1, rem - 1)) % md;
		}
	return f1[msk][pt][rem];
}

int main() {
	GetPrime();
	int T, pt;
	scanf("%d", &T);
	while(T--) {
		scanf("%d%d", &n, &kk);
		tot1 = tot2 = 0;
		for(auto it: prime) {
			if(it > n) break;
			if(it * it <= n)
				sta1[tot1++] = it;
			else sta2[++tot2] = it;
		}
		mem(vis1, 0), mem(vis2, 0);
		LL ans = (dfs1((1 << tot1) - 1, tot2, kk) + dfs1((1 << tot1) - 1, tot2, kk - 1)) % md;
		ans = (ans - 1 + md) % md;
		printf("%lld\n", ans);
	}
	return 0;
}
