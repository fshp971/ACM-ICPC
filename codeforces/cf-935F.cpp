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

#define lson (x << 1)
#define rson (x << 1 | 1)
#define mid ((l + r) >> 1)

const int maxn = 1e5;
const int maxnode = maxn << 2;

int n, seg[maxn + 5];
LL det[maxnode + 5], sum[maxnode + 5], fk[maxnode + 5];
int cnt1[maxnode + 5], cnt2[maxnode + 5];

pii operator+(const pii &a, const pii &b) { return MP(a.fi+b.fi, a.se+b.se); }

void Build(int x, int l, int r) {
    sum[x] = det[x] = 0;
    if(l == r) {
        fk[x] = -(1LL << 50);
        if(1<l && l<n) {
            if(seg[l-1]<=seg[l] && seg[l]>seg[l+1]) cnt1[x] = 1, sum[x] += (seg[l]<<1);
            else if(seg[l-1]>seg[l] && seg[l]<=seg[l+1]) cnt2[x] = 1, sum[x] -= (seg[l]<<1);
            else if(seg[l-1]<=seg[l] && seg[l]<=seg[l+1]) fk[x] = seg[l]-seg[l+1];
            else fk[x] = seg[l]-seg[l-1];
        }
        return;
    }
    Build(lson, l, mid); Build(rson, mid+1, r);
    sum[x] = sum[lson] + sum[rson];
    cnt1[x] = cnt1[lson] + cnt1[rson], cnt2[x] = cnt2[lson] + cnt2[rson];
    fk[x] = max(fk[lson], fk[rson]);
}

pii Query(int x, int l, int r, int ll, int rr) {
    if(ll <= l && r <= rr) return MP(cnt1[x], cnt2[x]);
    pii ret = MP(0,0);

    sum[lson] += det[x] * (cnt1[lson] - cnt2[lson]) * 2;
    sum[rson] += det[x] * (cnt1[rson] - cnt2[rson]) * 2;
    det[lson] += det[x], det[rson] += det[x], det[x] = 0;

    if(ll <= mid) ret = ret + Query(lson, l, mid, ll, rr);
    if(mid < rr) ret = ret + Query(rson, mid+1, r, ll, rr);
    return ret;
}

void Upd(int x, int l, int r, int ll, int rr, int vv) {
    if(ll <= l && r <= rr) {
        det[x] += vv, sum[x] += LL(vv) * (cnt1[x] - cnt2[x]) * 2;
        return;
    }
    if(ll <= mid) Upd(lson, l, mid, ll, rr, vv);
    if(mid < rr) Upd(rson, mid+1, r, ll, rr, vv);
    sum[x] = sum[lson] + sum[rson] + det[x] * (cnt1[x] - cnt2[x]) * 2;
}

LL Get(int x, int l, int r, int ps) {
    if(l == r) return seg[l] + det[x];
    if(ps <= mid) return Get(lson, l, mid, ps) + det[x];
    return Get(rson, mid+1, r, ps) + det[x];
}

void Set(int x, int l, int r, int ps, int c1, int c2, LL fkk) {
    if(l == r) {
        cnt1[x] = c1, cnt2[x] = c2, fk[x] = fkk;
        sum[x] = (seg[l] + det[x]) * (cnt1[x] - cnt2[x]) * 2;
        return;
    }
    if(ps <= mid) Set(lson, l, mid, ps, c1, c2, fkk);
    else Set(rson, mid+1, r, ps, c1, c2, fkk);
    cnt1[x] = cnt1[lson] + cnt1[rson];
    cnt2[x] = cnt2[lson] + cnt2[rson];
    fk[x] = max(fk[lson], fk[rson]);
    sum[x] = sum[lson] + sum[rson] + det[x] * (cnt1[x] - cnt2[x]) * 2;
}

int GetPs(int x, int l, int r, int ll, int rr) {
    if(!cnt2[x]) return 0;
    if(l == r) return l;
    int ret = 0;
    if(ll <= mid)
        if((ret = GetPs(lson, l, mid, ll, rr)) != 0)
            return ret;
    if(mid < rr)
        if((ret = GetPs(rson, mid+1, r, ll, rr)) != 0)
            return ret;
    return 0;
}

LL GetFk(int x, int l, int r, int ll, int rr) {
    if(ll <= l && r <= rr) return fk[x];
    LL ret = -(1LL << 50);
    if(ll <= mid) ret = max(ret, GetFk(lson,l,mid,ll,rr));
    if(mid < rr) ret = max(ret, GetFk(rson,mid+1,r,ll,rr));
    return ret;
}

void Modify(int x) {
    if(x == 1 || x == n) return;
    LL a = Get(1,1,n,x-1);
    LL b = Get(1,1,n,x);
    LL c = Get(1,1,n,x+1);
    LL fkk = -(1LL<<50);
    if(a <= b && b <= c) fkk = b-c;
    else if(a > b && b > c) fkk = b-a;
    int c1 = 0, c2 = 0;
    if(a <= b && b > c) c1 = 1;
    else if(a > b && b <= c) c2 = 1;
    Set(1,1,n,x,c1,c2,fkk);
}

LL Calc(int ps, int x) {
    LL a = Get(1,1,n,ps-1), b = Get(1,1,n,ps), c = Get(1,1,n,ps+1);
    return abs(a-b-x) + abs(b+x-c) - abs(a-b) - abs(b-c);
}

int main() {
    scanf("%d", &n);
    REP(i,1,n) scanf("%d", seg + i);
    Build(1,1,n);
    int T, o, l, r, x;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d%d%d", &o, &l, &r, &x);
        if(o == 1) {
            LL ans = 0;
            LL a1 = Get(1,1,n,1), a2 = Get(1,1,n,2), b1 = Get(1,1,n,n), b2 = Get(1,1,n,n-1);
            LL ts = sum[1] + ((a1<=a2) ? (-a1) : a1) + ((b2<=b1) ? b1 : (-b1));
            pii tmp = Query(1,1,n,l,r);
            if(tmp.fi) ans = ts + x + x;
            else if(tmp.se) {
                int ps = GetPs(1,1,n,l,r);
                if(l <= ps-1) ans = max(ans, ts + max(0LL,(GetFk(1,1,n,l,ps-1) + x)) * 2);
                if(ps+1 <= r) ans = max(ans, ts + max(0LL,(GetFk(1,1,n,ps+1,r) + x)) * 2);
                ans = max(ans, ts + Calc(ps,x));
            }
            else ans = ts + max(0LL,(GetFk(1,1,n,l,r) + x)) * 2;
            printf("%lld\n", ans);
        }
        else {
            Upd(1,1,n,l,r,x);
            Modify(l-1); Modify(l); Modify(r); Modify(r+1);
        }
    }
    return 0;
}
