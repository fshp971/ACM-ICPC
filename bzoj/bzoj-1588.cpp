#include <bits/stdc++.h>

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

const int maxn = 32767;
const int INF = 1 << 30;

int root = 0, tot = 0, val[maxn + 5];
int ch[maxn + 5][2], fa[maxn + 5], sz[maxn + 5];

void Rotate(int x, int d) {
    int p = fa[x];
    ch[p][d^1] = ch[x][d];
    if(ch[x][d]) fa[ ch[x][d] ] = p;
    fa[x] = fa[p];
    if(fa[p]) {
        if(ch[fa[p]][0] == p) ch[fa[p]][0] = x;
        else ch[fa[p]][1] = x;
    }
    fa[p] = x, ch[x][d] = p;
    sz[p] = sz[ ch[p][0] ] + sz[ ch[p][1] ] + 1;
    sz[x] = sz[ ch[x][0] ] + sz[ ch[x][1] ] + 1;
}

void Splay(int x, int target) {
    while(fa[x] != target) {
        int p = fa[x];
        if(ch[p][0] == x) {
            if(fa[p] && ch[fa[p]][0] == p) Rotate(p,1);
            Rotate(x,1);
        }
        else {
            if(fa[p] && ch[fa[p]][1] == p) Rotate(p,0);
            Rotate(x,0);
        }
    }
    if(!target) root = x;
}

int Pre(int x, int v) {
    if(x == 0) return -INF;
    if(v == val[x]) { Splay(x,0); return v; }
    if(v < val[x]) return Pre(ch[x][0], v);
    int t = Pre(ch[x][1], v);
    if(t == -INF) { Splay(x,0); return val[x]; }
    return t;
}

int Nex(int x, int v) {
    if(x == 0) return INF;
    if(v == val[x]) { Splay(x,0); return v; }
    if(v > val[x]) return Nex(ch[x][1], v);
    int t = Nex(ch[x][0], v);
    if(t == INF) { Splay(x,0); return val[x]; }
    return t;
}

void Insert(int &x, int v, int p = 0) {
    if(x == 0) {
        x = ++tot;
        val[x] = v, fa[x] = p, ch[x][0] = ch[x][1] = 0, sz[x] = 1;
        Splay(x,0);
    }
    else {
        if(v < val[x]) Insert(ch[x][0], v, x);
        else Insert(ch[x][1], v, x);
        sz[x] = sz[ ch[x][0] ] + sz[ ch[x][1] ] + 1;
    }
}

int main() {
    int n, a, ans = 0;
    scanf("%d", &n);
    REP(i,1,n) {
        scanf("%d", &a);
        int t1 = Pre(root,a), t2 = Nex(root,a), t3 = INF;
        if(t1 != -INF) t3 = min(t3, abs(a-t1));
        if(t2 != INF) t3 = min(t3, abs(a-t2));
        if(t3 == INF) t3 = a;
        ans += t3;
        Insert(root, a);
    }
    printf("%d\n", ans);
    return 0;
}
