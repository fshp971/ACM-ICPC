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

const int maxn = 5000;
const int md = 1e9 + 7;

int n, m;
vector<pii> seg;
vector<int> xx;

bool cmp(const pii &a, const pii &b) {
    if(a.se != b.se) return a.se < b.se;
    return a.fi < b.fi;
}

int main() {
    int T, x, y;
    scanf("%d%d%d", &n, &m, &T);
    while(T--) {
        scanf("%d%d", &x, &y);
        seg.PB(MP(x,y)), xx.PB(x);
    }
    seg.PB( MP(n+1,m) ), xx.PB(0), xx.PB(n);
    sort(xx.begin(), xx.end());
    T = unique(xx.begin(), xx.end()) - xx.begin();
    sort(seg.begin(), seg.end(), cmp);
    LL ans = 0;
    for(int i = 1; i < T; ++i) {
        LL tmp = 0, now = 0, las = 0;
        stack<pii> sta;
        sta.push( MP(xx[i],0) );
        for(auto it : seg) {
            if(it.fi < xx[i] || it.se == las) continue;
            LL l = it.se - las;
            tmp = (tmp + now*(l-1) % md +  (l*(l-1)/2) % md * LL(n-xx[i]+1) % md) % md;
            while(sta.top().fi > it.fi) {
                pii tmp2 = sta.top(); sta.pop();
                now = (now - LL(tmp2.fi-xx[i]) * LL(tmp2.se-sta.top().se) % md + md) % md;
            }
            now = (now + LL(it.fi-xx[i]) * LL(it.se-sta.top().se)) % md;
            tmp = (tmp + now) % md;
            sta.push(it), las = it.se;
        }
        LL d = xx[i] - xx[i-1];
        ans = (ans + (d*(d-1)/2) % md * ((LL(m)*(m+1)/2) % md) % md + d * tmp % md) % md;
    }
    printf("%lld\n", ans);
    return 0;
}
