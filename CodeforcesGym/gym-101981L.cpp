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

const int maxn = 5000;

int n, hf, x, y;
int ai[maxn+5];
int f[2][maxn+100][4][4][3];
int L[maxn+5], R[maxn+5];

inline void Min(int &a, int b) { a = min(a,b); }

int main() {
    scanf("%d%d%d", &n, &x, &y), hf = ((n+1)>>1) + 10;
    REP(i,1,n) {
        scanf("%d", ai+i);
        if(ai[i]==x) ai[i] = 0;
        else if(ai[i]==y) ai[i] = 1;
        else ai[i] = 2;
    }
    REP(i,0,n) {
        L[i] = -(min(i+1, n-i));
        R[i] = min(i, n-i+1);
    }
    int par = 0;
    REP(i,L[0],R[0]) mem(f[par][i+hf],0x7f);
    f[par][0+hf][0][0][2] = 0;
    for(int i = 1; i <= n; ++i) {
        REP(k,L[i],R[i]) mem(f[par^1][k+hf], 0x7f);
        REP(k,L[i-1],R[i-1]) {
            REP(p1,0,3) REP(p2,0,3) REP(c,0,2) {
                if(f[par][k+hf][p1][p2][c]>n) continue;
                if(c==2) {
                    Min(f[par^1][k+hf][p1][p2][ai[i]], f[par][k+hf][p1][p2][c]);
                    if(ai[i]==2) Min(f[par^1][k+1+hf][p1][p2][c], f[par][k+hf][p1][p2][c]);
                }
                else if(c==1) {
                    if(ai[i]==2) {
                        Min(f[par^1][k+hf][p1][p2|2][ai[i]], f[par][k+hf][p1][p2][c]);
                        Min(f[par^1][k+1+hf][p1][p2][c], f[par][k+hf][p1][p2][c]);
                    }
                    else if(ai[i]==1) {
                        Min(f[par^1][k+hf][p1][p2][c], f[par][k+hf][p1][p2][c]);
                    }
                    else {
                        Min(f[par^1][k-1+hf][p1][p2|2][ai[i]], f[par][k+hf][p1][p2][c]+1);
                        Min(f[par^1][k+hf][p1|1][p2][c], f[par][k+hf][p1][p2][c]+1);
                    }
                }
                else {
                    if(ai[i]==2) {
                        Min(f[par^1][k+hf][p1|2][p2][ai[i]], f[par][k+hf][p1][p2][c]);
                        Min(f[par^1][k+1+hf][p1][p2][c], f[par][k+hf][p1][p2][c]);
                    }
                    else if(ai[i]==0) {
                        Min(f[par^1][k+hf][p1][p2][c], f[par][k+hf][p1][p2][c]);
                    }
                    else {
                        Min(f[par^1][k-1+hf][p1|2][p2][ai[i]], f[par][k+hf][p1][p2][c]+1);
                        Min(f[par^1][k+hf][p1][p2|1][c], f[par][k+hf][p1][p2][c]+1);
                    }
                }
            }
        }
        par ^= 1;
    }
    int ans = 1<<30;
    REP(k,0,R[n]) {
        REP(p1,0,3) {
            if(p1==1) continue;
            REP(p2,0,3) {
                if(p2==1) continue;
                REP(c,0,2) Min(ans, f[par][k+hf][p1][p2][c]);
            }
        }
    }
    if(ans>n) puts("-1");
    else printf("%d\n", ans);
    return 0;
}
