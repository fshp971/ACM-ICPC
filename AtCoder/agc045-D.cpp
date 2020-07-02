#include <bits/stdc++.h>

using namespace std;

#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define PER(i,a,b) for(int i = a; i >= b; --i)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
typedef long long LL;
typedef long double LD;

const int maxn = 1e7;
const int maxa = 5000;
const int P = 1e9+7;

int Fac[maxn+5], InvFac[maxn+5];
LL PowMod(LL a, LL b) { LL r=1; while(b) { if(b&1) r=r*a%P; a=a*a%P, b>>=1; } return r; }
LL C(int n, int m) { return LL(Fac[n]) * InvFac[m] % P * InvFac[n-m] % P; }

void Add(int &a, int b) { a+=b; if(a>=P) a-=P; }
void Sub(int &a, int b) { a-=b; if(a<0) a+=P; }

int main() {
    Fac[0] = 1;
    REP(i,1,maxn) Fac[i] = Fac[i-1] * LL(i) % P;
    InvFac[maxn] = PowMod(Fac[maxn], P-2);
    PER(i,maxn-1,0) InvFac[i] = InvFac[i+1] * LL(i+1) % P;

    int n, m, ans = 0;
    scanf("%d%d", &n, &m), n -= m;
    REP(t,1,m+1) {
        int tmp = 0;
        for(int i = 1; i <= t-1; ++i) {
            LL ha = C(t-1, i);
            ha = ha * Fac[i] % P * Fac[i+n-1] % P;
            if(i >= 1)
                ha = ha * InvFac[i-1] % P;
            if(t <= m)
                ha = ha * Fac[i+n+m-t] % P * InvFac[i+n] % P;
            if((t-1-i)&1) Sub(tmp, ha);
            else Add(tmp, ha);
        }
        Add(ans, tmp);
    }
    printf("%d\n", ans);
    return 0;
}
