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
const int maxnode = maxn * 25;

int n, m, q, seg[maxn+5];
int tot = 0;
int rot[maxn+5];
int ch[maxnode+5][2], fa[maxnode+5], sz[maxnode+5], val[maxnode+5];

int NewNode(int v, int p) {
    ++tot;
    val[tot] = v, fa[tot] = p, sz[tot] = 1;
    ch[tot][0] = ch[tot][1] = 0;
    return tot;
}

void PushUp(int x) {
    sz[x] = sz[ch[x][0]] + sz[ch[x][1]] + 1;
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

void Splay(int &rt, int x, int target) {
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
    if(!target) rt = x;
}

void Insert(int &rt, int &x, int v, int p = 0) {
    if(x == 0) {
        x = NewNode(v,p);
        Splay(rt,x,0);
    }
    else {
        if(seg[v] < seg[val[x]]) Insert(rt, ch[x][0], v, x);
        else Insert(rt, ch[x][1], v, x);
    }
}

int Kth(int x, int k) {
    if(sz[x] < k) return -1;
    while(x) {
        if(k == sz[ch[x][0]]+1) return val[x];
        if(k <= sz[ch[x][0]]) x = ch[x][0];
        else k -= sz[ch[x][0]]+1, x = ch[x][1];
    }
    assert(false);
    return 0;
}

int fp[maxn+5];
int find(int x) { return fp[x]==x ? x : fp[x]=find(fp[x]); }

queue<int> que;
void Merge(int u, int v) {
    u = find(u), v = find(v);
    if(u == v) return;
    if(sz[rot[u]] < sz[rot[v]]) swap(u,v);
    fp[v] = u;
    que.push(rot[v]);
    while(!que.empty()) {
        int x = que.front(); que.pop();
        Insert(rot[u], rot[u], val[x]);
        if(ch[x][0]) que.push(ch[x][0]);
        if(ch[x][1]) que.push(ch[x][1]);
    }
}

int main() {
    scanf("%d%d", &n, &m);
    REP(i,1,n) {
        scanf("%d", seg+i);
        fp[i] = i, rot[i] = NewNode(i,0);
    }
    for(int i = 1, u, v; i <= m; ++i) {
        scanf("%d%d", &u, &v);
        Merge(u,v);
    }
    char ord[5];
    int a, b;
    scanf("%d", &q);
    while(q--) {
        scanf("%s%d%d", ord, &a, &b);
        if(ord[0] == 'B') Merge(a,b);
        else printf("%d\n", Kth(rot[find(a)],b));
    }
    return 0;
}
