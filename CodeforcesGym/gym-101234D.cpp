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

const int md = 1e9 + 7;
const int Bin = 17, maxn = 1 << Bin;
const double PI = acos(-1.0);

struct Comp {
    double re, im;
    Comp() : re(0), im(0) {}
    Comp(const double _re, const double _im) { re = _re, im = _im; }
    Comp operator+(const Comp &a) { return Comp(re+a.re, im+a.im); }
    Comp operator-(const Comp &a) { return Comp(re-a.re, im-a.im); }
    Comp operator*(const Comp &a) { return Comp(re*a.re-im*a.im, re*a.im+im*a.re); }
    Comp operator*(const double &a) { return Comp(re*a, im*a); }
    Comp operator/(const double &a) { return Comp(re/a, im/a); }
    void operator*=(const Comp &a) { (*this) = (*this) * a; }
    void operator+=(const Comp &a) { re += a.re, im += a.im; }
    void operator*=(const double &a) { re *= a, im *= a; }
    void operator/=(const double &a) { re /= a, im /= a; }
    Comp conj() { return Comp(re,-im); }
};

vector<Comp> ww[Bin + 2];
void Init() {
    for(int i = 1, l = 2; l <= maxn; ++i, l <<= 1)
        for(int k = 0; k < (l>>1); ++k)
            ww[i].PB( Comp(cos(PI*2*k/l), sin(PI*2*k/l)) );
}

void FFT(Comp *a, int len, int type) {
    int i, j, k, l, tt;
    for(i = 1, j = len>>1; i < len-1; ++i) {
        if(i < j) swap(a[i], a[j]);
        k = len>>1;
        while(j >= k) j -= k, k >>= 1;
        j += k;
    }
    Comp var, u, v;
    for(l = 2, tt = 1; l <= len; l <<= 1, ++tt) {
        for(k = 0; k < len; k += l) {
            for(i = k; i < k + (l>>1); ++i) {
                var = ww[tt][i-k];
                if(type == -1) var.im = -var.im;
                u = a[i], v = var * a[i+(l>>1)];
                a[i] = u+v, a[i+(l>>1)] = u-v;
            }
        }
    }
    if(type == -1) for(i = 0; i < len; ++i) a[i] /= len;
}

Comp A[maxn + 5], B[maxn + 5];
void Conv(vector<LL> &a, vector<LL> &b, LL *c) {
    int l1 = a.size(), l2 = b.size(), len = 1;
    while(len < l1+l2-1) len <<= 1;
    for(int i = 0; i < l1; ++i) A[i].re = a[i];
    for(int i = l1; i < len; ++i) A[i].re = 0;
    for(int i = 0; i < l2; ++i) A[i].im = b[i];
    for(int i = l2; i < len; ++i) A[i].im = 0;
    FFT(A, len, 1);
    for(int i = 0; i < len; ++i) {
        int j = (len-i) & (len-1);
        B[i] = (A[i]*A[i] - (A[j]*A[j]).conj()) * Comp(0,-0.25);
    }
    FFT(B, len, -1);
    for(int i = 0; i < len; ++i) c[i] += LL(B[i].re+0.5) << 1;
}

inline LL PowMod(LL a, LL b) { LL r=1; while(b) { if(b&1) r=r*a%md; a=a*a%md, b>>=1; } return r; }

int n, sz[maxn + 5];
LL f[maxn + 5];
bool vist[maxn + 5];
vector<int> G[maxn + 5];

int FindRoot(int x, int p, int all) {
    int res = 0, fg = 1;
    sz[x] = 1;
    for(auto it : G[x])
        if(it != p && !vist[it]) {
            res = max(res, FindRoot(it, x, all));
            sz[x] += sz[it];
            fg &= (sz[it] << 1) <= all;
        }
    fg &= ((all-sz[x]) << 1) <= all;
    if(fg) res = x;
    return res;
}

void dfs(int x, int p, int d, vector<LL> &cnt) {
    sz[x] = 1;
    while(d >= cnt.size()) cnt.PB(0);
    ++cnt[d];
    for(auto it : G[x])
        if(it != p && !vist[it])
            dfs(it, x, d+1, cnt), sz[x] += sz[it];
}

vector<LL> poly[2];
void Solve(int x, int all) {
    x = FindRoot(x, 0, all);
    ++f[0];
    int par = 0;
    poly[0].clear(); poly[1].clear();
    poly[0].PB(1);
    for(auto it : G[x]) {
        if(vist[it]) continue;
        poly[par^1].clear();
        dfs(it, x, 1, poly[par^1]);
        Conv(poly[0], poly[1], f);
        if(poly[par].size() < poly[par^1].size()) par ^= 1;
        for(int i = 0; i < poly[par^1].size(); ++i)
            poly[par][i] += poly[par^1][i];
    }
    vist[x] = 1;
    for(auto it : G[x])
        if(!vist[it]) Solve(it, sz[it]);
}

int main() {
    Init();
    scanf("%d", &n);
    for(int i = 1, u, v; i < n; ++i) {
        scanf("%d%d", &u, &v);
        G[u].PB(v), G[v].PB(u);
    }
    Solve(1, n-1);
    LL ans = 0;
    for(int i = 0; i < n; ++i)
        ans = (ans + f[i] % md * PowMod(i+1, md-2)) % md;
    for(int i = 1; i <= n; ++i) ans = ans * i % md;
    printf("%lld\n", ans);
    return 0;
}
