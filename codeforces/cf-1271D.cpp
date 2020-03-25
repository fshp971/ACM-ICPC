#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define PER(i,a,b) for(int i = a; i >= b; --i)
#define PB push_back
#define MP make_pair
#define fi first
#define se second
typedef long long LL;
typedef double DB;

const int maxn = 5000;

int n, m, kk;
int ai[maxn+5], bi[maxn+5], ci[maxn+5];
int link[maxn+5];
int f[2][maxn+5];
vector<int> val[maxn+5];

void Max(int &a, int b) { a = max(a,b); }

int main() {
    scanf("%d%d%d", &n, &m, &kk);
    REP(i,1,n) scanf("%d%d%d", ai+i, bi+i, ci+i), link[i] = i;
    for(int i = 1, u,v; i <= m; ++i) {
        scanf("%d%d", &u, &v);
        link[v] = max(link[v], u);
    }
    REP(i,1,n) val[link[i]].PB( ci[i] );
    REP(i,1,n) {
        sort(val[i].begin(), val[i].end(), [&](const int &a, const int &b) { return a>b; });
        for(int k = 1; k < val[i].size(); ++k) val[i][k] += val[i][k-1];
    }
    int par = 0;
    mem(f[par], -1);
    f[par][kk] = 0;
    REP(i,1,n) {
        mem(f[par^1], -1);
        for(int k = ai[i]; k <= maxn; ++k) if(f[par][k]!=-1) {
            Max(f[par^1][k+bi[i]], f[par][k]);
            for(int j = 1; j<=k+bi[i] && j<=val[i].size(); ++j) {
                Max(f[par^1][k+bi[i]-j], f[par][k] + val[i][j-1]);
            }
        }
        par ^= 1;
    }
    int ans = -1;
    REP(i,0,maxn) Max(ans, f[par][i]);
    printf("%d\n", ans);
    return 0;
}
