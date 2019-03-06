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

const int maxn = 1e5;
const int P = 998244353;

int n, kk, sq;
int ai[maxn+5], vi[maxn+5], pre[maxn+5], be[maxn+5];
int f[maxn+5], g[320+5];
int cnt[maxn+5], lz[maxn+5], h[318][maxn*2+5];

inline void Add(int &a, int b) { a+=b; if(a>=P) a-=P; }
inline void Sub(int &a, int b) { a-=b; if(a<0) a+=P; }

void Upd(int l, int r, int v) {
    if(l>r) return;
    int tmp = min((be[l]+1)*sq-1, r);
    while(l<=tmp) {
        Sub(h[be[l]][n+cnt[l]], f[l]);
        if(cnt[l]+lz[be[l]]<=kk) Sub(g[be[l]], f[l]);
        cnt[l] += v;
        Add(h[be[l]][n+cnt[l]], f[l]);
        if(cnt[l]+lz[be[l]]<=kk) Add(g[be[l]], f[l]);
        ++l;
    }
    if(l>r) return;
    for(int i = be[l]; i < be[r]; ++i) {
        if(v>0) Sub(g[i], h[i][n+kk-lz[i]]);
        else Add(g[i], h[i][n+kk+1-lz[i]]);
        lz[i] += v;
    }
    l = be[r]*sq;
    while(l<=r) {
        Sub(h[be[l]][n+cnt[l]], f[l]);
        if(cnt[l]+lz[be[l]]<=kk) Sub(g[be[l]], f[l]);
        cnt[l] += v;
        Add(h[be[l]][n+cnt[l]], f[l]);
        if(cnt[l]+lz[be[l]]<=kk) Add(g[be[l]], f[l]);
        ++l;
    }
}

int Que(int p) {
    int res = 0;
    for(int i = 0; i < be[p]; ++i) Add(res, g[i]);
    for(int i = be[p]*sq; i <= p; ++i) {
        if(cnt[i]+lz[i] <= kk) Add(res, f[i]);
    }
    return res;
}

int main() {
    scanf("%d%d", &n, &kk);
    sq = sqrt(n);
    REP(i,1,n) {
        scanf("%d", ai+i);
        pre[i] = vi[ai[i]];
        vi[ai[i]] = i;
        be[i] = i/sq;
    }
    h[0][n] = 1, f[0] = 1, g[0] = 1;
    for(int i = 1; i <= n; ++i) {
        Upd(pre[i], i-1, 1);
        Upd(pre[pre[i]], pre[i]-1, -1);
        f[i] = Que(i-1);
        Add(h[be[i]][n], f[i]);
        Add(g[be[i]], f[i]);
    }
    printf("%d\n", f[n]);
    return 0;
}
