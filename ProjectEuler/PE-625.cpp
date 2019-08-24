// ans = 551614306
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

const int P = 998244353;
const int maxn = 1e7;

LL PowMod(LL a, LL b) { LL r=1; while(b) { if(b&1) r=r*a%P; a=a*a%P, b>>=1; } return r; }
const int inv2 = PowMod(2, P-2);

int phi[maxn+5], vis[maxn+5], prime[maxn+5];
void Pre() {
    phi[1] = 1;
    int top = 0;
    for(int i = 2; i <= maxn; ++i) {
        if(vis[i] == 0) prime[++top] = i, phi[i] = i-1;
        for(int k = 1; k <= top; ++k) {
            if(LL(i) * prime[k] > maxn) break;
            vis[i*prime[k]] = 1;
            if(i % prime[k]) phi[i*prime[k]] = phi[i] * (prime[k]-1);
            else { phi[i*prime[k]] = phi[i] * prime[k]; break; }
        }
    }
    for(int i = 1; i <= maxn; ++i)
        phi[i] = (phi[i-1] + phi[i]) % P;
}

LL S1(LL n) { n%=P; return n*(n+1) % P * inv2 % P; }

unordered_map<LL,int> Hash;
LL PHI(LL n) {
    if(n <= maxn) return phi[n];
    if(Hash.find(n) != Hash.end()) return Hash[n];
    LL res = 0;
    for(LL i = 2, nx; i <= n; i = nx+1) {
        nx = n/(n/i);
        res = (res + (nx-i+1)%P * PHI(n/i)) % P;
    }
    res = (S1(n) - res + P) % P;
    Hash[n] = res;
    return res;
}

int main() {
    Pre();
    LL n = 1e11;
    LL ans = 0;
    for(LL i = 1, nx; i <= n; i = nx+1) {
        nx = n/(n/i);
        ans = (ans + (S1(nx) - S1(i-1) + P) * PHI(n/i)) % P;
    }
    printf("%lld\n", ans);
    return 0;
}
