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

const int maxn = 5e6;

bool vis[maxn + 5];
int tot, prime[maxn + 5], mu[maxn + 5];
int ff[maxn + 5];

void Mobius() {
    tot = 0;
    mu[1] = 1;
    for(int i = 2; i <= maxn; ++i) {
        if(!vis[i]) prime[++tot] = i, mu[i] = -1;
        for(int k = 1; k <= tot; ++k) {
            if((LL)prime[k] * i > maxn) break;
            vis[prime[k] * i] = true;
            if(i % prime[k]) mu[i * prime[k]] = -mu[i];
            else { mu[i * prime[k]] = 0; break; }
        }
    }
    for(int i = 1; i <= tot; ++i)
        for(int k = 1; LL(prime[i]) * k <= maxn; ++k)
            ff[prime[i]*k] += mu[k];
    for(int i = 1; i <= maxn; ++i) ff[i] += ff[i-1];
}

int main() {
    Mobius();
    int T, n, m, lim;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &n, &m), lim = min(n, m);
        LL ans = 0;
        for(int i = 1, nx = 0; i <= lim; i = nx + 1) {
            nx = min(n/(n/i), m/(m/i));
            ans += LL(ff[nx] - ff[i-1]) * (n/i) * (m/i);
        }
        printf("%lld\n", ans);
    }
    return 0;
}
