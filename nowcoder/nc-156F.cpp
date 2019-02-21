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

const int maxn = 1e5;
const int P = 998244353;

inline LL PowMod(LL a, LL b) { LL r=1; while(b) { if(b&1) r=r*a%P; a=a*a%P, b>>=1; } return r; }

int n, inv[maxn+5];
vector<int> G[maxn+5];

int ans = 0;
void dfs(int x, int p, int d) {
    ans = (ans+inv[d]) % P;
    for(auto y : G[x]) if(y!=p) {
        dfs(y,x,d+1);
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 1, u,v; i < n; ++i) {
        scanf("%d%d", &u, &v);
        G[u].PB(v), G[v].PB(u);
    }
    inv[1] = 1;
    REP(i,2,n) inv[i] = LL(P-P/i) * inv[P%i] % P;
    dfs(1,0,1);
    printf("%d\n", ans);
    return 0;
}

