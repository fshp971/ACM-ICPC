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

const int maxk = 5000;
const int md = 1e9 + 7;

int n, kk;
int cof[maxk + 5][maxk + 5];

LL PowMod(LL a, LL b) { LL r=1; while(b) { if(b&1) r=r*a%md; a=a*a%md, b>>=1; } return r; }
inline void Upd(int &a, int b) { a += b; if(a >= md) a -= md; }

int main() {
    scanf("%d%d", &n, &kk);
    cof[0][0] = 1;
    for(int i = 0; i < kk; ++i) {
        for(int k = 0; k <= i; ++k) {
            Upd(cof[i+1][k], LL(cof[i][k]) * k % md);
            Upd(cof[i+1][k+1], LL(cof[i][k]) * (n-k) % md);
        }
    }
    LL ans = 0, tmp = PowMod(2, n), inv2 = PowMod(2, md-2);
    for(int i = 0; i <= kk; ++i) {
        ans = (ans + tmp * cof[kk][i]) % md;
        tmp = tmp * inv2 % md;
    }
    printf("%lld\n", ans);
    return 0;
}
