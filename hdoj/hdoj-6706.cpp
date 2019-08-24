#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define PER(i,a,b) for(int i = a; i >= b; --i)
#define PB push_back
#define MP make_pair
#define fi first
#define se second
typedef long long LL;
typedef double DB;

const int maxn = 1e6;
const int P = 1e9+7;

bool vis[maxn+5];
int prime[maxn+5];
int phi[maxn+5];

LL PowMod(LL a, LL b) { LL r=1; while(b) { if(b&1) r=r*a%P; a=a*a%P, b>>=1; } return r; }
const LL inv6 = PowMod(6, P-2);
const LL inv2 = PowMod(2, P-2);

void Pre() {
    int tot = 0;
    phi[1] = 1;
    for(int i = 2; i <= maxn; ++i) {
        if(!vis[i]) prime[++tot] = i, phi[i] = i-1;
        for(int k = 1; k <= tot; ++k) {
            if(LL(prime[k]) * i > maxn) break;
            vis[prime[k] * i] = 1;
            if(i % prime[k]) phi[i * prime[k]] = phi[i] * (prime[k]-1);
            else {
                phi[i*prime[k]] = phi[i] * prime[k];
                break;
            }
        }
    }
    REP(i,1,maxn) phi[i] = (phi[i-1] + LL(i) * phi[i]) % P;
}

LL S2(LL n) {
    return n * (n+1) % P * (n*2+1) % P * inv6 % P;
}

LL S1(LL n) {
    return n * (n+1) % P * inv2 % P;
}

unordered_map<int,int> Hash;
LL S(int n) {
    if(n <= maxn) return phi[n];
    if(Hash.find(n) != Hash.end()) return Hash[n];
    LL res = 0;
    for(int i = 2, nx; i <= n; i = nx+1) {
        nx = n / (n/i);
        res = (res + (S1(nx) - S1(i-1) + P) * S(n/i)) % P;
    }
    res = (S2(n) - res + P) % P;
    Hash[n] = res;
    return res;
}

int main() {
    Pre();
    int _; scanf("%d", &_);
    while(_--) {
        int n, a, b;
        scanf("%d%d%d", &n, &a, &b);
        LL ans = (S(n) - 1 + P) * inv2 % P;
        printf("%lld\n", ans);
    }
    return 0;
}
