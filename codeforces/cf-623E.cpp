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

const int maxn = 1 << 16, md = 1e9 + 7;
const int mmd = sqrt(md) + 1;
const double PI = acos(-1.0);

struct Comp {
    double re, im;
    Comp(): re(0), im(0) {}
    Comp(const double _re, const double _im) { re = _re; im = _im; }
    Comp operator+(const Comp &a) { return Comp(re+a.re, im+a.im); }
    Comp operator-(const Comp &a) { return Comp(re-a.re, im-a.im); }
    Comp operator*(const Comp &a) { return Comp(re*a.re-im*a.im, re*a.im+im*a.re); }
    Comp operator*(const double &a) { return Comp(re*a, im*a); }
    Comp operator/(const double &a) { return Comp(re/a, im/a); }
    void operator*=(const Comp &a) { (*this) = (*this) * a; }
    void operator+=(const Comp &a) { re += a.re; im += a.im; }
    void operator*=(const double &a) { re*=a; im*=a; }
    void operator/=(const double &a) { re/=a; im/=a; }
    Comp conj() { return Comp(re, -im); }
};

LL Fac[maxn + 5], InvFac[maxn + 5];
LL n, Pre[maxn + 5], ans[maxn + 5];
int kk;

vector<Comp> ww[18];
void Init() {
    for(int i = 1, l = 2; l <= maxn; ++i, l <<= 1) {
        for(int k = 0; k < l/2; ++k)
            ww[i].PB( Comp( cos(PI*2*k/l), sin(PI*2*k/l) ) );
    }
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
        for(int i = 0; i < l/2; ++i)
        for(k = 0; k < len; k += l) {
            for(i = k; i < k+l/2; ++i) {
                var = ww[tt][i-k];
                if(type == -1) var.im = -var.im;
                u = a[i], v = var * a[i+l/2];
                a[i] = u+v, a[i+l/2] = u-v;
            }
        }
    }
    if(type == -1) for(i = 0; i < len; ++i) a[i] /= len;
}

inline LL PowMod(LL a, LL b) { LL r=1; while(b) { if(b&1) r=r*a%md; a=a*a%md, b>>=1; } return r; }
inline LL C(int tn, int tm) { return Fac[tn]*InvFac[tm]%md*InvFac[tn-tm]%md; }

Comp A[maxn + 5], B[maxn + 5], D[maxn + 5], E[maxn + 5], F[maxn + 5];
Comp A0[maxn + 5], A1[maxn + 5], B0[maxn + 5], B1[maxn + 5];
void Conv(LL *a, LL *b, int len, LL step) {
    LL var = 1;
    for(int i = 0; i < len; ++i) {
        LL tmp = a[i]*var % md;
        A[i] = Comp(tmp/mmd, b[i]/mmd);
        B[i] = Comp(tmp%mmd, b[i]%mmd);
        var = var*step % md;
    }
    FFT(A, len, 1); FFT(B, len, 1);
    for(int i = 0; i < len; ++i) {
        int j = (len-i) & (len-1);
        D[i] = (A[i]*A[i] - (A[j]*A[j]).conj()) * Comp(0,-0.25);
        D[i] += (A[i]*B[i] - (A[j]*B[j]).conj()) * Comp(0.5,0);
        E[i] = (B[i]*B[i] - (B[j]*B[j]).conj()) * Comp(0,-0.25);
    }
    FFT(D, len, -1); FFT(E, len, -1);
    for(int i = 0; i < len; ++i) a[i] = 0;
    for(int i = 0; i <= kk; ++i)
        a[i] = (LL(D[i].re+0.5)%md*mmd*mmd%md + LL(D[i].im+0.5)%md*mmd%md + LL(E[i].re+0.5)%md)%md * InvFac[kk] % md;
}

int main() {
    Init();
    Fac[0] = 1;
    for(LL i = 1; i <= maxn; ++i) Fac[i] = Fac[i-1] * i % md;
    InvFac[maxn] = PowMod(Fac[maxn], md-2);
    for(LL i=maxn-1; i >= 0; --i) InvFac[i] = InvFac[i+1] * (i+1) % md;
    scanf("%lld%d", &n, &kk);
    if(n > kk) { puts("0"); return 0; }
    int len = 1;
    while(len < (kk+1)*2) len <<= 1;
    for(int i = 1; i <= kk; ++i) Pre[i] = C(kk,i) * Fac[kk-i]  % md;
    LL step = 2, var;
    ans[0] = Fac[kk];
    step = 2;
    int cnt = 0;
    while(n) {
        if(n&1) Conv(ans, Pre, len, step);
        Conv(Pre, Pre, len, step);
        step = step*step % md, n >>= 1;
    }
    LL sum = 0;
    for(int i = 1; i <= kk; ++i) sum = (sum + ans[i]*InvFac[kk-i]%md) % md;
    printf("%lld\n", sum);
    return 0;
}
