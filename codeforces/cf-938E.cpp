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

const int maxn = 1e6, md = 1e9 + 7;

inline LL PowMod(LL a, LL b) { LL r=1; while(b) { if(b&1) r=r*a%md; a=a*a%md, b>>=1; } return r; }

int n, seg[maxn + 5];

int main() {
    scanf("%d", &n);
    REP(i,1,n) scanf("%d", seg + i);
    LL fn = 1;
    for(int i = 1; i <= n; ++i) fn = fn * i % md;
    sort(seg + 1, seg + 1 + n);
    int cnt = 0;
    LL ans = 0;
    for(int i = 1; i <= n; ++i) {
        int s = 1, v = seg[i];
        while(i+1 <= n && v == seg[i+1]) ++s, ++i;
        if(i == n) continue;
        ans = (ans + fn * PowMod(n-cnt, md-2) % md * v % md * s % md) % md;
        cnt += s;
    }
    printf("%lld\n", ans);
    return 0;
}
