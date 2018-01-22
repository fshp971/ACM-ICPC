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

const int maxn = 1 << 17;
const int md = 1e9 + 7;

inline LL PowMod(LL a, LL b) { LL r=1; while(b) { if(b&1) r=r*a%md; a=a*a%md, b>>=1; } return r; }
inline int bitcnt(int x) { int r=0; while(x) r+=x&1, x>>=1; return r; }

LL inv2 = PowMod(2, md-2);

void FWT1(LL *a, int len, int type) { //XOR
    for(int l = 1; l < len; l <<= 1) {
        for(int i = 0; i < len; i += (l << 1))
            for(int k = 0; k < l; ++k) {
                LL x = a[i+k], y = a[i+k+l];
                if(type == 1) {
                    a[i+k] = (x+y) % md;
                    a[i+k+l] = (x-y+md) % md;
                }
                else {
                    a[i+k] = (x+y)%md * inv2 % md;
                    a[i+k+l] = (x-y+md)%md * inv2 % md;
                }
            }
    }
}

void FWT2(LL *a, int len, int type) { //AND
    for(int l = 1; l < len; l <<= 1) {
        for(int i = 0; i < len; i += (l << 1))
            for(int k = 0; k < l; ++k) {
                LL x = a[i+k], y = a[i+k+l];
                if(type == 1) a[i+k] = (x+y) % md;
                else a[i+k] = (x-y+md) % md;
            }
    }
}

void FWT3(LL a[][18], int len, int type) { //OR
    for(int l = 1; l < len; l <<= 1) {
        for(int i = 0; i < len; i += (l << 1))
            for(int k = 0; k < l; ++k) {
                for(int t = 0; t <= 17; ++t) {
                    LL x = a[i+k][t], y = a[i+k+l][t];
                    if(type == 1) a[i+k+l][t] = (x+y) % md;
                    else a[i+k+l][t] = (y-x+md) % md;
                }
            }
    }
}

int n;
LL fib[maxn + 5], S[maxn + 5];
LL A[maxn + 5][18], B[maxn + 5], C[maxn + 5];

int main() {
    fib[0] = 0, fib[1] = 1;
    for(int i = 2; i < maxn; ++i) fib[i] = (fib[i-1] + fib[i-2]) % md;
    int a, len = maxn;
    LL buf[18];
    scanf("%d", &n);
    REP(i,1,n) scanf("%d", &a), ++S[a];
    for(int i = 0; i < len; ++i) A[i][bitcnt(i)] = S[i];
    FWT3(A, len, 1);
    for(int i = 0; i < len; ++i) {
        mem(buf, 0);
        for(int k = 0; k <= 17; ++k)
            for(int j = 0; k+j <= 17; ++j)
                buf[k+j] = (buf[k+j] + A[i][k] * A[i][j]) % md;
        for(int k = 0; k <= 17; ++k) A[i][k] = buf[k];
    }
    FWT3(A, len, -1);
    for(int i = 0; i < len; ++i) B[i] = A[i][bitcnt(i)];
    for(int i = 0; i < len; ++i) C[i] = S[i];
    FWT1(C, len, 1);
    for(int i = 0; i < len; ++i) C[i] = C[i]*C[i] % md;
    FWT1(C, len, -1);
    for(int i = 0; i < len; ++i) {
        B[i] = B[i] * fib[i] % md;
        C[i] = C[i] * fib[i] % md;
        S[i] = S[i] * fib[i] % md;
    }
    FWT2(B, len, 1), FWT2(C, len, 1), FWT2(S, len, 1);
    for(int i = 0; i < len; ++i)
        B[i] = B[i] * C[i] % md * S[i] % md;
    FWT2(B, len, -1);
    LL ans = 0;
    for(int i = 0; i < 17; ++i)
        ans = (ans + B[1<<i]) % md;
    printf("%lld\n", ans);
    return 0;
}
