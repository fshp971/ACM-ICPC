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

const int maxn = 50000, maxl = 1 << 17;
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

LL Fac[maxn + 5], InvFac[maxn + 5];
inline LL C(int n, int m) { return Fac[n] * InvFac[n-m] % P * InvFac[m] % P; }

vector<int> poly[50000 + 5];
priority_queue<pii> que;
LL A[maxl + 5], B[maxl + 5];

int main() {
    Fac[0] = 1;
    REP(i,1,maxn) Fac[i] = Fac[i-1] * i % P;
    InvFac[maxn] = PowMod(Fac[maxn], P-2);
    for(int i = maxn-1; i >= 0; --i) InvFac[i] = InvFac[i+1] * (i+1) % P;
    int n;
    scanf("%d", &n);
    for(int i = 1, a; i <= n; ++i) {
        scanf("%d", &a);
        poly[i].resize(a+1), que.push( MP(-(a+1),i) );
        poly[i][0] = 0;
        for(int k = 1; k <= a; ++k)
            poly[i][k] = C(a-1,k-1) * InvFac[k] % P;
    }
    while(que.size() > 1) {
        pii x = que.top(); que.pop();
        pii y = que.top(); que.pop();
        int l1 = -x.fi, l2 = -y.fi, len = 1;
        while(len < (l1+l2-1)) len <<= 1;
        FOR(i,0,l1) A[i] = poly[x.se][i];
        FOR(i,l1,len) A[i] = 0;
        FOR(i,0,l2) B[i] = poly[y.se][i];
        FOR(i,l2,len) B[i] = 0;
        NTT(A, len, 1); NTT(B, len, 1);
        FOR(i,0,len) A[i] = A[i] * B[i] % P;
        NTT(A, len, -1);
        poly[x.se].resize(l1+l2-1);
        FOR(i,0,l1+l2-1) poly[x.se][i] = A[i];
        que.push( MP(-(l1+l2-1), x.se) );
    }
    LL ans = 0;
    int x = que.top().se, sz = poly[x].size();
    for(int i = 1; i < sz; i += 2)
        ans = (ans + poly[x][i] * Fac[i] % P) % P;
    printf("%d %lld\n", (sz-1 == n) ? (n&1) : 499122177, ans);
    return 0;
}
