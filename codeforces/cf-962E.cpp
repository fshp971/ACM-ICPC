#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
#define SZ(v) (int)(v.size())
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 2e5;
const LL INF = 1LL << 40;

int n, top = 0, seg[maxn + 5];
vector<LL> P, B[maxn + 5], R[maxn + 5];

LL Run(LL L, LL R, vector<LL> &bb, vector<LL> &rr) {
    LL res = 0;
    if(L == -INF && R == INF) {
        if(bb.size()) res += bb[SZ(bb)-1] - bb[0];
        if(rr.size()) res += rr[SZ(rr)-1] - rr[0];
        return res;
    }
    if(L == -INF) {
        if(bb.size()) res += R - bb[0];
        if(rr.size()) res += R - rr[0];
        return res;
    }
    if(R == INF) {
        if(bb.size()) res += bb[SZ(bb)-1] - L;
        if(rr.size()) res += rr[SZ(rr)-1] - L;
        return res;
    }
    LL res1 = R - L, res2 = (R - L) << 1;
    if(bb.size()) {
        LL del = max(bb[0] - L, R - bb[SZ(bb)-1]);
        for(int i = 0; i+1 < SZ(bb); ++i) del = max(del, bb[i+1] - bb[i]);
        res1 += R - L - del;
    }
    if(rr.size()) {
        LL del = max(rr[0] - L, R - rr[SZ(rr)-1]);
        for(int i = 0; i+1 < SZ(rr); ++i) del = max(del, rr[i+1] - rr[i]);
        res1 += R - L - del;
    }
    if(!SZ(bb) && !SZ(rr)) res2 = R - L;
    return min(res1, res2);
}

int main() {
    char ord[5];
    int las0 = 0, las1 = 0, las2 = 0, msk = 0;
    LL ans = 0, a;
    scanf("%d", &n);
    P.PB(-INF);
    for(int i = 1; i <= n; ++i) {
        scanf("%lld%s", &a, ord);
        seg[i] = a;
        if(ord[0] == 'P') P.PB(a), ++top;
        else if(ord[0] == 'B') B[top].PB(a), msk |= 1;
        else R[top].PB(a), msk |= 2;
    }
    P.PB(INF);
    for(int i = 0; i+1 < SZ(P); ++i) ans += Run(P[i], P[i+1], B[i], R[i]);
    printf("%lld\n", ans);
    return 0;
}
