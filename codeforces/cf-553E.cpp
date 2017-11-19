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

const int maxn = 50, maxm = 100, maxT = 1 << 16;
const LL INF = 1LL << 35;
const double PI = acos(-1.0);

struct Comp {
    double re, im;
    Comp(): re(0), im(0) {}
    Comp(const double &_re, const double &_im) { re = _re, im = _im; }
    Comp operator+(const Comp &a) const { return Comp(re+a.re, im+a.im); }
    Comp operator-(const Comp &a) const { return Comp(re-a.re, im-a.im); }
    Comp operator*(const Comp &a) const { return Comp(re*a.re-im*a.im, re*a.im+im*a.re); }
    Comp operator*(const double &a) const { return Comp(re*a, im*a); }
    Comp operator/(const double &a) const { return Comp(re/a, im/a); }
    void operator*=(const Comp &a) { *this = (*this) * a; }
    void operator/=(const double &a) { re/=a, im/=a; }
    Comp conj() { return Comp(re, -im); }
};

void FFT(Comp *a, int len, int type) {
    int i, j, k, l;
    for(i = 1, j = len >> 1; i < len - 1; ++i) {
        if(i < j) swap(a[i], a[j]);
        k = len >> 1;
        while(j >= k) j -= k, k >>= 1;
        j += k;
    }
    Comp var, step, u, v;
    for(l = 2; l <= len; l <<= 1) {
        step = Comp( cos(PI*2 / l * type), sin(PI*2 / l * type) );
        for(k = 0; k < len; k += l) {
            var = Comp(1,0);
            for(i = k; i < k+l/2; ++i) {
                u = a[i], v = var * a[i+l/2];
                a[i] = u+v, a[i+l/2] = u-v;
                var *= step;
            }
        }
    }
    if(type == -1) for(i = 0; i < len; ++i) a[i] /=len;
}

int n, m, T, X;
double f[maxn + 5][maxT + 5], S[maxm + 5][maxT + 5];
double P[maxm + 5][maxT + 5], SP[maxm + 5][maxT + 5];
Comp A[maxT + 5], B[maxT + 5];
int from[maxm + 5], to[maxm + 5], wi[maxm + 5];
LL dist[maxn + 5][maxn + 5];

void dfs(int l, int r) {
    if(l == r) {
        for(int i = 1; i <= m; ++i)
            f[from[i]][l] = min(f[from[i]][l], S[i][l] + wi[i]);
        return;
    }
    int mid = (l + r) >> 1, len = 1, L = r-l+1;
    dfs(mid + 1, r);
    while(len < (L + r - mid)) len <<= 1;
    for(int i = 1; i <= m; ++i) {
        for(int t = 0; t < len; ++t) A[t] = B[t] = Comp(0,0);
        for(int t = mid+1; t <= r; ++t) A[t-mid-1] = Comp(f[to[i]][t],0);
        for(int t = 1; t <= L; ++t) B[L-t] = Comp(P[i][t],0);
        FFT(A,len,1), FFT(B,len,1);
        for(int i = 0; i < len; ++i) B[i] *= A[i];
        FFT(B,len,-1);
        for(int t = l; t <= mid; ++t)
            S[i][t] += B[t+L-mid-1].re;
    }
    dfs(l, mid);
}

int main() {
    int a, b, c;
    scanf("%d%d%d%d", &n, &m, &T, &X);
    for(int i = 1; i <= n; ++i)
        for(int k = 1; k <= n; ++k)
            dist[i][k] = (i == k) ? 0 : INF;
    for(int i = 1; i <= m; ++i) {
        scanf("%d%d%d", from + i, to + i, wi + i);
        dist[from[i]][to[i]] = wi[i];
        for(int k = 1; k <= T; ++k)
            scanf("%d", &a), P[i][k] = a / 100000.0;
        for(int k = T; k >= 1; --k) SP[i][k] += SP[i][k+1] + P[i][k];
    }
    for(int k = 1; k <= n; ++k) {
        for(int i = 1; i <= n; ++i)
            for(int j = 1; j <= n; ++j) {
                if(i != k && k != j)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
    }
    for(int i = 1; i < n; ++i)
        for(int k = 0; k <= T; ++k)
            f[i][k] = INF;
    for(int i = 1; i <= m; ++i) {
        for(int t = 0; t <= T; ++t)
            S[i][t] += SP[i][T+1-t] * (dist[to[i]][n] + X);
    }
    dfs(0, T);
    printf("%.10f\n", f[1][0]);
    return 0;
}
