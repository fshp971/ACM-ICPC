#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define PER(i,a,b) for(int i = a; i >= b; --i)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 1e5;
const int P = 1e9+7;

int n, q, cc[70];
char s[maxn+5];
LL Fac[maxn+5], InvFac[maxn+5];
int f[maxn+5], g[maxn+5];
LL ans[70][70];

inline LL PowMod(LL a, LL b) { LL r=1; while(b) { if(b&1) r=r*a%P; a=a*a%P, b>>=1; } return r; }
template<class T> inline void Add(T &a, T b) { a+=b; if(a>=P) a-=P; }
template<class T> inline void Sub(T &a, T b) { a-=b; if(a<0) a+=P; }

int main() {
    Fac[0] = 1;
    REP(i,1,maxn) Fac[i] = Fac[i-1]*i % P;
    InvFac[maxn] = PowMod(Fac[maxn], P-2);
    PER(i,maxn-1,0) InvFac[i] = InvFac[i+1] * (i+1) % P;
    scanf("%s", s+1), n = strlen(s+1);
    for(int i = 1; i <= n; ++i) {
        int c = ('a'<=s[i]&&s[i]<='z') ? s[i]-'a' : s[i]-'A'+26;
        ++cc[c];
    }
    LL cof = Fac[n>>1] * Fac[n>>1] % P;
    REP(i,0,51) cof = cof * InvFac[cc[i]] % P;
    f[0] = 1;
    for(int i = 0; i < 52; ++i) {
        if(!cc[i]) continue;
        for(int k = n>>1; k >= cc[i]; --k)
            Add(f[k], f[k-cc[i]]);
    }
    REP(i,0,51) REP(k,i,51) {
        if(!cc[i] || !cc[k]) continue;
        if(i==k) {
            ans[i][k] = f[n>>1] * cof % P;
            continue;
        }
        memcpy(g, f, sizeof(int)*((n>>1)+1));
        for(int j = cc[i]; j <= (n>>1); ++j)
            Sub(g[j], g[j-cc[i]]);
        for(int j = cc[k]; j <= (n>>1); ++j)
            Sub(g[j], g[j-cc[k]]);
        for(int j = n>>1; j >= cc[i]+cc[k]; --j)
            Add(g[j], g[j-cc[i]-cc[k]]);
        ans[i][k] = ans[k][i] = g[n>>1] * cof % P;
    }
    scanf("%d", &q);
    while(q--) {
        int x,y; scanf("%d%d", &x, &y);
        int a = ('a'<=s[x]&&s[x]<='z') ? s[x]-'a' : s[x]-'A'+26;
        int b = ('a'<=s[y]&&s[y]<='z') ? s[y]-'a' : s[y]-'A'+26;
        printf("%lld\n", ans[a][b]);
    }
    return 0;
}
