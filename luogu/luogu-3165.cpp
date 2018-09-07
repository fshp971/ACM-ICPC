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

const int maxn = 1e5;

int root = 0, tot = 0;
int ch[maxn+5][2], fa[maxn+5];
int sz[maxn+5], val[maxn+5], mi[maxn+5];
bool rev[maxn+5];

void PushUp(int x) {
    sz[x] = sz[ch[x][0]] + sz[ch[x][1]] + 1;
    mi[x] = min( val[x], min(mi[ch[x][0]], mi[ch[x][1]]) );
}

void PushDown(int x) {
    if(rev[x]) {
        rev[x] = 0;
        swap(ch[x][0], ch[x][1]);
        if(ch[x][0]) rev[ch[x][0]] ^= 1;
        if(ch[x][1]) rev[ch[x][1]] ^= 1;
    }
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

int sta[maxn+5];
void Splay(int x, int target) {
    int top = 0, tx = x;
    while(tx != target) sta[++top] = tx, tx = fa[tx];
    PER(i,top,1) PushDown(sta[i]);
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
        if(!target) root = x;
    }
}

pii GetMin() {
    int x = root, d = 0;
    while(x) {
        PushDown(x);
        if(val[x] < mi[ch[x][0]] && val[x] < mi[ch[x][1]])
            return MP(x, d+sz[ch[x][0]]+1-1);
        if(mi[ch[x][0]] < mi[ch[x][1]]) x = ch[x][0];
        else d += sz[ch[x][0]]+1, x = ch[x][1];
    }
    assert(false);
    return MP(0,0);
}

int Kth(int k) {
    int x = root;
    while(x) {
        PushDown(x);
        if(k == sz[ch[x][0]]+1) return x;
        if(k <= sz[ch[x][0]]) x = ch[x][0];
        else k -= sz[ch[x][0]]+1, x = ch[x][1];
    }
    assert(false);
    return 0;
}

void Reverse(int l, int r) {
    int x = Kth(l-1+1), y = Kth(r+1+1);
    Splay(x,0), Splay(y,x);
    rev[ch[ch[x][1]][0]] ^= 1;
}

void Delete(int x) {
    Splay(x,0);
    if(ch[x][0] == 0) {
        root = ch[x][1], fa[root] = 0;
    }
    else {
        int y = ch[x][0];
        while(ch[y][1]) y = ch[y][1];
        Splay(y,x);
        ch[y][1] = ch[x][1];
        if(ch[x][1]) fa[ch[x][1]] = y;
        root = y, fa[y] = 0;
        PushUp(y);
    }
}

int n, ai[maxn+5], num[maxn+5], seg[maxn+5];

int Build(int p, int l, int r) {
    int x = ++tot, mid = (l+r) >> 1;
    fa[x] = p, sz[x] = 1, val[x] = seg[mid];
    if(l<=mid-1) ch[x][0] = Build(x,l,mid-1);
    if(mid+1<=r) ch[x][1] = Build(x,mid+1,r);
    PushUp(x);
    return x;
}

bool cmp(const int &a, const int &b) {
    if(ai[a] != ai[b]) return ai[a] < ai[b];
    return a < b;
}

int main() {
    mi[0] = 1 << 30; // initialization
    scanf("%d", &n);
    REP(i,1,n) scanf("%d", ai+i), num[i] = i;
    sort(num+1, num+1+n, cmp);
    REP(i,1,n) seg[num[i]] = i;
    seg[0] = seg[n+1] = 1 << 30;
    root = Build(0, 0, n+1);
    REP(i,1,n) {
        pii tmp = GetMin();
        Reverse(1, tmp.se);
        Delete(tmp.fi);
        printf("%d%c", tmp.se+i-1, (i==n)?'\n':' ');
    }
    return 0;
}
