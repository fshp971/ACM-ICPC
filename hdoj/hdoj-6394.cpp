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

const int maxn = 1e5 + 10, Step = 17;

int ch[maxn+5][2], fa[maxn+5];
int sz[maxn+5];
bool rev[maxn+5];

inline bool IsRoot(int x) { return (ch[fa[x]][0]!=x && ch[fa[x]][1]!=x); }
inline void PushUp(int x) {
    sz[x] = sz[ch[x][0]] + sz[ch[x][1]] + 1;
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
int FindRoot(int x) { Access(x); Splay(x); while(ch[x][0]) { x = ch[x][0], PushDown(x); } return x; }
void Split(int x, int y) { MakeRoot(x); Access(y); Splay(y); }
void Cut(int x, int y) { Split(x,y); if(ch[y][0] == x) ch[y][0] = 0, PushUp(y), fa[x] = 0; }
void Link(int x, int y) { Split(x,y); if(ch[y][0] != x) fa[x] = y; }

int n, st[maxn+5][Step+2], dep[maxn+5], fp[maxn+5];
vector<int> G[maxn+5];

void dfs(int x, int p, int d) {
    mem(st[x],0);
    st[x][0] = p, dep[x] = d;
    for(int i = 0; st[x][i]; ++i)
        st[x][i+1] = st[st[x][i]][i];
    for(auto y : G[x]) if(y!=p) dfs(y,x,d+1);
}

int Go(int x, int d) {
    if(dep[x]-d < 0) return n+1;
    for(int i = Step; i >= 0; --i)
        if(d>>i&1) x = st[x][i];
    return x;
}

int main() {
    int _; scanf("%d", &_);
    while(_--) {
        scanf("%d", &n);
        REP(i,1,n) G[i].clear();
        for(int i = 2, u; i <= n; ++i)
            scanf("%d", &u), G[u].PB(i);
        REP(i,1,n+1) sz[i] = 1, rev[i] = 0, fa[i] = 0, ch[i][0] = ch[i][1] = 0;
        dfs(1,0,0);
        REP(i,1,n) scanf("%d", fp+i), fp[i] = Go(i,fp[i]), Link(i,fp[i]);
        int T; scanf("%d", &T);
        while(T--) {
            int o, x, d;
            scanf("%d%d", &o, &x);
            if(o == 1) {
                Split(n+1, x);
                printf("%d\n", sz[x]-1);
            }
            else {
                scanf("%d", &d);
                Cut(x, fp[x]);
                fp[x] = Go(x, d);
                Link(x, fp[x]);
            }
        }
    }
    return 0;
}
