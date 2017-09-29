#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define PB push_back
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 2100;
const int md = 998244353;

int n;
vector<int> seg1, seg2;
LL f[2][maxn + 5][11], fac[maxn + 5];

pii Calc(int x) {
    int len = 0, res = 0;
    while(x) {
        len ^= 1;
        res = (res + (len ? 1 : -1) * (x % 10) + 11) % 11;
        x /= 10;
    }
    return MP(len, res);
}

inline void Add(LL &a, LL b) { a = (a + b) % md; }

int main() {
    fac[0] = 1;
    for(int i = 1; i <= maxn; ++i)
        fac[i] = fac[i-1] * i % md;
    int T, u, par;
    scanf("%d", &T);
    while(T--) {
        seg1.clear(); seg2.clear();
        scanf("%d", &n);
        for(int i = 1; i <= n; ++i) {
            scanf("%d", &u);
            pii ret = Calc(u);
            if(ret.first & 1) seg1.PB(ret.second);
            else seg2.PB(ret.second);
        }
        par = 0;
        mem(f[par], 0), f[par][0][0] = 1;
        for(int i = 0; i < seg1.size(); ++i) {
            par ^= 1;
            for(int k = 0; k <= i + 1; ++k)
                for(int j = 0; j < 11; ++j)
                    f[par][k][j] = 0;
            for(int k = 0; k <= i; ++k)
                for(int j = 0; j < 11; ++j) {
                    Add(f[par][k+1][(j+seg1[i])%11], f[par^1][k][j]);
                    Add(f[par][k][(j-seg1[i]+11)%11], f[par^1][k][j]);
                }
        }
        int c1 = (seg1.size() + 1) >> 1, c2 = (seg1.size() + 2) >> 1;
        LL cnt = fac[c1] * fac[seg1.size() - c1] % md;
        par ^= 1, mem(f[par], 0);
        for(int i = 0; i < 11; ++i)
            f[par][c2][i] = f[par^1][c1][i] * cnt % md;
        for(int i = 0, cc = seg1.size(); i < seg2.size(); ++i, ++cc) {
            par ^= 1;
            for(int k = 0; k <= cc + 2; ++k)
                for(int j = 0; j < 11; ++j)
                    f[par][k][j] = 0;
            for(int k = 0; k <= cc + 1; ++k)
                for(int j = 0; j < 11; ++j) {
                    Add(f[par][k+1][(j+seg2[i])%11], f[par^1][k][j] * k);
                    Add(f[par][k][(j-seg2[i]+11)%11], f[par^1][k][j] * (cc+1-k));
                }
        }
        LL ans = 0;
        for(int i = 0; i <= n + 1; ++i)
            Add(ans, f[par][i][0]);
        printf("%lld\n", ans);
    }
    return 0;
}
