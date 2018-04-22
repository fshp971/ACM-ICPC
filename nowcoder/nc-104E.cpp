#include<bits/stdc++.h>
 
using namespace std;
 
#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define FOR(i,a,b) for(int i = a; i < b; ++i)
#define mem(a,b) memset(a,b,sizeof(a))
#define MP make_pair
#define PB push_back
#define fi first
#define se second
typedef long long LL;
typedef pair<int,int> pii;
 
const int maxn = 1550;
const int maxl = maxn * maxn;
 
int n, m, limx, limy;
int seg[maxl + 5];
int dow[maxl + 5], rig[maxl + 5];
int cav[maxn + 5][maxn + 5];
LL f[maxn + 5][maxn + 5];
 
inline int Ha(int x, int y) { return x*(n+1) + y; }
 
void DrawD(int y) {
    if(y == n+1) return;
    int pt = Ha(0,y);
    for(int i = 0; i <= limx; ++i)
        cav[i][y] = pt, pt = dow[pt];
}
 
void DrawR(int x) {
    if(x == n+1) return;
    int pt = Ha(x,0);
    for(int i = 0; i <= limy; ++i)
        cav[x][i] = pt, pt = rig[pt];
}
 
void ConR(int x1, int y1, int x2, int y2, int L) {
    for(int i = 0; i < L; ++i)
        rig[ cav[x1+i][y1] ] = cav[x2+i][y2];
}
 
void ConD(int x1, int y1, int x2, int y2, int L) {
    for(int i = 0; i < L; ++i)
        dow[ cav[x1][y1+i] ] = cav[x2][y2+i];
}
 
void Output() {
    limx = n, limy = n;
    for(int i = 0; i <= n; ++i) DrawR(i);
    for(int i = 1; i <= n; ++i)
        for(int k = 1; k <= n; ++k) f[i][k] = seg[ cav[i][k] ];
    return;
}
 
inline void Read(int &x) {
    char c = getchar();
    while(c < '0' || c > '9') c = getchar();
    for(x = 0; '0' <= c && c <= '9'; x = (x<<1) + (x<<3) + c - '0', c = getchar());
}

int main() {
    Read(n), Read(m);
    for(int i = 1; i <= n; ++i) {
        for(int k = 1; k <= n; ++k)
            Read(seg[Ha(i,k)]);
    }
    mem(dow, -1), mem(rig, -1), mem(cav, -1);
    for(int i = 0; i <= n; ++i) {
        for(int k = 0; k <= n; ++k) {
            if(i+1 <= n) dow[Ha(i,k)] = Ha(i+1,k);
            if(k+1 <= n) rig[Ha(i,k)] = Ha(i,k+1);
        }
    }
    while(m--) {
        int x, y, L;
        scanf("%d%d%d", &x, &y, &L);
        limx = min(n, x + L*2);
        limy = min(n, y + L*2);

        DrawR(x-1); DrawR(x), DrawR(x+L-1), DrawR(x+L), DrawR(x+(L<<1)-1), DrawR(x+(L<<1));
        DrawD(y-1); DrawD(y), DrawD(y+L-1), DrawD(y+L), DrawD(y+(L<<1)-1), DrawD(y+(L<<1));
 
        //type 1
        ConR(x, y+L-1, x, y+(L<<1), L);
        ConD(x+L-1, y, x, y+L, L);
        ConD(x-1, y+L, x, y, L);
 
        //type 2
        ConR(x, y+L*2-1, x+L, y+L*2, L);
        ConD(x+L-1, y+L, x+L*2, y+L, L);
 
        //type 3
        ConR(x+L, y+L*2-1, x, y+L, L);
        ConD(x+L*2-1, y+L, x+L*2, y, L);
        ConR(x+L, y-1, x+L, y+L, L);
 
        //type 4
        ConD(x-1, y, x+L, y, L);
        ConR(x+L, y+L-1, x, y, L);
        ConD(x+L*2-1, y, x+L, y+L, L);
        ConR(x, y-1, x+L, y, L);
    }
    Output();
    for(int i = 1; i <= n; ++i) {
        for(int k = 1; k <= n; ++k)
            f[i][k] = max(f[i-1][k], f[i][k-1]) + f[i][k];
    }
    printf("%lld\n", f[n][n]);
    return 0;
}
