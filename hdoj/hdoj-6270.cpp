
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
#include<unordered_map>
#include<unordered_set>
#include<stack>

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

const LL P = ((7 * 17) << 23) + 1, G = 3;
const int maxn = 1 << 18;

inline LL PowMod(LL a, LL b) { LL r=1; while(b) { if(b&1) r=r*a%P; a=a*a%P, b>>=1; } return r; }

void NTT(LL *a, int len, int type) {
    int i, j, k ,l;
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
                u = a[i], v = var * a[i+(l>>1)] % P;
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

int n, ai[maxn + 5], bi[maxn + 5];
vector<LL> poly[maxn + 5];
priority_queue<pii> que;

LL A[maxn + 5], B[maxn + 5];
void Conv(vector<LL> &v1, vector<LL> &v2) {
    int l1 = v1.size(), l2 = v2.size(), len = 1;
    while(len < l1+l2-1) len <<= 1;
    for(int i = 0; i < l1; ++i) A[i] = v1[i];
    for(int i = l1; i < len; ++i) A[i] = 0;
    for(int i = 0; i < l2; ++i) B[i] = v2[i];
    for(int i = l2; i < len; ++i) B[i] = 0;
    NTT(A,len,1), NTT(B,len,1);
    for(int i = 0; i < len; ++i) A[i] = A[i] * B[i] % P;
    NTT(A,len,-1);
    l1 = l1+l2-1; v1.resize(l1);
    for(int i = 0; i < l1; ++i) v1[i] = A[i];
    v2.clear();
}

int main() {
    Fac[0] = 1;
    for(int i = 1; i <= maxn; ++i) Fac[i] = Fac[i-1] * i % P;
    InvFac[maxn] = PowMod(Fac[maxn], P-2);
    for(int i = maxn-1; i >= 0; --i) InvFac[i] = InvFac[i+1] * (i+1) % P;
    int T;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        int sum = 0;
        REP(i,1,n) scanf("%d%d", ai+i, bi+i), sum += ai[i];
        for(int i = 1; i <= n; ++i) {
            int len = min(ai[i], bi[i]) + 1;
            poly[i].resize(len);
            for(int k = 0; k < len; ++k)
                poly[i][k] = C(ai[i],k) * C(bi[i],k) % P * Fac[k] % P;
            que.push( MP(-len, i) );
        }
        while(que.size() > 1) {
            int x = que.top().se; que.pop();
            int y = que.top().se; que.pop();
            Conv(poly[x], poly[y]);
            que.push( MP(-poly[x].size(), x) );
        }
        int xx = que.top().se; que.pop();
        LL ans = 0;
        for(int i = 0; i < poly[xx].size(); ++i) {
            if(i&1) ans = (ans - Fac[sum-i] * poly[xx][i] % P + P) % P;
            else ans = (ans + Fac[sum-i] * poly[xx][i]) % P;
        }
        printf("%lld\n", ans);
        poly[xx].clear();
    }
    return 0;
}
