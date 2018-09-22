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
#define mid ((l+r)>>1)
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 1e5;
const int maxnode = maxn * 30;

int n, ai[maxn+5];
int tot, L[maxnode+5], R[maxnode+5], sz[maxnode+5];
int rot[maxn+5];

int Build(int l, int r) {
    int x = ++tot;
    sz[x] = L[x] = R[x] = 0;
    if(l < r) {
        L[x] = Build(l, mid);
        R[x] = Build(mid+1, r);
    }
    return x;
}

int Upd(int px, int l, int r, int p) {
    int x = ++tot;
    L[x] = L[px], R[x] = R[px], sz[x] = sz[px]+1;
    if(l < r) {
        if(p <= mid) L[x] = Upd(L[x], l, mid, p);
        else R[x] = Upd(R[x], mid+1, r, p);
    }
    return x;
}

// < key
int Que1(int x1, int x2, int l, int r, int p) {
    if(l == r) return 0;
    if(p <= mid)
        return Que1(L[x1], L[x2], l, mid, p);
    else
        return (sz[L[x2]]-sz[L[x1]]) + Que1(R[x1], R[x2], mid+1, r, p);
}

// > key
int Que2(int x1, int x2, int l, int r, int p) {
    if(l == r) return 0;
    if(p <= mid)
        return (sz[R[x2]]-sz[R[x1]]) + Que2(L[x1], L[x2], l, mid, p);
    else
        return Que2(R[x1], R[x2], mid+1, r, p);
}

int tr[maxn+5], vi[maxn+5], T = 0;
void Inc(int x) {
    for(;x<=n;x+=x&(-x)) {
        if(vi[x] != T) vi[x] = T, tr[x] = 0;
        ++tr[x];
    }
}

int Sum(int x) {
    int r = 0;
    for(;x;x-=x&(-x)) r += (vi[x]==T) ? tr[x] : 0;
    return r;
}

LL Calc(int l, int r) {
    LL ret = 0;
    ++T;
    PER(i,r,l) {
        Inc(ai[i]);
        ret += Sum(ai[i]-1);
    }
    return ret;
}

map<pii,LL> Map;
multiset<LL> Set;

int main() {
    int _; scanf("%d", &_);
    while(_--) {
        scanf("%d", &n);
        tot = 0;
        rot[0] = Build(1,n);
        REP(i,1,n) {
            scanf("%d", ai+i);
            rot[i] = Upd(rot[i-1], 1, n, ai[i]);
        }
        LL t = Calc(1,n);
        Map[pii(1,n)] = t;
        Set.insert(t);
        REP(i,1,n) {
            LL a; scanf("%lld", &a);
            printf("%lld%c", *(--Set.end()), (i==n)?'\n':' ');
            a ^= *(--Set.end());
            auto it = --Map.upper_bound( pii(int(a),maxn+10) );
            int l = it->fi.fi, r = it->fi.se;
            LL val1 = it->se;
            Map.erase(it);
            Set.erase( Set.find(val1) );
            if(a-l <= r-a) {
                LL val2 = Calc(l, a-1);
                val1 -= val2;
                REP(k,l,a) val1 -= Que1(rot[a], rot[r], 1, n, ai[k]);
                val1 -= Que2(rot[l-1], rot[a-1], 1, n, ai[a]);
                if(l<=a-1) Map[pii(l,int(a-1))] = val2, Set.insert(val2);
                if(a+1<=r) Map[pii(int(a+1),r)] = val1, Set.insert(val1);
            }
            else {
                LL val2 = Calc(a+1, r);
                val1 -= val2;
                REP(k,a,r) val1 -= Que2(rot[l-1], rot[a-1], 1, n, ai[k]);
                val1 -= Que1(rot[a], rot[r], 1, n, ai[a]);
                if(a+1<=r) Map[pii(int(a+1),r)] = val2, Set.insert(val2);
                if(l<=a-1) Map[pii(l,int(a-1))] = val1, Set.insert(val1);
            }
        }
    }
    return 0;
}
