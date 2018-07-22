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
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 5e5;

int n, xi[maxn + 5], ai[maxn + 5];
LL T, sa[maxn + 5];

inline LL Calc(int l, int lc, int r, int rc) {
    if(l == r) return rc - lc;
    return sa[r-1] + rc - sa[l-1] - lc;
}

bool Chk(LL all) {
    int l = 1, r = n+1, lc = 1, rc = 1;
    LL now = 0;
    for(int i = 1; i <= n; ++i) {
        if(all >= ai[i])
            all -= ai[i], now += LL(xi[i]-xi[1])*ai[i], r = i+1;
        else {
            now += LL(xi[i]-xi[1])*all, r = i, rc = all+1;
            break;
        }
    }
    if(now <= T) return true;
    for(int i = 2; i <= n; ++i) {
        now += LL(xi[i]-xi[i-1]) * (Calc(l,lc,i,1) - Calc(i,1,r,rc));
        while(r<=n && xi[i]-xi[l] > xi[r]-xi[i]) {
            int dt = min(ai[l]-lc+1, ai[r]-rc+1);
            now += (LL(xi[r]-xi[i]) - LL(xi[i]-xi[l])) * dt;
            lc += dt, rc += dt;
            if(lc > ai[l]) ++l, lc = 1;
            if(rc > ai[r]) ++r, rc = 1;
        }
        if(now <= T) return true;
    }
    return false;
}

int main() {
    scanf("%d%lld", &n, &T), T >>= 1;
    int top = 0;
    REP(i,1,n) scanf("%d", xi + i);
    for(int i = 1, a; i <= n; ++i) {
        scanf("%d", &a);
        if(a) {
            ++top, xi[top] = xi[i], ai[top] = a;
            sa[top] = sa[top-1] + ai[top];
        }
    }
    n = top;
    LL l = 1, r = sa[n], ans = 0;
    while(l <= r) {
        LL mid = (l + r) >> 1;
        if(Chk(mid)) ans = mid, l = mid + 1;
        else r = mid - 1;
    }
    printf("%lld\n", ans);
    return 0;
}
