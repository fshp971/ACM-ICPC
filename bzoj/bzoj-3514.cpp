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
#define lson L[x]
#define rson R[x]
#define mid ((l+r)>>1)
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 4e5;
const int maxnode = maxn * 30;

int ch[maxn+5][2], fa[maxn+5];
int id[maxn+5], mi[maxn+5];
bool rev[maxn+5];

inline bool IsRoot(int x) { return (ch[fa[x]][0]!=x && ch[fa[x]][1]!=x); }
inline void PushUp(int x) {
    mi[x] = min(id[x], min(mi[ch[x][0]], mi[ch[x][1]]));
}
inline void PushDown(int x) {
    if(rev[x]) {
        rev[x] = 0;
        swap(ch[x][0], ch[x][1]);
        if(ch[x][0]) rev[ch[x][0]] ^= 1;
        if(ch[x][1]) rev[ch[x][1]] ^= 1;
    }
}
void Rotate(int x) {
    int y = fa[x], d = ch[y][1]==x;
    ch[y][d] = ch[x][d^1];
    if(ch[x][d^1]) fa[ch[x][d^1]] = y;
    if(fa[y]) {
        int z = fa[y];
        if(ch[z][0] == y) ch[z][0] = x;
        if(ch[z][1] == y) ch[z][1] = x;
    }
    fa[x] = fa[y], fa[y] = x, ch[x][d^1] = y;
    PushUp(y);
}
int top, sta[maxn+5];
void Splay(int x, int target = 0) {
    sta[top = 1] = x;
    for(int i = x; !IsRoot(i) && fa[x]!=target; i = fa[i]) sta[++top] = fa[i];
    while(top>0) PushDown(sta[top--]);
    while(!IsRoot(x) && fa[x]!=target) {
        int y = fa[x];
        if(!IsRoot(y) && fa[y]!=target)
            Rotate( ((ch[fa[y]][0]==y)^(ch[y][0]==x)) ? x : y );
        Rotate(x);
    }
    PushUp(x);
}
void Access(int x) { for(int y = 0; x; y = x, x = fa[x]) Splay(x), ch[x][1] = y, PushUp(x); }
void MakeRoot(int x) { Access(x); Splay(x); rev[x]^=1; }
void Split(int x, int y) { MakeRoot(x); Access(y); Splay(y); }

int n, m, kk, type;
int uu[maxn+5], vv[maxn+5];
int fp[maxn+5];
int seg[maxn+5];

int find(int x) { return fp[x]==x ? x : fp[x] = find(fp[x]); }

int tot = 0, rot[maxnode+5], sz[maxnode+5], L[maxnode+5], R[maxnode+5];
int Build(int l, int r) {
    int x = ++tot;
    if(l<r) {
        L[x] = Build(l, mid);
        R[x] = Build(mid+1, r);
    }
    return x;
}
int Upd(int px, int l, int r, int p) {
    int x = ++tot;
    L[x] = L[px], R[x] = R[px], sz[x] = sz[px]+1;
    if(l<r) {
        if(p<=mid) L[x] = Upd(L[px], l, mid, p);
        else R[x] = Upd(R[px], mid+1, r, p);
    }
    return x;
}
int Que(int x1, int x2, int l, int r, int p) {
    if(r<=p) return sz[x2]-sz[x1];
    int ret = Que(L[x1], L[x2], l, mid, p);
    if(mid<p) ret += Que(R[x1], R[x2], mid+1, r, p);
    return ret;
}

int main() {
    scanf("%d%d%d%d", &n, &m, &kk, &type);
    id[0] = mi[0] = 1<<30;
    REP(i,1,n) id[i] = mi[i] = 1<<30, fp[i] = i;
    for(int i = 1, u,v; i <= m; ++i) {
        scanf("%d%d", &u, &v);
        uu[i] = u, vv[i] = v;
        if(u == v) { seg[i] = -1; continue; }
        else if(find(u) == find(v)) {
            Split(u,v);
            seg[i] = mi[v];
            int x = mi[v] + n;
            int y = uu[x-n], z = vv[x-n];
            MakeRoot(x);
            Access(y), Splay(y), fa[x] = 0, ch[y][0] = 0, PushUp(y);
            Access(z), Splay(z), fa[x] = 0, ch[z][0] = 0, PushUp(z);
        }
        else fp[find(u)] = find(v);
        mi[i+n] = id[i+n] = i;
        MakeRoot(u), MakeRoot(v);
        fa[u] = fa[v] = i+n;
    }
    rot[0] = Build(0,m);
    for(int i = 1; i <= m; ++i) {
        if(seg[i] == -1) rot[i] = rot[i-1];
        else rot[i] = Upd(rot[i-1], 0, m, seg[i]);
    }
    int ans = 0;
    while(kk--) {
        int l, r; scanf("%d%d", &l, &r);
        if(type) l^=ans, r^=ans;
        int sub = Que(rot[l-1], rot[r], 0, m, l-1);
        ans = n-sub;
        printf("%d\n", ans);
    }
    return 0;
}
