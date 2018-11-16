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

const int maxn = 123;
const int P = 1e9+7;

inline LL PowMod(LL a, LL b) { LL r=1; while(b) { if(b&1) r=r*a%P; a=a*a%P, b>>=1; } return r; }

int n, m, lim[maxn+5];
int ai[maxn+5];
int f[maxn+5][maxn*maxn+5];

void Sub(int &a, int b) { a-=b; if(a<0) a+=P; }

int main() {
    REP(i,0,maxn) lim[i] = i*(i-1) / 2;
    int _; scanf("%d", &_);
    while(_--) {
        scanf("%d%d", &n, &m);
        REP(i,1,n) scanf("%d", ai+i);
        ai[0] = ai[n+1] = 2;
        f[0][0] = -1;
        for(int i = 1; i <= n+1; ++i) {
            if(ai[i]!=2) continue;
            REP(k,0,lim[i]) f[i][k] = 0;
            int sum = 0, ps = i-1;
            PER(k,i-1,0) {
                if(ai[k]!=2) {
                    if(ai[k]==1) ps = k-1;
                    else sum += ps-k+1;
                    continue;
                }
                for(int j = 0; j<=lim[k] && j+sum<=lim[i]; ++j)
                    Sub(f[i][j+sum], f[k][j]);
                sum += ps-k+1;
            }
        }
        LL ans = 0;
        for(int i = 1; i <= lim[n+1]; ++i)
            ans = (ans + f[n+1][i]*PowMod(i,m)%P) % P;
        printf("%lld\n", ans);
    }
    return 0;
}
