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

typedef complex<double> Comp;
const double PI = acos(-1.0);
const int maxn = 1 << 19;
const char AGCT[] = "AGCT";

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
            var = Comp(1, 0);
            for(i = k; i < k + l/2; ++i) {
                u = a[i], v = var * a[i+l/2];
                a[i] = u+v, a[i+l/2] = u-v;
                var *= step;
            }
        }
    }
    if(type == -1) for(i = 0; i < len; ++i) a[i] /= len;
}

int n, m, kk, llen;
char str1[maxn + 5], str2[maxn + 5];
Comp A[maxn + 5], B[maxn + 5];
bool ffg[maxn + 5];

void Run(char c) {
    for(int i = 0; i < llen; ++i) A[i] = B[i] = 0;
    int cont = 0, rc = 0;
    for(int i = 0; i < m; ++i) if(str2[i] == c) B[m-1-i] = 1, ++cont;
    if(!cont) return;
    for(int i = 0, k = 0; k < n; ++k) {
        if(str1[k] == c) ++rc;
        if(k - i > kk) {
            if(str1[i++] == c) --rc;
        }
        if(rc) A[k] = 1;
    }
    rc = 0;
    for(int i = n - 1, k = n - 1; i >= 0; --i) {
        if(str1[i] == c) ++rc;
        if(k - i > kk) {
            if(str1[k--] == c) --rc;
        }
        if(rc) A[i] = 1;
    }
    FFT(A, llen , 1), FFT(B, llen, 1);
    for(int i = 0; i < llen; ++i) A[i] *= B[i];
    FFT(A, llen, -1);
    for(int i = m - 1; i < n; ++i) ffg[i] &= int(A[i].real() + 0.5) == cont;
}

int main() {
    scanf("%d%d%d", &n, &m, &kk);
    scanf("%s%s", str1, str2);
    int ans = 0;
    llen = 1;
    while(llen < n + m) llen <<= 1;
    for(int i = m - 1; i < n; ++i) ffg[i] = 1;
    for(int i = 0; i < 4; ++i) Run(AGCT[i]);
    for(int i = m - 1; i < n; ++i) ans += ffg[i];
    printf("%d\n", ans);
    return 0;
}
