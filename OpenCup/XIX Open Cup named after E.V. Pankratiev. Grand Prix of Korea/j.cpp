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
typedef pair<LL,int> pLi;

const int maxn = 3e5;

struct Node {
    int p, l, r;
    LL sq;
    Node() {}
    Node(int _p, int _l, int _r, LL _sq) : p(_p), l(_l), r(_r), sq(_sq) {}
    bool operator<(const Node &a) const { return sq>a.sq; }
};

int n, hi[maxn+5], num[maxn+5], rk[maxn+5], sta[maxn+5];
int L[maxn+5], R[maxn+5];
LL ans[maxn+5];

int Build() {
    int top = 0;
    for(int i = 1; i <= n; ++i) {
        L[rk[i]] = R[rk[i]] = 0;
        int p = top;
        while(p && sta[p]>rk[i]) --p;
        if(p>0) R[sta[p]] = rk[i];
        if(p<top) L[rk[i]] = sta[p+1];
        sta[++p] = rk[i], top = p;
    }
    return sta[1];
}

void Work(int x) {
    if(L[x]) {
        Work(L[x]);
        L[x] = L[L[x]];
    }
    else L[x] = num[x];
    if(R[x]) {
        Work(R[x]);
        R[x] = R[R[x]];
    }
    else R[x] = num[x];
}

inline LL S1(LL n) { return (n*(n+1))>>1; }

inline LL Go(LL sq, int p, int l, int r) {
    LL len = sq/hi[p];
    len = min(len, r-l+1LL);
    LL res = S1(r-l+1) - S1(r-l+1-len);
    {
        LL tl = min(len, LL(r-p));
        res -= S1(r-p) - S1(r-p-tl);
    }
    {
        LL tl = min(len, LL(p-l));
        res -= S1(p-l) - S1(p-l-tl);
    }
    return res;
}

LL Calc(LL sq) {
    LL res = 0;
    REP(i,1,n) res += Go(sq, i, L[rk[i]], R[rk[i]]);
    return res;
}

LL Find(LL x) {
    LL l = 1, r = LL(1e9) * maxn, res = r+1;
    while(l<=r) {
        LL mid = (l+r)>>1;
        LL tmp = Calc(mid);
        if(x<=tmp) res = mid, r = mid-1;
        else l = mid+1;
    }
    return res;
}

priority_queue<pLi> que;

int main() {
    LL l, r;
    scanf("%d", &n);
    REP(i,1,n) scanf("%d", hi+i), num[i] = i;
    scanf("%lld%lld", &l, &r);
    sort(num+1, num+1+n, [&](const int &a, const int &b){return hi[a]<hi[b];});
    REP(i,1,n) rk[num[i]] = i;
    Work(Build());

    LL sq1 = Find(l);
    LL ct1 = Calc(sq1);

    if(ct1 >= r) {
        REP(i,1,r-l+1) ans[i] = sq1;
    }
    else {
        REP(i,1,ct1-l+1) ans[i] = sq1;
        REP(i,1,n) {
            LL len = sq1/hi[i] + 1;
            if(len > R[rk[i]]-L[rk[i]]+1) continue;
            que.push( pLi(-len*hi[i], i) );
        }
        int pt = ct1-l+1+1;
        while(pt <= r-l+1) {
            LL sq = -que.top().fi;
            int x = que.top().se;
            que.pop();
            LL len = sq / hi[x];
            LL cc = (R[rk[x]] - L[rk[x]] + 1 - len + 1);
            if(R[rk[x]]-x >= len) cc -= (R[rk[x]] - x - len + 1);
            if(x-L[rk[x]] >= len) cc -= (x - L[rk[x]] - len + 1);
            cc = min(LL(cc), r-l+1-pt+1);
            for(int i = 1; i <= cc; ++i) ans[pt++] = sq;
            if(len+1 <= R[rk[x]]-L[rk[x]]+1) {
                que.push( pLi(-(len+1)*hi[x], x) );
            }
        }
    }
    REP(i,1,r-l+1) printf("%lld%c", ans[i], (i==r-l+1)?'\n':' ');
    return 0;
}
