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

const int maxn = 500;
const int Bin = 9;

int n;
LL P, f[maxn + 5][Bin + 5][maxn + 5];
LL C[maxn + 5][maxn + 5];
LL ans[maxn + 5];

inline void Add(LL &a, LL b) { a+=b; if(a>=P) a-=P; }

int main() {
    scanf("%d%lld", &n, &P);
    C[0][0] = 1;
    for(int i = 1; i <= n; ++i) {
        C[i][0] = 1;
        for(int k = 1; k <= i; ++k)
            C[i][k] = (C[i-1][k] + C[i-1][k-1]) % P;
    }
    int bin = 0;
    while(n > (1<<bin)) ++bin;
    for(int i = 1; i <= n; ++i) {
        f[i][0][0] = 1;
        for(int k = 1; k <= bin; ++k) {
            for(int s = 0; s <= n; ++s) {
                for(int t = 0; t*2 <= i && t*2 * (1<<(k-1)) <= s; ++t)
                    Add(f[i][k][s], C[i][t*2] * f[i][k-1][s - t*2*(1<<(k-1))] % P);
            }
        }
    }
    for(int i = 1; i <= n; ++i) {
        ans[i] = f[i][bin][n];
        for(int k = 1; k < i; ++k)
            Add(ans[i], C[i][k] * ans[k] % P * (P-1) % P);
        printf("%lld\n", ans[i]);
    }
    return 0;
}
