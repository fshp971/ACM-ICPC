#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 20000;
const int maxk = 230;
const LL INF = 1LL << 50;

int n, kk, md;
int S[maxn + 5];
LL f[maxk + 5][maxk + 5][2];

inline int NX(int x) { return x < md ? x : (x - md); }

int main() {
	int T;
	scanf("%d", &T);
	while(T--) {
		scanf("%d", &n);
		for(int i = 1; i <= n; ++i)
			scanf("%d", S + i), S[i] += S[i - 1];
		kk = sqrt(n << 1) + 1;
		int pos = 0;
		md = kk + 5;
		for(int i = 1; i <= kk; ++i)
			f[pos][i][0] = f[pos][i][1] = 0;
		pos = NX(pos - 1 + md);
		for(int i = n; i >= 1; --i, pos = NX(pos - 1 + md)) {
			for(int k = 1; k <= kk; ++k) {
				if(n - i + 1 < k) {
					f[pos][k][0] = f[pos][k][1] = 0;
					continue;
				}
				f[pos][k][0] = -INF, f[pos][k][1] = INF;
				f[pos][k][0] = f[NX(pos+k)][k][1] + S[i+k-1] - S[i-1];
				f[pos][k][1] = f[NX(pos+k)][k][0] - S[i+k-1] + S[i-1];
				if(n - i + 1 >= k + 1) {
					f[pos][k][0] = max(f[pos][k][0], f[NX(pos+k+1)][k+1][1] + S[i+k] - S[i-1]);
					f[pos][k][1] = min(f[pos][k][1], f[NX(pos+k+1)][k+1][0] - S[i+k] + S[i-1]);
				}

			}
		}
		printf("%lld\n", f[NX(pos+1)][1][0]);
	}
	return 0;
}
