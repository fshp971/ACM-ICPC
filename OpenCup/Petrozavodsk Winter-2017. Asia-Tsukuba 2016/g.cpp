#include<cassert>
#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
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

#define mid ((l+r) >> 1)
#define lson L[x]
#define rson R[x]

const int maxn = 5e5;
const int maxnode = maxn << 5;
const int N = 1e9;

LL tr[maxnode + 5];
int tot = 0, lz[maxnode + 5], L[maxnode + 5], R[maxnode + 5];

void PushDown(int x, int l, int r) {
    if(!lson) lson = ++tot;
    if(!rson) rson = ++tot;
    lz[lson] += lz[x], lz[rson] += lz[x];
    tr[lson] += LL(mid-l+1) * lz[x];
    tr[rson] += LL(r-mid) * lz[x];
    lz[x] = 0;
}

void Upd(int x, int l, int r, int ll, int rr, int vv) {
    if(ll <= l && r <= rr) lz[x] += vv, tr[x] += LL(r-l+1) * vv;
    else {
        PushDown(x,l,r);
        if(ll <= mid) Upd(lson, l, mid, ll, rr, vv);
        if(mid < rr) Upd(rson, mid+1, r, ll, rr, vv);
        tr[x] = tr[lson] + tr[rson];
    }
}

int Query(int x, int l, int r, int rr) {
    if(!tr[x]) return -1;
    if(!lson) {
        if(lz[x] == 0) return -1;
        return min(r, rr);
    }
    PushDown(x,l,r);
    if(mid < rr) {
        int res = Query(rson, mid+1, r, rr);
        if(res != -1) return res;
    }
    return Query(lson, l, mid, rr);
}

int main() {
    //freopen("in.txt", "r", stdin);
    int T, u, rt = 0;
    scanf("%d", &T);
    Upd(rt,0,N,0,0,1);
    while(T--) {
        scanf("%d", &u);
        int q = Query(rt,0,N,u);
        //printf("q = %d\n", q);
        if(q == -1) { puts("No"); continue; }
        puts("Yes");
        Upd(rt,0,N,q,q,-1);
        if(q+1 <= u) Upd(rt,0,N,q+1,u,1);
        /*
        printf("u = %d\n", u);
        exit(0);
        */
    }
    return 0;
}
