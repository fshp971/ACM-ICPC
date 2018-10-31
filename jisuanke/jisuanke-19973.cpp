// ICPC 2017 南宁 题面第一组样例答案是错的...
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
typedef double DB;

void FWT(DB *a, int len, int type) {
    for(int l = 1; l < len; l <<= 1) {
        for(int i = 0; i < len; i += (l<<1))
            for(int k = 0; k < l; ++k) {
                DB x = a[i+k], y = a[i+k+l];
                a[i+k] = x+y, a[i+k+l] = x-y;
                if(type == -1) a[i+k]/=2.0, a[i+k+l]/=2.0;
            }
    }
}

const DB PI = acos(-1.0);
const int maxn = 1e5;

int par, tot[2];
DB f[2][maxn+5][16], g[2][maxn+5][16];

DB p1[16], p2[16];
void Calc(int n, int fg, DB a) {
    tot[par^1] = 0;
    for(int j = 0; j < n; ++j) {
        REP(i,0,n-1) {
            DB tmp = DB(i)*fg * a - DB(i)*j/n * 2.0*PI;
            p1[i] = cos(tmp), p2[i] = sin(tmp);
        }
        REP(i,n,15) p1[i] = p2[i] = 0;
        FWT(p1, 16, 1);
        FWT(p2, 16, 1);
        for(int i = 0; i < tot[par]; ++i) {
            REP(k,0,15) {
                f[par^1][tot[par^1]][k] = f[par][i][k]*p1[k] - g[par][i][k]*p2[k];
                g[par^1][tot[par^1]][k] = f[par][i][k]*p2[k] + g[par][i][k]*p1[k];
            }
            ++tot[par^1];
        }
    }
    par^=1;
}

int main() {
    int _; scanf("%d", &_);
    int nn[10], cof;
    DB a;
    while(_--) {
        cof = 1;
        REP(i,1,5) scanf("%d", nn+i), cof *= nn[i];
        scanf("%lf", &a);
        par = 0;
        tot[par] = 1;
        REP(i,0,15) f[par][0][i] = 1, g[par][0][i] = 0;
        REP(i,1,5) {
            if(i&1) Calc(nn[i], 1, a);
            else Calc(nn[i], -1, a);
        }
        DB ans = 0;
        for(int i = 0; i < tot[par]; ++i) {
            FWT(f[par][i], 16, -1);
            DB tmp = 0;
            REP(k,0,15) tmp += f[par][i][k] * DB(k);
            ans += fabs(tmp);
        }
        ans /= pow(cof, 1.5);
        printf("%.6f\n", ans);
    }
    return 0;
}
