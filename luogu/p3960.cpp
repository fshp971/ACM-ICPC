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

const int maxn = 3e5;
const int maxnode = maxn * 30;

int tot = 0;
int rot[maxn+5];
int ch[maxnode+5][2], fa[maxnode+5], sz[maxnode+5];
LL val[maxnode+5];

int NewNode(LL v, int p, int c) {
    ++tot;
    fa[tot] = p, sz[tot] = c, val[tot] = v;
    return tot;
}

void PushUp(int x) {
    sz[x] = sz[ch[x][0]] + sz[ch[x][1]] + 1;
}

void Rotate(int x, int d) {
    int p = fa[x];
    ch[p][d^1] = ch[x][d];
    if(ch[x][d]) fa[ch[x][d]] = p;
    fa[x] = fa[p];
    if(fa[p]) {
        if(ch[fa[p]][0] == p) ch[fa[p]][0] = x;
        else ch[fa[p]][1] = x;
    }
    fa[p] = x, ch[x][d] = p;
    PushUp(p), PushUp(x);
}

void Splay(int &rt, int x, int target) {
    while(fa[x] != target) {
        int p = fa[x];
        if(ch[p][0] == x) {
            if(fa[p] != target && ch[fa[p]][0] == p) Rotate(p,1);
            Rotate(x,1);
        }
        else {
            if(fa[p] != target && ch[fa[p]][1] == p) Rotate(p,0);
            Rotate(x,0);
        }
        if(!target) rt = x;
    }
}

int Kth(int &rt, int k) {
    int x = rt;
    while(x) {
        if(sz[x]>1 && !ch[x][0] && !ch[x][1]) {
            LL l = val[x], r = val[x]+sz[x]-1, mid = (l+r)>>1;
            val[x] = mid;
            if(l<=mid-1) ch[x][0] = NewNode(l, x, mid-1-l+1);
            if(mid+1<=r) ch[x][1] = NewNode(mid+1, x, r-mid);
        }
        if(sz[ch[x][0]]+1 == k) return x;
        if(k <= sz[ch[x][0]]) x = ch[x][0];
        else k -= sz[ch[x][0]]+1, x = ch[x][1];
    }
    assert(false);
    return 0;
}

void Insert(int &rt, LL v, int k) {
    if(k == 0) rt = NewNode(v, 0, 1);
    else {
        int x = Kth(rt, k);
        Splay(rt, x, 0);
        ch[x][1] = NewNode(v, x, 1);
        PushUp(x);
    }
}

LL Delete(int &rt, int k) {
    int x = Kth(rt, k);
    Splay(rt, x, 0);
    if(k == 1) {
        rt = ch[x][1], fa[rt] = 0;
    }
    else {
        int y = Kth(rt, k-1);
        Splay(rt, y, x);
        ch[y][1] = ch[x][1];
        if(ch[x][1]) fa[ch[x][1]] = y;
        rt = y, fa[y] = 0;
        PushUp(rt);
    }
    return val[x];
}

int n, m, _;
LL seg[maxn+5];

int Build(int p, int l, int r) {
    int mid = (l+r) >> 1;
    int x = NewNode(seg[mid], p, r-l+1);
    if(l<=mid-1) ch[x][0] = Build(x, l, mid-1);
    if(mid+1<=r) ch[x][1] = Build(x, mid+1, r);
    return x;
}

int main() {
    scanf("%d%d%d", &n, &m, &_);
    REP(i,1,n) {
        if(m-1 >= 1) rot[i] = NewNode(LL(i-1)*m+1, 0, m-1);
        seg[i] = LL(m)*i;
    }
    rot[0] = Build(0,1,n);
    while(_--) {
        int x, y; scanf("%d%d", &x, &y);
        int u, v;
        LL key, tmp;
        if(y == m) {
            key = Delete(rot[0], x);
            Insert(rot[0], key, n-1);
        }
        else {
            key = Delete(rot[x], y);
            tmp = Delete(rot[0], x);
            Insert(rot[x], tmp, m-2);
            Insert(rot[0], key, n-1);
        }
        printf("%lld\n", key);
    }
    return 0;
}
