#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 2e6;
const int md = 1e9 + 7;

bool vist[maxn + 5];
int prime[maxn + 5];
int mu[maxn + 5];

inline LL PowMod(LL a, LL b) { LL r=1; while(b) { if(b&1) r=r*a%md; a=a*a%md, b>>=1; } return r; }

void Mobius() {
    int tot = 0;
    mu[1] = 1;
    for(int i = 2; i <= maxn; ++i) {
        if(!vist[i]) prime[++tot] = i, mu[i] = -1;
        for(int k = 1; k <= tot; ++k) {
            if((LL)prime[k] * i > maxn) break;
            vist[prime[k]*i] = true;
            if(i%prime[k]) mu[i*prime[k]] = -mu[i];
            else {
                mu[i*prime[k]] = 0;
                break;
            }
        }
    }
    for(int i = 1; i <= maxn; ++i)
        if(mu[i] < 0) mu[i] += md;
}

int n, kk, pw[maxn + 5];
LL del[maxn + 5];
int main() {
    Mobius();
    scanf("%d%d", &n, &kk);
    for(int i = 1; i <= kk; ++i) pw[i] = PowMod(i, n);
    for(int i = 1; i <= kk; ++i) {
        for(int k = i, t = 1; k <= kk; k += i, ++t)
            del[k] = (del[k] + (LL(pw[t]) - pw[t-1] + md) % md * mu[i]) % md;
    }
    LL ans = 0, tmp = 0;
    for(int i = 1; i <= kk; ++i) {
        tmp = (tmp + del[i]) % md;
        ans = (ans + (tmp^i)) % md;
    }
    printf("%lld\n", ans);
    return 0;
}
