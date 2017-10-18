#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define PB push_back
typedef long long LL;
typedef pair<int,int> pii;

#define fi first
#define se second

const int maxn = 2e5, MaxStep = 30;

int n, seg[maxn + 5];
int S[maxn + 5][MaxStep + 2];
pii rmq[maxn + 5][MaxStep + 5];
LL ans = 0;

void InitRMQ() {
    for(int i = 1; i <= n; ++i) rmq[i][0] = MP(seg[i], i);
    for(int i = 1; (1<<i) <= n; ++i)
        for(int k = (1<<i); k <= n; ++k)
            rmq[k][i] = max(rmq[k][i-1], rmq[k - (1 << (i-1))][i-1]);
}

pii RMQ(int l, int r) {
    int i;
    for(i = 0; (1 << (i+1)) < (r-l+1); ++i);
    return max(rmq[r][i], rmq[l+(1<<i)-1][i]);
}

void Calc(int l, int r) {
    if(l >= r) return;
    pii x = RMQ(l, r);
    int ll = l, rr = x.se - 1, L = x.se, R = x.se;
    while(ll <= rr) {
        int mid = (ll + rr) >> 1, fg = 0;
        for(int i = 0; i <= MaxStep; ++i) {
            if((x.fi>>i & 1) == 0 && S[x.se-1][i] - S[mid-1][i]) {
                fg = 1; break;
            }
        }
        if(fg) ll = mid + 1;
        else L = mid, rr = mid - 1;
    }
    ll = x.se + 1, rr = r;
    while(ll <= rr) {
        int mid = (ll + rr) >> 1, fg = 0;
        for(int i = 0; i <= MaxStep; ++i) {
            if((x.fi>>i & 1) == 0 && S[mid][i] - S[x.se][i]) {
                fg = 1; break;
            }
        }
        if(fg) rr = mid - 1;
        else R = mid, ll = mid + 1;
    }
    LL del = LL(x.se) * (n - x.se + 1) - LL(x.se - L + 1) * (R - x.se + 1);
    ans += LL(x.se - l + 1) * (r - x.se + 1) - LL(x.se - L + 1) * (R - x.se + 1);
    Calc(l, x.se - 1);
    Calc(x.se + 1, r);
}

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) {
        scanf("%d", seg + i);
        for(int k = 0; k <= MaxStep; ++k)
            S[i][k] += S[i-1][k] + (seg[i] >> k & 1);
    }
    InitRMQ();
    Calc(1, n);
    printf("%lld\n", ans);
    return 0;
}
