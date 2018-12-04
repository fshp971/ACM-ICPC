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
#define lson (x<<1)
#define rson (x<<1|1)
#define mid ((l+r)>>1)
typedef long long LL;
typedef pair<int,int> pii;
typedef pair<LL,int> pLi;

const int maxn = 1e5;
const int maxnode = maxn<<2;

int n, m, M;
int si[maxn+5];
LL ha[maxn+5];
vector<pLi> tr[maxnode+5], seg1, seg2;
vector<pii> vec1, vec2;

void Build(int x, int l, int r) {
    tr[x].clear();
    if(l==r) { tr[x].PB( pLi(ha[l],l) ); return; }
    Build(lson, l, mid);
    Build(rson, mid+1, r);
    int pt1 = 0, pt2 = 0;
    while(pt1<tr[lson].size() && pt2<tr[rson].size()) {
        if(tr[lson][pt1].fi < tr[rson][pt2].fi) tr[x].PB( tr[lson][pt1++] );
        else tr[x].PB( tr[rson][pt2++] );
    }
    while(pt1<tr[lson].size()) tr[x].PB( tr[lson][pt1++] );
    while(pt2<tr[rson].size()) tr[x].PB( tr[rson][pt2++] );
}

void Que(int x, int l, int r, int ll, int rr, vector<pii> &vec) {
    if(ll<=l && r<=rr) { vec.PB( pii(x,0) ); return; }
    if(ll<=mid) Que(lson, l, mid, ll, rr, vec);
    if(mid<rr) Que(rson, mid+1, r, ll, rr, vec);
}

int Next(vector<pii> &vec, int &pt, vector<pLi> &seg, int l, int r) {
    LL h = 1LL<<M;
    int c = -1, rk = -1;
    for(int i = 0; i < vec.size(); ++i) {
        if(vec[i].se < tr[vec[i].fi].size() && h > tr[vec[i].fi][vec[i].se].fi) {
            h = tr[vec[i].fi][vec[i].se].fi;
            c = si[(tr[vec[i].fi][vec[i].se].se-l+(r-l)) % (r-l+1) + l];
            if(rk!=-1) --vec[rk].se;
            rk = i;
            ++vec[i].se;
        }
    }
    if(pt < seg.size() && h > seg[pt].fi) {
        h = seg[pt].fi;
        c = si[(seg[pt].se-l+(r-l)) % (r-l+1) + l];
        if(rk!=-1) --vec[rk].se;
        ++pt;
    }
    return c;
}

inline void NR(LL &A) { A = (A*100000005+20150609)%998244353; }

int main() {
    int _; scanf("%d", &_);
    while(_--) {
        LL Ai;
        scanf("%d%d%lld", &n, &m, &Ai);
        M = min(40,n);
        REP(i,1,n) NR(Ai), si[i] = Ai&1;
        REP(i,1,n) {
            ha[i] = 0;
            REP(k,0,M-1) {
                ha[i]<<=1;
                if(i+k<=n && si[i+k]) ha[i]|=1;
            }
        }
        Build(1,1,n);
        for(int i = 1; i <= m; ++i) {
            int a,b,c,d;
            NR(Ai), a = Ai%n+1;
            NR(Ai), b = Ai%n+1;
            NR(Ai), c = Ai%n+1;
            NR(Ai), d = Ai%n+1;
            int l1 = min(a,b), r1 = max(a,b);
            int l2 = min(c,d), r2 = max(c,d);

            vec1.clear(); vec2.clear();
            if(l1<=r1-M+1) Que(1, 1, n, l1, r1-M+1, vec1);
            if(l2<=r2-M+1) Que(1, 1, n, l2, r2-M+1, vec2);

            seg1.clear(); seg2.clear();
            for(int k = max(l1,r1-M+2); k <= r1; ++k) {
                int len = r1-k+1;
                seg1.PB( pLi( (ha[l1]>>len)|((ha[k]>>(M-len))<<(M-len)), k ) );
            }
            for(int k = max(l2,r2-M+2); k <= r2; ++k) {
                int len = r2-k+1;
                seg2.PB( pLi( (ha[l2]>>len)|((ha[k]>>(M-len))<<(M-len)), k ) );
            }
            sort(seg1.begin(), seg1.end());
            sort(seg2.begin(), seg2.end());
            int pt1 = 0, pt2 = 0;


            int ans = 2;
            while(ans==2) {
                int c1 = Next(vec1, pt1, seg1, l1, r1);
                int c2 = Next(vec2, pt2, seg2, l2, r2);
                if(c1==-1 && c2==-1) ans = 0;
                else if(c1<c2) ans = -1;
                else if(c1>c2) ans = 1;
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}
