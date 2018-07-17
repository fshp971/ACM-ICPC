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
typedef double DB;
typedef pair<int,int> pii;

const double PI = acos(-1.0);
const int Bin = 21, maxn = 1 << Bin;

struct Comp {
    DB re, im;
    Comp() : re(0), im(0) {}
    Comp(const DB _re, const DB _im) { re = _re; im = _im; }
    Comp operator+(const Comp &a) { return Comp(re+a.re, im+a.im); }
    Comp operator-(const Comp &a) { return Comp(re-a.re, im-a.im); }
    Comp operator*(const Comp &a) { return Comp(re*a.re-im*a.im, re*a.im+im*a.re); }
    Comp operator*(const DB &a) { return Comp(re*a, im*a); }
    Comp operator/(const DB &a) { return Comp(re/a, im/a); }
    void operator*=(const Comp &a) { (*this) = (*this) * a; }
    void operator+=(const Comp &a) { re += a.re; im += a.im; }
    void operator*=(const DB &a) { re*=a; im*=a; }
    void operator/=(const DB &a) { re/=a; im/=a; }
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

Comp A[maxn + 5], B[maxn + 5];
void Conv(LL *a, LL *b, LL *c, int len) {
    for(int i = 0; i < len; ++i) A[i] = Comp(a[i], b[i]);
    FFT(A, len, 1);
    for(int i = 0; i < len; ++i) {
        int j = (len-i) & (len-1);
        B[i] = (A[i]*A[i] - (A[j]*A[j]).conj()) * Comp(0,-0.25);
    }
    FFT(B, len, -1);
    for(int i = 0; i < len; ++i) c[i] = LL(B[i].re+0.5);
}

int n, m;
char mmp[705][705];
bool ok[705][705], vist[705][705];
LL aa[maxn + 5], bb[maxn + 5];

void dfs(int x, int y) {
    if(x < 0 || y >= n || y < 0 || y >= m || vist[x][y] || !ok[x][y]) return;
    vist[x][y] = 1;
    dfs(x+1,y); dfs(x-1,y); dfs(x,y+1); dfs(x,y-1);
}

int main() {
    Init();
    scanf("%d%d", &n, &m);
    int lx = n, ly = m, rx = -1, ry = -1;
    int len = 1, M = (m<<1) - 1;
    int all = (n*2 - 2) * M + (m*2 - 2) + 1;
    while(len < all) len <<= 1;

    all = 0;
    for(int i = 0; i < n; ++i) {
        scanf("%s", mmp[i]);
        for(int k = 0; k < m; ++k) {
            if(mmp[i][k] != '#')
                aa[i*M + k] = 1;
            if(mmp[i][k] == 'o') {
                lx = min(lx,i), ly = min(ly,k);
                rx = max(rx,i), ry = max(ry,k);
                ++all;
            }
        }
    }
    FOR(i,0,n) FOR(k,0,m) {
        if(mmp[i][k] == 'o')
            bb[ (rx-i) * M + (ry-k) ] = 1;
    }
    Conv(aa, bb, aa, len);
    for(int i = 0; i <= (n-1); ++i) {
        for(int k = 0; k <= (m-1); ++k) {
            int c = (i+rx-lx) * M + (k+ry-ly);
            ok[i][k] = (aa[c] == all);
        }
    }
    dfs(lx,ly);
    mem(aa, 0), mem(bb, 0);
    for(int i = 0; i <= (n-1); ++i) {
        for(int k = 0; k <= (m-1); ++k) {
            aa[i*M + k] = vist[i][k];
            if(mmp[i][k] == 'o')
                bb[ (i-lx)*M + (k-ly) ] = 1;
        }
    }
    Conv(aa, bb, aa, len);
    int ans = 0;
    for(int i = 0; i < len; ++i) ans += (aa[i] > 0);
    printf("%d\n", ans);
    return 0;
}
