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

const int maxn = 1e4;

int ch[maxn+5][2], fa[maxn+5];
int val[maxn+5], sum[maxn+5], mx[maxn+5];
bool rev[maxn+5];

inline bool IsRoot(int x) { return (ch[fa[x]][0]!=x && ch[fa[x]][1]!=x); }
inline void PushUp(int x) {
    sum[x] = sum[ch[x][0]] + sum[ch[x][1]] + val[x];
    mx[x] = max(val[x], max(mx[ch[x][0]], mx[ch[x][1]]));
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
void Splay(int x) {
    sta[top = 1] = x;
    for(int i = x; !IsRoot(i); i = fa[i]) sta[++top] = fa[i];
    while(top>0) PushDown(sta[top--]);
    while(!IsRoot(x)) {
        int y = fa[x];
        if(!IsRoot(y)) {
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

int main() {
    mx[0] = -40000;
    int n, m; scanf("%d%d", &n, &m);
    char ord[10];
    while(m--) {
        int x, y;
        scanf("%s%d%d", ord, &x, &y);
        if(ord[0] == 'C') Link(x,y);
        else if(ord[0] == 'D') Cut(x,y);
        else printf("%s\n", FindRoot(x)==FindRoot(y)?"Yes":"No");
    }
    return 0;
}
