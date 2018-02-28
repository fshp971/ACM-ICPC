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

#define lson L[x]
#define rson R[x]
#define mid ((l + r) >> 1)

const int maxnode = 16000000;

int tree[maxnode + 5], lazy[maxnode + 5], L[maxnode + 5], R[maxnode + 5];

int NewNode(int l, int r) {
    static int tot = 0;
    assert(tot+1 <= maxnode);
    lazy[++tot] = 2, tree[tot] = (r-l+1);
    return tot;
}

void PushDown(int x, int l, int r) {
    if(!L[x]) L[x] = NewNode(l,mid);
    if(!R[x]) R[x] = NewNode(mid+1,r);
    if(lazy[x]) {
        lazy[lson] = lazy[rson] = lazy[x];
        if(lazy[x] == 2) tree[lson] = (mid-l+1), tree[rson] = (r-mid);
        else tree[lson] = tree[rson] = 0;
        lazy[x] = 0;
    }
}

void Upd(int x, int l, int r, int ll, int rr, int cc) {
    if(ll <= l && r <= rr) {
        lazy[x] = cc; tree[x] = (cc==2) ? (r-l+1) : 0;
        return;
    }
    PushDown(x, l, r);
    if(ll <= mid) Upd(lson, l, mid, ll, rr, cc);
    if(mid < rr) Upd(rson, mid + 1, r, ll, rr, cc);
    tree[x] = tree[lson] + tree[rson];
}

int main() {
    int n, rt;
    scanf("%d", &n);
    rt = NewNode(1,n);
    int T, ord, l, r;
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d%d", &l, &r, &ord);
        Upd(rt, 1, n, l, r, ord);
        printf("%d\n", tree[rt]);
    }
    return 0;
}
