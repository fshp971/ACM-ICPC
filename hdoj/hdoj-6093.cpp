#include<bits/stdc++.h>

using namespace std;

#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define FOR(i,a,b) for(int i = a; i < b; ++i)
#define mem(a,b) memset(a,b,sizeof(a))
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 5000 + 10;
const int maxd = 1500;
const int md = 998244353;

int frac[maxd + 2], pre[maxd + 2];
char A[maxn + 2], B[maxn + 2];
int L_Len[maxd + 2];

int C[maxd + 10], tot, FuckD;
void GetLen(char *a, int len, int d) {
	static int TmpC[maxn + 2];
	int now = 0, base = 1;
	tot = 0;
	for(int i = 1; i <= len; ++i)
		TmpC[i] = a[len - i] - '0';
	while(len) {
		for(int k = len ; k > 1; --k) {
			TmpC[k-1] += TmpC[k] % d * 10;
			TmpC[k] /= d;
		}
		C[++tot] = TmpC[1] % d;
		TmpC[1] /= d;
		while(len > 0 && TmpC[len] == 0) --len;
	}
}

bool vist[maxd + 2];
int tree[maxd + 2];

void Add(int x) {
	for(; x <= FuckD; x += x & (-x))
		++tree[x];
}

int Sum(int x) {
	int res = 0;
	for(; x > 0; x -= x & (-x))
		res += tree[x];
	return res;
}

inline int Cont(int l, int r) {
	return (r - l + 1) - (Sum(r+1) - Sum(l));
}

int Run(char *a, int len) {
	int l = 2, r = maxd, dd = 0, t_len;

	t_len = (a[0] == '0') ? (len - 1) : len;
	while(l <= r) {
		int mid = (l + r) >> 1;
		if(t_len < L_Len[mid])
			dd = mid, r = mid - 1;
		else l = mid + 1;
	}
	if(dd - 1 <= 1) return 0;

	do {
		--dd;
		GetLen(a, len, dd);
	} while(tot < dd);

	if(tot > dd) return pre[dd - 1];

	LL ans = pre[dd - 2];
	bool hh = true;

	FuckD = dd;
	for(int i = 0; i <= FuckD; ++i)
		tree[i] = 0, vist[i] = 0;

	for(int i = tot; i >= 1; --i) {
		if(i == tot) {
			if(C[i] > 1)
				ans += LL(Cont(1, C[i]-1)) * frac[i-1] % md;
		}
		else
			ans += LL(Cont(0, C[i]-1)) * frac[i-1] % md;
		if(ans >= md) ans -= md;
		if(vist[C[i]]) {
			hh = false;
			break;
		}
		vist[C[i]] = 1;
		Add(C[i] + 1);
	}
	if(hh) ans = (ans + 1) % md;
	return ans;
}

int main() {
	frac[0] = 1, pre[0] = 0, L_Len[0] = 0;
	for(int i = 1; i <= maxd; ++i) {
		frac[i] = LL(frac[i-1]) * i % md;
		pre[i] = (LL(frac[i]) * i + pre[i-1]) % md;
		L_Len[i] = floor( log10(double(i)) * double(i-1) ) + 1;
	}
	int T, A_len, B_len, pt;
	scanf("%d", &T);
	while(T--) {
		scanf("%s", A), A_len = strlen(A);
		scanf("%s", B), B_len = strlen(B);
		pt = A_len - 1, --A[pt];
		while(A[pt] < '0')
			A[pt] += 10, --A[--pt];
		printf("%lld\n", (LL(Run(B, B_len)) - Run(A, A_len) + md) % md);
	}
	return 0;
}
