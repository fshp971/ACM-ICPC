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

const int maxn = 1e5;
const int maxk = 18;

int n, kk, ai[maxk+5];
int msk[maxn+5], cnt[(1<<maxk)+5], cnt2[(1<<maxk)+5], ban[(1<<maxk)+5];
int f[(1<<maxk)+5][maxk+2];
int G[maxk+2][maxk+2];
vector<pii> vec;

bool cmp(const pii &a, const pii &b) { return G[a.fi][a.se] < G[b.fi][b.se]; }

int main() {
    scanf("%d%d", &n, &kk);
    REP(i,0,kk-1) {
        int len, s;
        scanf("%d%d", ai+i, &len);
        REP(k,1,len) scanf("%d", &s), msk[s] |= (1<<i);
    }
    REP(i,1,n) ++cnt[msk[i]];
    for(int i = 0; i < (1<<kk); ++i) {
        f[i][kk] = cnt[i];
        for(int k = kk-1; k >= 0; --k) {
            f[i][k] = f[i][k+1];
            if(i>>k&1) f[i][k] += f[i^(1<<k)][k];
        }
        cnt2[i] = f[i][0];
    }
    REP(i,0,kk-1) REP(j,0,kk-1) G[i][j] = 1e9;
    for(int i = 0; i < (1<<kk); ++i) {
        if(!cnt[i]) continue;
        for(int k = 0; k < kk; ++k)
            if(i>>k&1) {
                for(int j = 0; j < kk; ++j)
                    if(i>>j&1) G[k][j] = (k==j)?0:min(G[k][j],ai[j]);
            }
    }
    for(int k = 0; k < kk; ++k) {
        REP(i,0,kk-1) REP(j,0,kk-1)
            G[i][j] = min(G[i][j], G[i][k]+G[k][j]);
    }
    REP(i,0,kk-1) REP(j,0,kk-1) G[i][j] += ai[i], vec.PB( pii(i,j) );
    sort(vec.begin(), vec.end(), cmp);
    LL ans = 0;
    for(auto pp : vec) {
        int x = pp.fi, y = pp.se;
        int Mask = ((1<<kk)-1) ^ (1<<x);
        for(int i = Mask; i > 0; i = (i-1)&Mask) {
            if(ban[i^(1<<x)]&(1<<y)) continue;
            ans += LL(cnt2[((1<<kk)-1)^ban[i^(1<<x)]]-cnt2[((1<<kk)-1)^ban[i^(1<<x)]^(1<<y)]) * cnt[i^(1<<x)] * G[x][y];
            ban[i^(1<<x)] |= (1<<y);
        }
        // i == 0
        if(!(ban[1<<x]&(1<<y))) {
            ans += LL(cnt2[((1<<kk)-1)^ban[1<<x]]-cnt2[((1<<kk)-1)^ban[1<<x]^(1<<y)]) * cnt[1<<x] * G[x][y];
            ban[1<<x] |= (1<<y);
        }
    }
    for(int i = 0; i < (1<<kk); ++i) {
        int mi = 1e9;
        for(int k = 0; k < kk; ++k)
            if(i>>k&1) mi = min(mi, ai[k]);
        ans -= 1LL * cnt[i] * mi;
    }
    assert(ans%2==0);
    ans >>= 1;
    printf("%lld\n", ans);
    return 0;
}
