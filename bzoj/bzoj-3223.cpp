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

const int maxn = 1e5 + 10;

int root = 0, tot = 0;
int ch[maxn+5][2], fa[maxn+5], sz[maxn+5], val[maxn+5];
bool rev[maxn+5];

void Output();

void PushUp(int x) {
    sz[x] = sz[ch[x][0]] + sz[ch[x][1]] + 1;
}

void PushDown(int x) {
    if(rev[x]) {
        swap(ch[x][0], ch[x][1]), rev[x] = 0;
        if(ch[x][0]) rev[ch[x][0]] ^= 1;
        if(ch[x][1]) rev[ch[x][1]] ^= 1;
    }
}

// d = 0: left-rotate;
// d = 1: right-rotate;
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
    PushUp(p); PushUp(x);
}

void Splay(int x, int target) {
    bool fg = 0;
    if(x == 5) fg = 1;
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
    }
    if(!target) root = x;
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

int n, m, ans[maxn+5];
void Reverse(int l, int r) {
    int x = Kth(l-1+1), y = Kth(r+1+1);
    Splay(x,0), Splay(y,root);
    rev[ch[ch[x][1]][0]] ^= 1;
}

int Build(int p, int l, int r) {
    int x = ++tot, mid = (l+r)>>1;
    fa[x] = p, sz[x] = r-l+1, val[x] = mid;
    if(l<=mid-1) ch[x][0] = Build(x, l, mid-1);
    if(mid+1<=r) ch[x][1] = Build(x, mid+1, r);
    return x;
}

void dfs(int x, int d) {
    PushDown(x);
    ans[ sz[ch[x][0]]+1+d-1 ] = val[x];
    if(ch[x][0]) dfs(ch[x][0], d);
    if(ch[x][1]) dfs(ch[x][1], d+sz[ch[x][0]]+1);
}

int main() {
    scanf("%d%d", &n, &m);
    root = Build(0, 0, n+1);
    while(m--) {
        int l, r; scanf("%d%d", &l, &r);
        Reverse(l,r);
    }
    dfs(root, 0);
    REP(i,1,n) printf("%d%c", ans[i], (i==n)?'\n':' ');
    return 0;
}
