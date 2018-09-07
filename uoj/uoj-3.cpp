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
 
const int maxn = 15e4;
const int INF = 1<<30;
 
int ch[maxn+5][2], fa[maxn+5];
int ai[maxn+5], bi[maxn+5], mb[maxn+5];
bool rev[maxn+5];
 
inline bool IsRoot(int x) { return (ch[fa[x]][0]!=x && ch[fa[x]][1]!=x); }
inline void PushUp(int x) {
    mb[x] = max( bi[x], max(mb[ch[x][0]],mb[ch[x][1]]) );
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
 
int uu[maxn+5], vv[maxn+5], aa[maxn+5], bb[maxn+5], num[maxn+5];
int fp[maxn+5];
int find(int x) { return fp[x]==x ? x : fp[x]=find(fp[x]); }
 
bool cmp(const int &a, const int &b) { return aa[a]!=aa[b] ? (aa[a]<aa[b]) : (bb[a]<bb[b]); }
 
int main() {
    int n, m; scanf("%d%d", &n, &m);
    REP(i,1,n) fp[i] = i;
    REP(i,1,m) scanf("%d%d%d%d", uu+i, vv+i, aa+i, bb+i), num[i] = i;
    sort(num+1, num+1+m, cmp);
    int ans = INF;
    for(int mm = 1; mm <= m; ++mm) {
        int u = uu[num[mm]], v = vv[num[mm]], a = aa[num[mm]], b = bb[num[mm]], id = num[mm]+n;
        ai[id] = a, bi[id] = mb[id] = b;
        if(u == v) continue;
        if(find(u) != find(v)) {
            MakeRoot(u), MakeRoot(v), fa[u] = id, fa[v] = id, fp[find(u)] = find(v);
        }
        else {
            Split(u,v);
            if(mb[v] <= b) continue;
            int x = v, key = mb[v];
            while(bi[x] != key) {
                //PushDown(x); // 此处可以不执行
                if(ch[x][0] && mb[ch[x][0]]==key) x = ch[x][0];
                else x = ch[x][1];
            }
            int y = uu[x-n], z = vv[x-n];
            MakeRoot(x);
            Access(y), Splay(y), fa[x] = 0, ch[y][0] = 0, PushUp(y);
            Access(z), Splay(z), fa[x] = 0, ch[z][0] = 0, PushUp(z);
            MakeRoot(u), MakeRoot(v);
            fa[u] = id, fa[v] = id;
        }
        if(find(1) == find(n))
            Split(1,n), ans = min(ans, a+mb[n]);
    }
    printf("%d\n", ans==INF?(-1):ans);
    return 0;
}
