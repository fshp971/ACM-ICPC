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

const int maxn = 3e5;

int ch[maxn+5][2], fa[maxn+5];
int val[maxn+5], sum[maxn+5];
bool rev[maxn+5];

inline bool IsRoot(int x) { return (ch[fa[x]][0]!=x && ch[fa[x]][1]!=x); }
inline void PushUp(int x) {
    sum[x] = sum[ch[x][0]] ^ sum[ch[x][1]] ^ val[x];
}
inline void PushDown(int x) {
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
    if(!IsRoot(p)) {
        if(ch[fa[p]][0] == p) ch[fa[p]][0] = x;
        else ch[fa[p]][1] = x;
    }
    fa[p] = x, ch[x][d] = p;
    PushUp(p), PushUp(x);
}

int top, sta[maxn+5];
void Splay(int x) {
    sta[top = 1] = x;
    for(int i = x; !IsRoot(i); i = fa[i]) sta[++top] = fa[i];
    while(top>0) PushDown(sta[top--]);
    while(!IsRoot(x)) {
        int p = fa[x];
        if(ch[p][0] == x) {
            if(!IsRoot(p) && ch[fa[p]][0] == p) Rotate(p,1);
            Rotate(x,1);
        }
        else {
            if(!IsRoot(p) && ch[fa[p]][1] == p) Rotate(p,0);
            Rotate(x,0);
        }
    }
}

void Access(int x) { for(int y=0; x; y=x, x=fa[x]) Splay(x), ch[x][1]=y, PushUp(x); }
void MakeRoot(int x) { Access(x); Splay(x); rev[x]^=1; }
int FindRoot(int x) { Access(x); Splay(x); while(ch[x][0]) { x=ch[x][0], PushDown(x); } return x; }
void Split(int x, int y) { MakeRoot(x); Access(y); Splay(y); }
void Cut(int x, int y) {
    MakeRoot(x); Access(y); Splay(y);
    if(ch[y][0] == x) ch[y][0] = 0, PushUp(y), fa[x] = 0;
}
void Link(int x, int y) { MakeRoot(x); if(FindRoot(y) != x) fa[x] = y; }

int main() {
    int n, m; scanf("%d%d", &n, &m);
    for(int i = 1, a; i <= n; ++i) {
        scanf("%d", &a);
        val[i] = sum[i] = a;
    }
    while(m--) {
        int o, x, y;
        scanf("%d%d%d", &o, &x, &y);
        if(o == 0) {
            Split(x,y);
            printf("%d\n", sum[y]);
        }
        else if(o == 1) {
            Link(x,y);
        }
        else if(o == 2) {
            Cut(x,y);
        }
        else {
            Splay(x);
            val[x] = y;
            PushUp(x);
        }
    }
    return 0;
}
