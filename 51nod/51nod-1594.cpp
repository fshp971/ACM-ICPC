//#include<cstdio>
#include<stdio.h>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<iostream>
#include<algorithm>
#include<vector>
#include<string>
#include<queue>
#include<utility>
#include<bitset>
#include<complex>
#include<map>
#include<set>
#include<unordered_map>
#include<unordered_set>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define PB push_back
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 2e6;

bool vis[maxn + 5];
int phi[maxn + 5], mu[maxn + 5], prime[maxn + 5];
void Init() {
    phi[1] = 1;
    for(int i = 2; i <= maxn; ++i) if(!phi[i]) {
        for(int k = i; k <= maxn; k += i) {
            if(!phi[k]) phi[k] = k;
            phi[k] = phi[k] / i * (i-1);
        }
    }
    int tot = 0; mu[1] = 1;
    for(int i = 2; i <= maxn; ++i) {
        if(!vis[i]) prime[++tot] = i, mu[i] = -1;
        for(int k = 1; k <= tot; ++k) {
            if(LL(prime[k]) * i > maxn) break;
            vis[prime[k] * i] = true;
            if(i % prime[k]) mu[i * prime[k]] = -mu[i];
            else { mu[i * prime[k]] = 0; break; }
        }
    }
}

int n, cnt[maxn + 5], f[maxn + 5];
int main() {
    Init();
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i) cnt[i] = f[i] = 0;
        for(int i = 1; i <= n; ++i) ++cnt[phi[i]];
        for(int i = 1; i <= n; ++i)
            for(int k = i; k <= n; k += i)
                f[i] += cnt[k];
        LL ans = 0;
        for(int i = 1; i <= n; ++i) {
            LL tmp = 0;
            for(int k = 1; k * i <= n; ++k) tmp += LL(mu[k]) * f[k*i] * f[k*i];
            ans += phi[i] * tmp;
        }
        printf("%lld\n", ans);
    }
    return 0;
}
