#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
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
#include<stack>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define PER(i,a,b) for(int i=a; i>=b; --i)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 262144;
const int P = 1e9+7;

inline LL PowMod(LL a, LL b) { LL r=1; while(b) { if(b&1) r=r*a%P; a=a*a%P, b>>=1; } return r; }

const LL inv2 = PowMod(2,P-2);

void FWT(LL *a, int len, int type) {
    for(int l = 1; l < len; l <<= 1) {
        for(int i = 0; i < len; i += (l << 1))
            for(int k = 0; k < l; ++k) {
                LL x = a[i + k], y = a[i + k + l];
                a[i+k] = (x+y) % P, a[i+k+l] = (x-y+P) % P;
                if(type == -1)
                    a[i+k] = a[i+k]*inv2 % P, a[i+k+l] = a[i+k+l]*inv2 % P;
            }
    }
}

int n;
LL aa[maxn+5], bb[maxn+5], cc[maxn+5];

int main() {
    scanf("%d", &n);
    REP(i,0,n-1) scanf("%lld", aa+i);
    REP(i,0,n-1) scanf("%lld", bb+i);
    FWT(aa,n,1), FWT(bb,n,1);
    REP(i,0,n-1) cc[i] = bb[i] * PowMod(aa[i],P-2) % P;
    FWT(cc,n,-1);
    REP(i,0,n-1) printf("%lld\n", cc[i]);
    return 0;
}
