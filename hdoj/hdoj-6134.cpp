#include<bits/stdc++.h>

using namespace std;

#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define FOR(i,a,b) for(int i = a; i < b; ++i)
#define mem(a,b) memset(a,b,sizeof(a))
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 1e6;
const int md = 1e9 + 7;

bool vis[maxn + 5];
int prime[maxn + 5];
LL S2[maxn + 5];
LL mu[maxn + 5];

void Mobius() {
	int tot = 0;
	mu[0] = 0, mu[1] = 1;
	for(int i = 2; i <= maxn; ++i) {
		if(!vis[i])
			prime[++tot] = i, mu[i] = -1;
		for(int k = 1; k <= tot; ++k) {
			if(LL(prime[k]) * i > maxn) break;
			vis[prime[k] * i] = true;
			if(i % prime[k]) mu[i * prime[k]] = -mu[i];
			else {
				mu[i * prime[k]] = 0;
				break;
			}
		}
	}
	for(int i = 1; i <= maxn; ++i)
		mu[i] = (mu[i] + mu[i-1] + md) % md;
}

LL Inc[maxn + 10], F[maxn + 2];

void Init() {
	LL tmp;
	for(int i = 2; i <= maxn; ++i) {
		Inc[i] = (Inc[i] + 1) % md;
		Inc[i + 1] = (Inc[i + 1] - 1) % md;
		for(LL j = i + 1, nx; j <= maxn; j = nx + 1) {
			nx = min(j + i - 1, LL(maxn));
			tmp = (j / i) + 1;
			Inc[j] = (Inc[j] + tmp) % md;
			Inc[nx + 1] = (Inc[nx + 1] - tmp + md) % md;
		}
	}
	LL det = 0;
	for(int i = 1; i <= maxn; ++i) {
		det = (det + Inc[i]) % md;
		F[i] = (F[i-1] + det + i) % md;
	}
}

int main() {
	S2[0] = 0;
	for(int i = 1; i <= maxn; ++i) {
		S2[i] = S2[i-1] + i;
		if(S2[i] >= md) S2[i] -= md;
	}

	Mobius();
	Init();
	int n;
	while(~scanf("%d", &n)) {
		LL ans = 0;
		for(int i = 1, nx; i <= n; i = nx + 1) {
			nx = n / (n / i);
			ans = (ans + (mu[nx] - mu[i-1] + md) * F[n/i]) % md;
		}
		printf("%lld\n", ans);
	}
	return 0;
}
