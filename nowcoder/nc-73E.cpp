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

const int maxl = 1 << 20;
const int P = 998244353, G = 3;

inline LL PowMod(LL a, LL b) { LL r=1; while(b) { if(b&1) r=r*a%P; a=a*a%P, b>>=1; } return r; }

void NTT(LL *a, int len, int type) {
    int i, j, k, l;
    for(int i = 1, j = len>>1; i < len-1; ++i) {
        if(i < j) swap(a[i], a[j]);
        k = len>>1;
        while(j >= k) j -= k, k >>= 1;
        j += k;
    }
    LL var, step, u, v;
    for(l = 2; l <= len; l <<= 1) {
        step = PowMod(G, (P-1) / l);
        for(k = 0; k < len; k += l) {
            var = 1;
            for(i = k; i < k+(l>>1); ++i) {
                u = a[i], v = var*a[i+(l>>1)] % P;
                a[i] = (u+v) % P;
                a[i+(l>>1)] = (u-v+P) % P;
                var = var*step % P;
            }
        }
    }
    if(type == -1) {
        for(i = 1; i < (len>>1); ++i) swap(a[i], a[len-i]);
        LL inv = PowMod(len, P-2);
        for(i = 0; i < len; ++i) a[i] = a[i]*inv % P;
    }
}

LL A[maxl + 5];
char str[1000010];
int main() {
    LL n = 0, kk;
    scanf("%s%lld", str, &kk);
    for(int i = 0; str[i] != '\0'; ++i)
        n = (n*10 + str[i]-'0') % (P-1);
    LL x = 1, step = PowMod(G, (P-1) / kk);
    for(int i = 0; i < kk; ++i)
        A[i] = PowMod((x+1) % P, n), x = x * step % P;
    NTT(A, kk, -1);
    LL ans = 0;
    for(int i = 0; i < kk; ++i) ans ^= A[i];
    printf("%lld\n", ans);
    return 0;
}
