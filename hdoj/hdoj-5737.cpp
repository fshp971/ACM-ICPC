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
const int P = 1e9+7;

int A, B, C, M;
int rnd(int last) {
    A = (36969 + (last >> 3)) * (A & M) + (A >> 16);
    B = (18000 + (last >> 3)) * (B & M) + (B >> 16);
    return (C & ((A << 16) + B)) % 1000000000;
}

int n, m, nn;
int ai[maxn+5], bi[maxn+5], val[maxn+5];

int tot, rot[maxn+5], sz[maxn*50+5], L[maxn*50+5], R[maxn*50+5];
int Bul(int l, int r) {
    int x = ++tot;
    sz[x] = 0;
    if(l == r) L[x] = R[x] = 0;
    else {
        L[x] = Bul(l, mid);
        R[x] = Bul(mid+1, r);
    }
    return x;
}
int Add(int px, int l, int r, int p) {
    int x = ++tot;
    L[x] = L[px], R[x] = R[px], sz[x] = sz[px]+1;
    if(l<r) {
        if(p<=mid) L[x] = Add(L[px], l, mid, p);
        else R[x] = Add(R[px], mid+1, r, p);
    }
    return x;
}
int Ask(int x1, int x2, int l, int r, int p) {
    if(r<=p) return sz[x2]-sz[x1];
    int ret = 0;
    if(mid<p) ret += Ask(R[x1], R[x2], mid+1, r, p);
    ret += Ask(L[x1], L[x2], l, mid, p);
    return ret;
}

int tr[maxnode+5];
void Build(int x, int l, int r) {
    if(l == r) tr[x] = ai[l];
    else {
        Build(lson, l, mid);
        Build(rson, mid+1, r);
        if(tr[lson]==tr[rson]) tr[x] = tr[lson];
        else tr[x] = 0;
    }
}
void Upd(int x, int l, int r, int ll, int rr, int c) {
    if(ll<=l && r<=rr) tr[x] = c;
    else {
        if(tr[x]) tr[lson] = tr[rson] = tr[x], tr[x] = 0;
        if(ll<=mid) Upd(lson, l, mid, ll, rr, c);
        if(mid<rr) Upd(rson, mid+1, r, ll, rr, c);
        if(tr[lson] && tr[lson]==tr[rson]) tr[x] = tr[lson];
    }
}
int Que(int x, int l, int r, int ll, int rr) {
    if(tr[x]) {
        int rk = upper_bound(val+1, val+1+nn, tr[x]) - val - 1;
        if(rk) return Ask(rot[ll-1], rot[rr], 1, nn, rk);
        return 0;
    }
    int ret = 0;
    if(ll<=mid) ret += Que(lson, l, mid, ll, min(mid,rr));
    if(mid<rr) ret += Que(rson, mid+1, r, max(mid+1,ll), rr);
    return ret;
}

int main() {
    int _; scanf("%d", &_);
    while(_--) {
        scanf("%d%d%d%d", &n, &m, &A, &B);
        C = ~(1<<31), M = (1<<16)-1;
        nn = 0;
        REP(i,1,n) scanf("%d", ai+i);
        REP(i,1,n) scanf("%d", bi+i), val[++nn] = bi[i];

        // build persistent segment tree with bi[]
        sort(val+1, val+1+nn);
        nn = unique(val+1, val+1+nn) - val - 1;
        tot = 0;
        rot[0] = Bul(1,nn);
        for(int i = 1; i <= n; ++i) {
            int rk = lower_bound(val+1, val+1+nn, bi[i]) - val;
            rot[i] = Add(rot[i-1], 1, nn, rk);
        }

        // build segment tree with ai[]
        Build(1,1,n);

        int las = 0;
        LL ans = 0;
        for(int i = 1; i <= m; ++i) {
            int l = rnd(las)%n + 1;
            int r = rnd(las)%n + 1;
            int x = rnd(las) + 1;
            if(l>r) swap(l,r);
            if((l+r+x)&1) { // "+" opt
                Upd(1, 1, n, l, r, x);
            }
            else { // "?" opt
                las = Que(1, 1, n, l, r);
                ans = (ans + LL(i)*las) % P;
            }
        }
        printf("%lld\n", ans);
    }
    return 0;
}
