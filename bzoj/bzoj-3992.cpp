#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<cassert>
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

const int maxn = 1 << 14;
const LL P = (479 << 21) + 1, G = 3;

LL PowMod(LL a, LL b) { LL r=1; while(b) { if(b&1) r=r*a%P; a=a*a%P, b>>=1; } return r; }

void NTT(LL *a, int len, int type) {
    int i, j, k, l;
    for(i = 1, j = len>>1; i < len-1; ++i) {
        if(i < j) swap(a[i], a[j]);
        k = len>>1;
        while(j >= k) j -= k, k >>= 1;
        j += k;
    }
    LL var, step, u, v;
    for(l = 2; l <= len; l <<= 1) {
        step = PowMod(G, (P-1)/l);
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

int m, vist[maxn + 5];
int pw[maxn + 5], seg[maxn + 5];

int GetG(int n) {
    for(int g = 2; g < n; ++g) {
        bool fg = 1;
        for(int i = 0, now = 1; i < n-1; ++i, now = now*g % n) {
            if(vist[now] == g) { fg = 0; break; }
            vist[now] = g;
        }
        if(fg) return g;
    }
    return 0;
}

inline void Add(LL &a, LL b) { a+=b; if(a>=P) a-=P; }

LL AA[maxn + 5], BB[maxn + 5];
int main() {
    int n, x, S;
    scanf("%d%d%d%d", &n, &m, &x, &S);
    REP(i,1,S) scanf("%d", seg + i);
    int g = GetG(m), zero = 0;
    for(int i = 0, now = 1; i < m-1; ++i, now = now*g % m)
        pw[now] = i;
    REP(i,1,S) {
        if(seg[i]) AA[ pw[seg[i]] ] = 1;
        else ++zero;
    }
    if(x == 0) {
        if(zero) printf("%lld\n", (PowMod(S,n) - PowMod(S-1,n) + P) % P);
        else puts("0");
        exit(0);
    }
    BB[0] = 1;
    int len = 1;
    while(len < (m*2-3)) len <<= 1;
    while(n) {
        NTT(AA, len, 1);
        if(n&1) {
            NTT(BB, len, 1);
            FOR(i,0,len) BB[i] = (BB[i] * AA[i]) % P;
            NTT(BB, len, -1);
            for(int i = m-1; i < len; ++i) Add(BB[i-(m-1)], BB[i]), BB[i] = 0;
        }
        FOR(i,0,len) AA[i] = (AA[i] * AA[i]) % P;
        NTT(AA, len, -1);
        for(int i = m-1; i < len; ++i) Add(AA[i-(m-1)], AA[i]), AA[i] = 0;
        n >>= 1;
    }
    printf("%lld\n", BB[pw[x]]);
    return 0;
}
