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

const int maxn = 1100;
const int md = 1e9 + 7;

char str[maxn + 5];
int n, kk, num[maxn + 5];
int f[maxn + 5];
LL Fac[maxn + 5], InvFac[maxn + 5];

inline int bitcnt(int x) { int r=0; while(x) { r+=(x&1); x>>=1; } return r; }

LL PowMod(LL a, LL b) { LL r=1; while(b) { if(b&1) r=r*a%md; a=a*a%md, b>>=1; } return r; }

inline LL C(int tn, int tm) { return Fac[tn] * InvFac[tm] % md * InvFac[tn-tm] % md; }

void Upd(LL& a, LL b) { a = (a+b) % md; }

int main() {
    Fac[0] = 1;
    for(int i = 1; i <= maxn; ++i) Fac[i] = Fac[i-1] * i % md;
    InvFac[maxn] = PowMod(Fac[maxn], md-2);
    for(int i = maxn-1; i >= 0; --i) InvFac[i] = InvFac[i+1] * (i+1) % md;

    f[1] = 0; f[0] = -1;
    for(int i = 2; i <= maxn; ++i) f[i] = f[bitcnt(i)] + 1;
    scanf("%s", str);
    scanf("%d", &kk);
    if(kk == 0) { puts("1"); exit(0); }
    --kk;
    n = strlen(str);
    for(int i = 1; i <= n; ++i) num[i] = str[n-i] - '0';
    int cc = 0;
    LL ans = 0;
    for(int i = n; i >= 1; --i) {
        if(num[i] == 1) {
            for(int k = 0; k <= i-1; ++k) {
                if(f[k+cc] == kk)
                    Upd(ans, C(i-1,k));
            }
            ++cc;
        }
    }
    if(f[cc] == kk) Upd(ans, 1);
    if(kk+1 == 1) --ans;
    printf("%lld\n", ans);
    return 0;
}
