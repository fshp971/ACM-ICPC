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

const int maxn = 200;
const int P = 1e9+7;

int n, ai[maxn+5];
int f[maxn+5][maxn+5][maxn+5], g[maxn+5][maxn+5];
char M[maxn+5][maxn+5];

inline void Add(int &a, int b) { a+=b; if(a>=P) a-=P; }
inline void Sub(int &a, int b) { a-=b; if(a<0) a+=P; }

int main() {
    int _; scanf("%d", &_);
    while(_--) {
        scanf("%d", &n);
        REP(i,1,n) scanf("%d", ai+i);
        REP(i,1,n) scanf("%s", M[i]+1);
        REP(i,1,n) {
            REP(k,1,n) REP(j,1,n) {
                f[i][k][j] = f[i-1][k][j];
                if(ai[i]==ai[k]&&ai[k]==ai[j]) {
                    Add(f[i][k][j], g[k-1][j-1]);
                    Add(f[i][k][j], 1);
                }
                g[k][j] = (M[ai[k]][ai[i]]=='1'&&M[ai[j]][ai[i]]=='1') ? f[i-1][k][j] : 0;
                Add(g[k][j], g[k-1][j]);
                Add(g[k][j], g[k][j-1]);
                Sub(g[k][j], g[k-1][j-1]);
            }
        }
        int ans = 0;
        REP(k,1,n) REP(j,1,n) Add(ans, f[n][k][j]);
        printf("%d\n", ans);
    }
    return 0;
}
