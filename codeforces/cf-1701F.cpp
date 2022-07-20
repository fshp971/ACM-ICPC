#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define PER(i,a,b) for(int i = a; i >= b; --i)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
#define lson (x<<1)
#define rson (x<<1|1)
#define mid ((l+r)>>1)
typedef long long LL;
typedef long double LD;

const int maxn = 2e5;
const int maxnode = maxn << 2;

struct Mat {
    LL mat[3][3];
    Mat() { mem(mat,0); }
    void ide() { REP(i,0,2) REP(k,0,2) mat[i][k] = (i==k); }
    LL* operator[](const int i) { return mat[i]; }
    Mat operator*(Mat &a) {
        Mat res;
        REP(i,0,2) REP(k,0,2) {
            if(mat[i][k] == 0) continue;
            REP(j,0,2) res[i][j] += mat[i][k]*a[k][j];
        }
        return res;
    }
    // void print() { REP(i,0,2) { REP(k,0,2) printf("%d ", mat[i][k]); puts(""); } }
} addm, subm;

int n;
unordered_set<int> s;
LL f2[maxnode+5], f1[maxnode+5], f0[maxnode+5];
Mat tr[maxnode+5];

void build(int x, int l, int r) {
    tr[x].ide();
    if(l < r) build(lson, l, mid), build(rson, mid+1, r);
}

void push(int x, Mat &v) {
    tr[x] = tr[x] * v;
    f2[x] = f2[x] * v[0][0] + f1[x] * v[0][1] + f0[x] * v[0][2];
    f1[x] = f1[x] * v[1][1] + f0[x] * v[1][2];
}

void ins(int x, int l, int r, int p, int v) {
    if(l == r) {
        if(v == -1) f0[x] = f1[x] = f2[x] = 0;
        else f2[x] = tr[x][0][2], f1[x] = tr[x][1][2], f0[x] = 1;
        return;
    }
    if(p <= mid) ins(lson, l, mid, p, v);
    else ins(rson, mid+1, r, p, v);
    f2[x] = f2[lson] + f2[rson];
    f1[x] = f1[lson] + f1[rson];
    f0[x] = f0[lson] + f0[rson];
    f2[x] = f2[x] * tr[x][0][0] + f1[x] * tr[x][0][1] + f0[x] * tr[x][0][2];
    f1[x] = f1[x] * tr[x][1][1] + f0[x] * tr[x][1][2];
}

void upd(int x, int l, int r, int ll, int rr, Mat &v) {
    if(ll<=l && r<=rr) { push(x,v); return; }
    push(lson,tr[x]);
    push(rson,tr[x]);
    tr[x].ide();
    if(ll <= mid) upd(lson, l, mid, ll, rr, v);
    if(mid < rr) upd(rson, mid+1, r, ll, rr, v);
    f2[x] = f2[lson] + f2[rson];
    f1[x] = f1[lson] + f1[rson];
}

int main() {
    addm.ide();
    addm[0][1] = 2, addm[0][2] = 1, addm[1][2] = 1;

    subm.ide();
    subm[0][1] = -2, subm[0][2] = 1, subm[1][2] = -1;

    int _, d, a, fg;
    scanf("%d%d", &_, &d);
    build(1,1,maxn);
    while(_--) {
        scanf("%d", &a);
        if(s.find(a) == s.end()) fg = 1, s.insert(a);
        else fg = -1, s.erase(a);
        ins(1, 1, maxn, a, fg);
        if(a > 1) {
            int ll = max(a-d, 1);
            int rr = a-1;
            if(fg == 1) upd(1, 1, maxn, ll, rr, addm);
            else upd(1, 1, maxn, ll, rr, subm);
        }
        printf("%lld\n", (f2[1]-f1[1])>>1);
    }
    return 0;
}
