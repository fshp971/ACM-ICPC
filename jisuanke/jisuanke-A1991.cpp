// ICPC 2018 Shenyang Online C
#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define PER(i,a,b) for(int i = a; i >= b; --i)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
typedef long long LL;
typedef pair<int,int> pii;
typedef __int128 LINT;

typedef long long LL;
const int maxn = 1e5;
bool vis[maxn+5];
int prime[maxn+5], mu[maxn+5];
void mobius() {
    int tot = 0;
    mu[1] = 1;
    for(int i=2; i<=maxn; ++i) {
        if(!vis[i])
            prime[++tot] = i, mu[i] = -1;
        for(int k=1; k<=tot; ++k) {
            if((LL)prime[k] * i > maxn) break;
            vis[prime[k] * i] = true;
            if(i % prime[k]) mu[i * prime[k]] = -mu[i];
            else {
                mu[i * prime[k]] = 0;
                break;
            }
        }
    }
}

LL P;
LL Sqr(LL x) { return LINT(x)*x % P; }
LL S1(LL n) { return LINT(n)*(n+1) % (P*2) / 2; }
LL S2(LL n) { return LINT(n)*(n+1) % (P*6) * (n*2+1) % (P*6) / 6; }
LL S3(LL n) { return Sqr(S1(n)); }

LL F(LL n, LL d) {
    LL lim = n/d;
    LL ret = LINT(n+1) * S2(lim) % P;
    ret = (ret - LINT(d) * S3(lim) % P + P) % P;
    return ret;
}

int main() {
    mobius();
    LL n;
    while(~scanf("%lld%lld", &n, &P)) {
        LL ans = 0;
        for(LL i = 1; i*i <= n; ++i) {
            if(mu[i]==0) continue;
            LL tmp = i*i % P * i % P * i % P;
            tmp = LINT(tmp) * F(n,i*i) % P;
            if(mu[i]==1) ans = (ans + tmp) % P;
            else ans = (ans - tmp + P) % P;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
