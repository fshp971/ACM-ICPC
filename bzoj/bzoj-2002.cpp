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

const int maxn = 2e5 + 10;

int ch[maxn+5][2], fa[maxn+5];
int sz[maxn+5];
bool rev[maxn+5]; // 区间翻转, 主要用于实现快速换根(MakeRoot)

// 判断当前结点是否是一个树链的根
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

// 快速旋转
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

// 一般lct中的splay只需要将结点旋转到伸展树的根即可
// 因此target是不必要的, 可以删掉
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

// lct的核心操作是Access(x), 即为将x和它当前的根单独剖成一条链, 这时x是当前链最深的结点
// Split(x,y)是提出x到y的路径作为单独的一条链, 这时x是根, 而y是这条链最深的结点且被Splay()到伸展树的根
// 其他操作简单明了, 在此不做赘述
void Access(int x) { for(int y = 0; x; y = x, x = fa[x]) Splay(x), ch[x][1] = y, PushUp(x); }
void MakeRoot(int x) { Access(x); Splay(x); rev[x]^=1; }
int FindRoot(int x) { Access(x); Splay(x); while(ch[x][0]) { x = ch[x][0], PushDown(x); } return x; }
void Split(int x, int y) { MakeRoot(x); Access(y); Splay(y); }
void Cut(int x, int y) { Split(x,y); if(ch[y][0] == x) ch[y][0] = 0, PushUp(y), fa[x] = 0; }
void Link(int x, int y) { Split(x,y); if(ch[y][0] != x) fa[x] = y; }

int fp[maxn+5]; // 使用并查集判连通性(FindRoot()太慢了)
int find(int x) { return fp[x]==x ? x : fp[x]=find(fp[x]); }

void Read(int &x) {
    char c=getchar();
    while(c<'0'||c>'9') c=getchar();
    for(x=0;'0'<=c&&c<='9';x=x*10+c-'0',c=getchar());
}

int ki[maxn+5];
int main() {
    //int n; scanf("%d", &n);
    int n; Read(n);
    REP(i,1,n+1) sz[i] = 1;
    REP(i,1,n) {
        //scanf("%d", ki+i);
        Read(ki[i]);
        int u = min(i+ki[i], n+1);
        Link(u,i);
    }
    int _; scanf("%d", &_);
    while(_--) {
        int i, j, k;
        //scanf("%d%d", &i, &j), ++j;
        Read(i), Read(j), ++j;
        if(i == 1) {
            Split(n+1,j);
            printf("%d\n", sz[j]-1);
        }
        else {
            //scanf("%d", &k);
            Read(k);
            int u = min(j+ki[j], n+1);
            Cut(u,j);
            ki[j] = k, u = min(j+ki[j], n+1);
            Link(u,j);
        }
    }
    return 0;
}
