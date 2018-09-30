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
typedef double DB;
typedef pair<int,int> pii;

const DB eps = 1e-12;
int cmp(DB x) {
    if(fabs(x)<eps) return 0;
    return x<0 ? -1 : 1;
}

struct Node {
    DB p[3];
    Node() {}
    // p[0]: Monarch/Minister; p[1]: Rebel; p[2]: Traitor
    Node(DB _p1, DB _p2, DB _p3) {
        p[0] = _p1, p[1] = _p2, p[2] = _p3;
    }
};

Node f[40][40][40][40][4];
bool g[40][40][40][40][4];

// h1: Monarch; h2: Rebel; h3: Minister; h4: Traitor.
Node dfs(int h1, int h2, int h3, int h4, int t) {
    if(g[h1][h2][h3][h4][t]) return f[h1][h2][h3][h4][t];
    g[h1][h2][h3][h4][t] = 1;
    Node &nd = f[h1][h2][h3][h4][t];

    // Gode Game
    if(h2==0 && h4==0)
        return nd = Node(1,0,0);
    if(h1==0) {
        if(h4>0 && h2==0 && h3==0)
            return nd = Node(0,0,1);
        return nd = Node(0,1,0);
    }

    // Play
    if((t==0&&h1==0) || (t==1&&h2==0) || (t==2&&h3==0) || (t==3&&h4==0))
        return nd = dfs(h1,h2,h3,h4,(t+1)%4);
    int nh1[4], nh2[4], nh3[4], nh4[4], tot = 0;
    int th1, th2, th3, th4;
    DB np = 0;

    int rt;
    if(t==0||t==2) rt = 0;
    else rt = (t==1) ? 1 : 2;

    for(int i = 0; i <= 3; ++i) {
        if(i==t) continue;
        if((i==0&&h1==0) || (i==1&&h2==0) || (i==2&&h3==0) || (i==3&&h4==0)) continue;
        if((i==0&&t==2) || (i==2&&t==0)) continue;
        th1 = h1, th2 = h2, th3 = h3, th4 = h4;
        if(i==0) --th1;
        else if(i==1) --th2;
        else if(i==2) --th3;
        else --th4;
        Node tmp = dfs(th1, th2, th3, th4, (t+1)%4);
        if( cmp(tmp.p[rt]-np) > 0 ) {
            np = tmp.p[rt];
            tot = 1, nh1[0] = th1, nh2[0] = th2, nh3[0] = th3, nh4[0] = th4;
        }
        else if( cmp(tmp.p[rt]-np) == 0 ) {
            nh1[tot] = th1, nh2[tot] = th2, nh3[tot] = th3, nh4[tot] = th4;
            ++tot;
        }
    }
    nd = Node(0,0,0);
    for(int i = 0; i < tot; ++i) {
        Node tmp = dfs(nh1[i], nh2[i], nh3[i], nh4[i], (t+1)%4);
        REP(k,0,2) nd.p[k] += tmp.p[k];
    }
    REP(i,0,2) nd.p[i] /= DB(tot);
    return nd;
}

int main() {
    int _; scanf("%d", &_);
    while(_--) {
        int h1, h2, h3, h4;
        scanf("%d%d%d%d", &h1, &h3, &h2, &h4);
        Node ans = dfs(h1,h2,h3,h4,0);
        printf("%.6f %.6f %.6f\n", ans.p[0], ans.p[1], ans.p[2]);
    }
    return 0;
}
