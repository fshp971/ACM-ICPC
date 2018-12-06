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

const int maxn = 1e5;
const int maxnode = maxn<<2;

int n, ai[maxn+5], bi[maxn+5];
vector<pii> vec1, vec2;
vector<tuple<char,int,int>> ans;

int mi[maxnode+5], lz[maxnode+5];

void Build(int x, int l, int r) {
    if(l==r) mi[x] = ai[l];
    else {
        Build(lson, l, mid);
        Build(rson, mid+1, r);
        mi[x] = min(mi[lson], mi[rson]);
    }
}

void PushDown(int x) {
    if(!lz[x]) return;
    mi[lson] = lz[lson] = lz[x];
    mi[rson] = lz[rson] = lz[x];
    lz[x] = 0;
}

void Upd(int x, int l, int r, int ll, int rr, int v) {
    if(ll<=l && r<=rr) lz[x] = mi[x] = v;
    else {
        PushDown(x);
        if(ll<=mid) Upd(lson, l, mid, ll, rr, v);
        if(mid<rr) Upd(rson, mid+1, r, ll, rr, v);
        mi[x] = min(mi[lson], mi[rson]);
    }
}

int Que(int x, int l, int r, int ll, int rr) {
    if(ll<=l && r<=rr) return mi[x];
    PushDown(x);
    int res = maxn+100;
    if(ll<=mid) res = min(res, Que(lson, l, mid, ll, rr));
    if(mid<rr) res = min(res, Que(rson, mid+1, r, ll, rr));
    return res;
}

int main() {
    scanf("%d", &n);
    REP(i,1,n) scanf("%d", ai+i);
    REP(i,1,n) scanf("%d", bi+i);
    Build(1,1,n);
    int pt = 1;
    for(int i = 1; i <= n; ++i) {
        while(pt<=n && ai[pt]!=bi[i]) ++pt;
        if(pt>n) exit( puts("-1")*0 );
        int l = i, r = i;
        while(i+1<=n && bi[i]==bi[i+1]) ++i;
        r = i;
        if(l<pt) vec1.PB( pii(l,pt) );
        if(pt<r) vec2.PB( pii(pt,r) );
    }
    for(int i = 0; i < vec1.size(); ++i) {
        int l = vec1[i].fi, r = vec1[i].se;
        int mi = Que(1, 1, n, l, r-1);
        ans.PB( make_tuple('m', l, r-1) );
        if(mi<ai[r]) ans.PB( make_tuple('M', l, r) );
        else ans.PB( make_tuple('m', l, r) );
        Upd(1, 1, n, l, r, ai[r]);
    }
    for(int i = int(vec2.size())-1; i >= 0; --i) {
        int l = vec2[i].fi, r = vec2[i].se;
        int mi = Que(1, 1, n, l+1, r);
        ans.PB( make_tuple('m', l+1, r) );
        if(mi<ai[l]) ans.PB( make_tuple('M', l, r) );
        else ans.PB( make_tuple('m', l, r) );
        Upd(1, 1, n, l, r, ai[l]);
    }
    printf("%d\n", int(ans.size()) );
    for(auto x : ans) printf("%c %d %d\n", get<0>(x), get<1>(x), get<2>(x));
    return 0;
}
