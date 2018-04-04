#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<cassert>
#include<cassert>
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
#include<unordered_map>
#include<unordered_set>

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

const int maxn = 2e6;
const int md = 1e9 + 7;

int m, n, kk;
LL Fac[maxn + 5], InvFac[maxn + 5], ha;
double Log[maxn + 5], lha;

inline LL PowMod(LL a, LL b) { LL r=1; while(b) { if(b&1) r=r*a%md; a=a*a%md, b>>=1; } return r; }

bool Chk() {
    int l = kk, r = m, tn = kk;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(lha < Log[mid] - Log[mid-kk]) tn = mid, r = mid - 1;
        else l = mid + 1;
    }
    for(int i = max(kk,tn-5); i <= min(m,tn+5); ++i) {
        if(Fac[i] * InvFac[i-kk] % md == ha) {
            n = i; return true;
        }
    }
    return false;
}

int main() {
    Fac[0] = 1, Log[0] = 0;
    REP(i,1,maxn) Fac[i] = Fac[i-1] * i % md, Log[i] = Log[i-1] + log(i);
    InvFac[maxn] = PowMod(Fac[maxn], md - 2);
    for(int i = maxn-1; i >= 0; --i) InvFac[i] = InvFac[i+1] * (i+1) % md;
    int T, a, b;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &a, &m);
        ha = 1, lha = 0;
        while(a--) scanf("%d", &b), ha = ha * b % md, lha += log(b);
        bool fg = 0;
        for(kk = 1; kk <= m; ++kk) {
            ha = ha * kk % md, lha += log(kk);
            if(Chk()) {
                printf("YES\n%d %d\n", n, kk), fg = 1;
                break;
            }
        }
        if(!fg) puts("NO");
    }
    return 0;
}
