#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
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

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 1e3, md = 1e4;

int f[2][maxn + 2];

int main() {
    int n, kk, par = 0;
    scanf("%d%d", &n, &kk);
    f[par][0] = 1;
    for(int i = 2; i <= n; ++i) {
        par ^= 1, mem(f[par], 0);
        int tmp = 0;
        for(int k = 0, j = 0; j <= kk; ++j) {
            tmp = (tmp + f[par^1][j]) % md;
            while(k + i - 1 < j) tmp = (tmp - f[par^1][k++] + md) % md;
            f[par][j] = tmp;
        }
    }
    printf("%d\n", f[par][kk]);
    return 0;
}
