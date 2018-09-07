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

const int maxn = 4e5;

int ch[maxn+5][2], fa[maxn+5];
int val[maxn+5], mi[maxn+5], len[maxn+5], sum[maxn+5];
bool rev[maxn+5];

inline bool IsRoot(int x) { return (ch[fa[x]][0]!=x && ch[fa[x]][1]!=x); }
inline void PushUp(int x) {
    sum[x] = sum[ch[x][0]] + sum[ch[x][1]] + len[x];
    mi[x] = min(val[x], min(mi[ch[x][0]], mi[ch[x][1]]));
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
        if(!IsRoot(y) && fa[y]!=target) {
            if((ch[fa[y]][0]==y)^(ch[y][0]==x)) Rotate(x);
            else Rotate(y);
        }
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

int fp[maxn+5];
int find(int x) { return fp[x]==x ? x : fp[x]=find(fp[x]); }

int main() {
    val[0] = mi[0] = 1e9+10;
    int n, m; scanf("%d%d", &n, &m);
    REP(i,1,n) val[i] = mi[i] = 1e9 + 10, fp[i] = i;
    char ord[10];
    while(m--) {
        scanf("%s", ord);
        if(ord[0] == 'f') {
            int id, u, v, t, l;
            scanf("%d%d%d%d%d", &id, &u, &v, &t, &l);
            id += n+1, ++u, ++v;
            val[id] = mi[id] = t, len[id] = sum[id] = l;
            if(find(u) != find(v)) {
                fp[find(u)] = find(v);
                MakeRoot(u);
                MakeRoot(v);
                fa[v] = id, fa[u] = id;
            }
            else {
                Split(u,v);
                if(mi[v] >= t) continue;
                int key = mi[v];
                int x = v;
                while(1) {
                    if(val[x] == key) break;
                    if(ch[x][0] && mi[ch[x][0]] == key) x = ch[x][0];
                    else x = ch[x][1];
                }
                Splay(x);
                int y = ch[x][0], z = ch[x][1];
                while(PushDown(y), ch[y][1]) y = ch[y][1];
                while(PushDown(z), ch[z][0]) z = ch[z][0];
                MakeRoot(x);
                Access(y), Splay(y), fa[x] = 0, ch[y][0] = 0, PushUp(y);
                Access(z), Splay(z), fa[x] = 0, ch[z][0] = 0, PushUp(z);
                MakeRoot(u), MakeRoot(v);
                fa[u] = id, fa[v] = id;
            }
        }
        else if(ord[0] == 'm') {
            int u, v;
            scanf("%d%d", &u, &v);
            ++u, ++v;
            if(find(u) != find(v)) puts("-1");
            else {
                Split(u,v);
                printf("%d\n", sum[v]);
            }
        }
        else {
            int id, l;
            scanf("%d%d", &id, &l);
            id += n+1;
            MakeRoot(id);
            len[id] = l; PushUp(id);
        }
    }
    return 0;
}
