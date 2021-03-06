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

const double PI = acos(-1.0);
const int Bin = 17, maxn = 1 << Bin;

struct Comp {
    double re, im;
    Comp(): re(0), im(0) {}
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
    Comp conj() { return Comp(re, -im); }
};

vector<Comp> ww[Bin + 2];
void Init() {
    for(int i = 1, l = 2; l <= maxn; ++i, l <<= 1) {
        for(int k = 0; k < (l>>1); ++k)
            ww[i].PB( Comp( cos(PI*2*k/l), sin(PI*2*k/l) ) );
    }
}

void FFT(Comp *a, int len, int type) {
    int i, j, k, l, tt;
    for(i = 1, j = len>>1; i < len-1; ++i) {
        if(i<j) swap(a[i], a[j]);
        k = len >> 1;
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
void Conv(LL *a, LL *b, LL *c, int l1, int l2) {
    int len = 1;
    while(len < l1+l2-1) len <<= 1;
    for(int i = 0; i < l1; ++i) A[i].re = a[i];
    for(int i = l1; i < len; ++i) A[i].re = 0;
    for(int i = 0; i < l2; ++i) A[i].im = b[i];
    for(int i = l2; i < len; ++i) A[i].im = 0;
    FFT(A,len,1);
    for(int i = 0; i < len; ++i) {
        int j = (len-i) & (len-1);
        B[i] = (A[i]*A[i] - (A[j]*A[j]).conj()) * Comp(0,-0.25);
    }
    FFT(B,len,-1);
    for(int i = 0; i < len; ++i) c[i] = LL(B[i].re + 0.5);
}

int n, m;
LL aa[maxn + 5], bb[maxn + 5], cc[maxn + 5], f[maxn + 5];
LL BB[maxn + 5];
void Solve(int l, int r) {
    if(l == r) { f[0] += aa[l] * bb[l]; return; }
    int mid = (l + r) >> 1;
    Solve(l,mid); Solve(mid+1,r);
    Conv(aa + l, bb + mid+1, BB, mid-l+1, r-mid);
    for(int i = 0; i < r-l; ++i)
        f[i + l + mid+1] += BB[i];
    for(int i = l; i <= mid; ++i) cc[mid-i] = bb[i];
    Conv(cc, aa + mid+1, BB, mid-l+1, r-mid);
    for(int i = 0; i < r-l; ++i)
        f[i+1] += BB[i];
}

int main() {
    Init();
    int T, q, mx;
    scanf("%d", &T);
    while(T--) {
        mem(aa,0); mem(bb,0); mem(cc,0), mem(f,0);
        scanf("%d%d%d", &n, &m, &q);
        mx = 0;
        for(int i = 1, a; i <= n; ++i)
            scanf("%d", &a), ++aa[a], mx = max(mx,a);
        for(int i = 1, b; i <= m; ++i)
            scanf("%d", &b), ++bb[b], mx = max(mx,b);
        Solve(0,mx);
        while(q--) {
            int c; scanf("%d", &c);
            printf("%lld\n", f[c]);
        }
    }
    return 0;
}
