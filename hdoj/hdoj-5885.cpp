#include <bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
typedef long long LL;
typedef double DB;
typedef pair<int,int> pii;

const DB eps  = 1e-8;
template<class T> int cmp(const T &a, const T &b) {
    if(fabs(a-b) < eps) return 0;
    return a < b ? -1 : 1;
}

const int Bin = 20, maxn = 1 << Bin;
const DB PI = acos(-1.0);

struct Comp {
    DB re, im;
    Comp() : re(0), im(0) {}
    Comp(const DB _re, const DB _im) { re = _re, im = _im; }
    Comp operator+(const Comp &a) { return Comp(re+a.re, im+a.im); }
    Comp operator-(const Comp &a) { return Comp(re-a.re, im-a.im); }
    Comp operator*(const Comp &a) { return Comp(re*a.re-im*a.im, re*a.im+im*a.re); }
    Comp operator*(const DB &a) { return Comp(re*a, im*a); }
    Comp operator/(const DB &a) { return Comp(re/a, im/a); }
    void operator*=(const Comp &a) { (*this) = (*this) * a; }
    void operator+=(const Comp &a) { re+=a.re, im+=a.im; }
    void operator*=(const DB &a) { re*=a, im*=a; }
    void operator/=(const DB &a) { re/=a, im/=a; }
    Comp conj() { return Comp(re, -im); }
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
        k = len >> 1;
        while(j >= k) j -= k, k >>= 1;
        j += k;
    }
    Comp var, u, v;
    for(l = 2, tt = 1; l <= len; l <<= 1, ++tt) {
        for(k = 0; k < len; k += l) {
            for(i = k; i < k+(l>>1); ++i) {
                var = ww[tt][i-k];
                if(type == -1) var.im = -var.im;
                u = a[i], v = var * a[i+(l>>1)];
                a[i] = u+v, a[i+(l>>1)] = u-v;
            }
        }
    }
    if(type == -1) for(i = 0; i < len; ++i) a[i] /= len;
}

const int N = 500;

int n, m;
DB mmp[N + 5][N + 5];

Comp aa[maxn + 5], bb[maxn + 5];
int main() {
    Init();
    int rr, mm, nn, len, del;
    DB r;
    while(~scanf("%d%d%lf", &n, &m, &r)) {
        FOR(i,0,n) FOR(k,0,m) scanf("%lf", &mmp[i][k]);
        rr = floor(r), mm = m + (rr<<1), nn = n + (rr<<1);
        len = 1, del = rr*mm + rr;
        while(len < nn*mm) len <<= 1;
        assert(len <= maxn);
        FOR(i,0,len) aa[i] = Comp(0,0);
        FOR(i,0,n) FOR(k,0,m) aa[(i+rr) * mm + (k+rr)].re = mmp[i][k];
        REP(i,-rr,rr) REP(k,-rr,rr) {
            DB dis = sqrt(i*i + k*k);
            if(cmp(dis, r) == -1)
                aa[i * mm + k + del].im = 1.0 / (1.0+dis);
        }
        FFT(aa, len, 1);
        for(int i = 0; i < len; ++i) {
            int j = (len-i) & (len-1);
            bb[i] = (aa[i]*aa[i] - (aa[j]*aa[j]).conj()) * Comp(0,-0.25);
        }
        FFT(bb, len, -1);
        DB ans = 0;
        FOR(i,0,n) FOR(k,0,m) ans = max(ans, bb[(i+rr)*mm+k+rr+del].re);
        printf("%.3f\n", ans);
    }
    return 0;
}
