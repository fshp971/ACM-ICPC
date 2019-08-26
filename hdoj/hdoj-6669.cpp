#include<bits/stdc++.h>

using namespace std;

#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define PER(i,a,b) for(int i = a; i >= b; --i)
#define mem(a,b) memset(a,b,sizeof(a))
#define PB push_back
#define MP make_pair
#define fi first
#define se second
typedef long long LL;
typedef double DB;

const int maxn = 6000;
const int INF = 2e9;

int n, ai[maxn+5], bi[maxn+5];
int xx[maxn+5], all;
int f[2][maxn+5];

void Min(int &a, int b) { a = min(a,b); }

int main() {
    int _; scanf("%d", &_);
    while(_--) {
        scanf("%d", &n);
        all = 0;
        for(int i = 1; i <= n; ++i) {
            scanf("%d%d", ai+i, bi+i);
            REP(k,-1,1) {
                xx[++all] = ai[i]+k;
                xx[++all] = bi[i]+k;
            }
        }
        sort(xx+1, xx+1+all);
        all = unique(xx+1, xx+1+all) - xx - 1;
        int par = 0;
        REP(i,1,all) f[0][i] = 0;
        for(int i = 1; i <= n; ++i) {
            int l = lower_bound(xx+1, xx+1+all, ai[i]) - xx;
            int r = lower_bound(xx+1, xx+1+all, bi[i]) - xx;
            REP(i,1,all) f[par^1][i] = INF;
            for(int k = 1; k <= all; ++k) {
                if(f[par][k] == INF) continue;
                if(k < l) {
                    int step = (xx[l]-xx[k])/2;
                    int ps = step*2 + xx[k];
                    if(ps < xx[l]) {
                        Min(f[par^1][l], f[par][k]+step+1);
                        if(ps+2 <= xx[r]) Min(f[par^1][l+1], f[par][k]+step+1);
                    }
                    else Min(f[par^1][l], f[par][k]+step);
                }
                else if(k > r) {
                    int step = (xx[k]-xx[r])/2;
                    int ps = xx[k] - step*2;
                    if(ps > xx[r]) {
                        Min(f[par^1][r], f[par][k]+step+1);
                        if(ps-2 >= xx[l]) Min(f[par^1][r-1], f[par][k]+step+1);
                    }
                    else Min(f[par^1][r], f[par][k]+step);
                }
                else Min(f[par^1][k], f[par][k]);
            }
            par ^= 1;
        }
        int ans = INF;
        REP(i,1,all) Min(ans, f[par][i]);
        printf("%d\n", ans);
    }
    return 0;
}
