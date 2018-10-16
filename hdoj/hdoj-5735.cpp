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

const int P = 1e9+7;

int n, o, wi[(1<<16)+5];
vector<int> G[(1<<16)+5];
LL ans;
LL f[(1<<8)+5][(1<<8)+5];
LL g[(1<<16)+5][(1<<8)+5];

inline int opt(int x, int y) {
    if(o == 0) return x&y;
    if(o == 1) return x|y;
    return x^y;
}

void dfs(int x, int p) {
    int a = wi[x]>>8, b = wi[x]-(a<<8);
    LL res = 0;
    for(int i = 0; i < (1<<8); ++i) {
        if(f[i][b] != -1) res = max(res, f[i][b] + (opt(a,i)<<8));
    }
    ans = (ans + (res+wi[x]) * x) % P;
    for(int i = 0; i < (1<<8); ++i) {
        g[x][i] = f[a][i];
        f[a][i] = max(f[a][i], res + opt(b,i));
    }
    for(auto y : G[x]) dfs(y,x);
    for(int i = 0; i < (1<<8); ++i) f[a][i] = g[x][i];
}

int main() {
    int _; scanf("%d", &_);
    char ord[10];
    while(_--) {
        scanf("%d%s", &n, ord);
        o = (ord[0]=='A') ? 0 : (ord[0]=='O' ? 1 : 2);
        REP(i,1,n) scanf("%d", wi+i), G[i].clear();
        for(int i = 2, fa; i <= n; ++i) {
            scanf("%d", &fa), G[fa].PB(i);
        }
        ans = 0;
        mem(f,-1);
        dfs(1,0);
        printf("%lld\n", ans);
    }
    return 0;
}
