#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define FOR(i,a,b) for(int i = a; i < b; ++i)
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

namespace fastIO {
	#define BUF_SIZE 100000
	//fread -> read
	bool IOerror = 0;
	inline char nc() {
		static char buf[BUF_SIZE], *p1 = buf + BUF_SIZE, *pend = buf + BUF_SIZE;
		if(p1 == pend) {
			p1 = buf;
			pend = buf + fread(buf, 1, BUF_SIZE, stdin);
			if(pend == p1) {
				IOerror = 1;
				return -1;
			}
		}
		return *p1++;
	}
	inline bool blank(char ch) {
		return ch == ' ' || ch == '\n' || ch == '\r' || ch == '\t';
	}
	inline void read(int &x) {
		char ch;
		while(blank(ch = nc()));
		if(IOerror) return;
		for(x = ch - '0'; (ch = nc()) >= '0' && ch <= '9'; x = x * 10 + ch - '0');
	}
	#undef BUF_SIZE
};
using namespace fastIO;

const int maxn = 1e6, md = 1e9 + 7;

int n, arr[maxn + 2], Li[maxn + 2], Ri[maxn + 2];
LL fac[maxn + 2], inv_fac[maxn + 2];

inline LL PowMod(LL a, LL b) {
	LL res = 1;
	while(b) {
		if(b & 1) res = res * a % md;
		a = a * a % md, b >>= 1;
	}
	return res;
}

bool cmp(const int &a, const int &b) {
	if(Li[a] != Li[b]) return Li[a] < Li[b];
	return Ri[a] > Ri[b];
}

inline LL C(int n, int m) {
	return fac[n] * inv_fac[m] % md * inv_fac[n-m] % md;
}

LL build(int l, int r, int &pt) {
	if(l > r)
		return 1;
	if(pt > n || Li[arr[pt]] != l || Ri[arr[pt]] != r)
		return 0;
	int mid = arr[pt], ppt = ++pt, sz1, sz2;
	LL res1 = build(l, mid - 1, pt);
	sz1 = pt - ppt, ppt = pt;
	LL res2 = build(mid + 1, r, pt);
	sz2 = pt - ppt;
	return C(sz1 + sz2, sz1) * res1 % md * res2 % md;
}

int main() {
	fac[0] = inv_fac[0] = 1;
	for(int i = 1; i <= maxn; ++i) {
		fac[i] = fac[i-1] * i % md;
		inv_fac[i] = PowMod(fac[i], md - 2);
	}

	int T = 0, pt;
	while(read(n), !fastIO::IOerror) {
		REP(i,1,n) read(Li[i]), arr[i] = i;
		REP(i,1,n) read(Ri[i]);
		sort(arr + 1, arr + 1 + n, cmp);
		printf("Case #%d: %lld\n", ++T, build(1, n, pt = 1));
	}
	return 0;
}
