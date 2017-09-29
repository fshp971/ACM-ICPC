#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define PB push_back
typedef long long LL;
typedef pair<int,int> pii;

const int maxm = 40;

int n;
int f[2][maxm*2 + 5];

inline void Min(int &a, int b) { a = min(a, b); }

int main() {
    int n, u, par = 0;
    scanf("%d", &n);
    mem(f[par], 0x7f);
    f[par][0] = 0;
    for(int i = 1; i <= n; ++i) {
        scanf("%d", &u), u /= 100;
        par ^= 1, mem(f[par], 0x7f);
        for(int k = 0; k <= maxm; ++k) {
            Min(f[par][k + u/10], f[par^1][k] + u);
            int r = min(u, k);
            Min(f[par][k - r], f[par^1][k] + u - r);
        }
    }
    int ans = 1 << 30;
    for(int i = 0; i <= maxm; ++i) Min(ans, f[par][i]);
    printf("%d\n", ans * 100);
    return 0;
}
