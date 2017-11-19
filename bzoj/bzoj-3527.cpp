#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
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
typedef complex<double> Comp;
const double PI = acos(-1.0);

const int maxn = 1 << 20;

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
                u = a[i], v = var * a[i + l/2];
                a[i] = u + v, a[i + l/2] = u - v;
                var *= step;
            }
        }
    }
    if(type == -1) for(i = 0; i < len; ++i) a[i] /= len;
}

Comp A[maxn + 5], B[maxn + 5];

int main() {
    int n;
    double a, b, c;
    scanf("%d", &n);
    FOR(i,0,n) scanf("%lf", &a), B[i] = a;
    for(int i = -(n-1); i <= (n-1); ++i) {
        if(i < 0) A[i+n] = double(-1) / i / i;
        else if(i > 0) A[i+n] = double(1) / i / i;
    }
    int len = 1;
    while(len < n*4) len <<= 1;
    FFT(A, len, 1);
    FFT(B, len, 1);
    for(int i = 0; i < len; ++i) A[i] *= B[i];
    FFT(A, len, -1);
    for(int i = 0; i < n; ++i)
        printf("%.3f\n", A[i+n].real());
    return 0;
}
