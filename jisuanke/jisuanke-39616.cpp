// 计蒜之道2019 复赛 F - 多重积分
#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define PER(i,a,b) for(int i = a; i >= b; --i)
#define PB push_back
#define MP make_pair
typedef long long LL;
typedef double DB;

const int maxn = 1e6;

int n, P;
char s[int(1e5)+10];
bool vis[maxn+5];
int prime[maxn+5], mu[maxn+5];
int fac[30], ck[30], md[30][40], top = 0;
int cg[30], rm[30];
LL cof[30], fun[maxn+5];

LL PowMod(LL a, LL b, LL p) { LL r=1; while(b) { if(b&1) r=r*a%p; a=a*a%p, b>>=1; } return r; }

void Pre() {
    int tot = 0;
    mu[1] = 1;
    for(int i = 2; i <= maxn; ++i) {
        if(!vis[i]) prime[++tot] = i, mu[i] = -1;
        for(int k = 1; k <= tot; ++k) {
            if(LL(prime[k])*i > maxn) break;
            vis[prime[k]*i] = 1;
            if(i%prime[k]) mu[i*prime[k]] = -mu[i];
            else {
                mu[i*prime[k]] = 0;
                break;
            }
        }
    }

    for(int i = 1; i <= maxn; ++i) {
        int key = i%P;
        for(int k = 1; k*i <= maxn; ++k) {
            fun[i*k] += mu[k]*key;
            if(fun[i*k] >= P) fun[i*k] -= P;
            else if(fun[i*k] < 0) fun[i*k] += P;
        }
    }

    int tmpP = P;
    for(int i = 2; i*i <= tmpP; ++i) {
        if(tmpP%i) continue;
        fac[top] = i;
        while(tmpP%i == 0) tmpP/=i, ++ck[top];
        ++top;
    }
    if(tmpP > 1) fac[top] = tmpP, ck[top] = 1, ++top;

    int len = strlen(s);
    for(int i = 0; i < top; ++i) {
        md[i][0] = 1;
        REP(k,1,ck[i]) md[i][k] = md[i][k-1] * fac[i];

        rm[i] = 0;
        for(int k = 0; k < len; ++k)
            rm[i] = (rm[i]*10LL + s[k]-'0') % (md[i][ck[i]]-ck[i]);

        cg[i] = 0;
        for(int k = len-1; k >= 0; --k) {
            cg[i] = cg[i]*10 + s[k]-'0';
            if(cg[i] >= ck[i]) break;
        }

        cof[i] = (P/md[i][ck[i]]) * PowMod(P/md[i][ck[i]]%md[i][ck[i]], md[i][ck[i]]-ck[i]-1, md[i][ck[i]]) % P;
    }
}

LL S1(LL n) {
    if(n&1) return ((n+1)>>1) * n % P;
    return (n>>1) * (n+1) % P;
}

LL GP(int v, int ps) {
    int t = 0;
    while(v%fac[ps]==0) v/=fac[ps], ++t;
    if(t*cg[ps] >= ck[ps]) return 0LL;
    return PowMod(v%md[ps][ck[ps]], rm[ps], md[ps][ck[ps]]) * md[ps][t*cg[ps]] % md[ps][ck[ps]];
}

LL CRT(int x) {
    if(x <= 1) return x;
    LL res = 0;
    for(int j = 0; j < top; ++j)
        res = (res + GP(x, j) * cof[j]) % P;
    return res;
}

int main() {
    scanf("%d", &n);
    scanf("%s", s);
    scanf("%d", &P);
    if(P == 1) exit( puts("0")*0 );
    Pre();
    LL ans = 0;
    for(int i = 1; i <= n; ++i) {
        int val = (2LL * i * S1(n/i) + n/i) % P;
        ans = (ans + fun[i] * CRT(val)) % P;
    }
    printf("%lld\n", ans);
    return 0;
}
