#include<bits/stdc++.h>

using namespace std;

#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define FOR(i,a,b) for(int i = a; i < b; ++i)
#define mem(a,b) memset(a,b,sizeof(a))
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 1 << 20;

inline int BitCnt(LL x) {
	int res = 0;
	while(x) {
		if(x & 1) ++res;
		x >>= 1;
	}
	return res;
}

int G1[maxn + 2], G2[maxn + 2];
int f[maxn + 2];
bool vist[maxn + 2];
vector<pii> Nd;

int dfs(int msk, int cnt) {
	if(vist[msk]) return f[msk];
	vist[msk] = 1;
	if(msk == 0) return f[msk] = 0;
	if(BitCnt(msk) == 1) return f[msk] = 1;
	f[msk] = 0;
	for(int i = 0; i < cnt; ++i)
		if(msk & (1 << i)) {
			f[msk] = max(f[msk], dfs(msk ^ (1 << i), cnt));
		}
	return f[msk];
}

int main() {
	int n, kk, cnt1, cnt2, a;
	scanf("%d%d", &n, &kk);
	cnt1 = n / 2, cnt2 = n - cnt1;
	for(int i = 1; i <= n; ++i) {
		G1[i] = G2[i] = 0;
		for(int k = 0; k < cnt1; ++k) {
			scanf("%d", &a);
			G1[i] |= (a << k);
		}
		for(int k = 0; k < cnt2; ++k) {
			scanf("%d", &a);
			G2[i] |= (a << k);
		}
	}

	for(int i = 0; i < (1 << cnt1); ++i) {
		int fg = 1;
		for(int k = 0; k < cnt1; ++k) {
			if(i & (1 << k)) {
				if( (i ^ (1 << k)) != (i & G1[k + 1])) {
					fg = 0;
					break;
				}
			}
		}
		if(fg) Nd.push_back( MP(i, BitCnt(i)) );
	}

	for(int i = 0; i < (1 << cnt2); ++i) {
		int fg = 1;
		for(int k = 0; k < cnt2; ++k) {
			if(i & (1 << k)) {
				if( (i ^ (1 << k)) != (i & G2[k + 1 + cnt1])) {
					fg = 0;
					break;
				}
			}
		}
		if(fg) vist[i] = 1, f[i] = BitCnt(i);
	}

	int ans = 1;
	for(auto it: Nd) {
		int msk = (1 << cnt2) - 1;
		for(int i = 0; i < cnt1; ++i) {
			if(it.first & (1 << i)) {
				msk &= G2[i + 1];
			}
		}
		ans = max(ans, it.second + dfs(msk, cnt2));
	}
	printf("%.10f\n", double(kk * kk) * double(ans-1) / double(2.0 * ans));
	return 0;
}
