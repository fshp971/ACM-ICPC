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

const int maxn = 2500, md = 1e9 + 7;

int n, m, cnt[maxn + 5];
LL ans = 0;
LL Fac[maxn + 5], InvFac[maxn + 5];
LL conf[maxn * 2 + 5];
vector<pii> G[maxn + 5];

inline LL PowMod(LL a, LL b) { LL r=1; while(b) { if(b&1) r=r*a%md; a=a*a%md, b>>=1; } return r; }
inline LL C(int tn, int tm) { return (tn >= tm) ? (Fac[tn] * InvFac[tm] % md * InvFac[tn-tm] % md) : 0; }

void dfs(int x, int pre, int val) {
    cnt[x] = 1;
    for(auto it : G[x])
        if(it.fi != pre)
            dfs(it.fi, x, it.se), cnt[x] += cnt[it.fi];
    LL det = cnt[x] * PowMod(n-cnt[x], md - 2) % md;
    LL res = 0, cf = 1;
    for(int i = 0; i <= m; ++i) {
        res = (res + conf[i] * cf % md * i) % md;
        cf = cf * det % md;
    }
    for(int i = m + 1; i <= (m << 1); ++i) {
        res = (res + conf[i]  * cf % md * ((m<<1) - i)) % md;
        cf = cf * det % md;
    }
    res = res * PowMod(n-cnt[x], m << 1) % md * val % md;
    ans = (ans + res) % md;
}

int main() {
    int u, v, l;
    Fac[0] = 1;
    for(int i = 1; i <= maxn; ++i) Fac[i] = Fac[i-1] * i % md;
    InvFac[maxn] = PowMod(Fac[maxn], md - 2);
    for(int i = maxn - 1; i >= 0; --i)
        InvFac[i] = InvFac[i+1] * (i+1) % md;
    scanf("%d%d", &n, &m);
    for(int i = 0; i <= m*2; ++i) {
        conf[i] = 0;
        for(int k = 0; k <= i; ++k)
            conf[i] = (conf[i] + C(m,k) * C(m,i-k) % md) % md;
    }
    for(int i = 1; i < n; ++i) {
        scanf("%d%d%d", &u, &v, &l);
        G[u].PB(MP(v,l)), G[v].PB(MP(u,l));
    }
    dfs(1, 0, 0);
    printf("%lld\n", ans);
    return 0;
}
