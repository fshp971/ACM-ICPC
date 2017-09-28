#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define PB push_back
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 50;

int n, sum = 0, aa[maxn + 5], f[maxn + 5][2];

int main() {
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) scanf("%d", aa + i), sum += aa[i];
    for(int i = n; i >= 1; --i) {
        f[i][0] = max(f[i+1][1] + aa[i], f[i+1][0]);
        f[i][1] = min(f[i+1][0], f[i+1][1] + aa[i]);
    }
    printf("%d %d\n", sum - f[1][0], f[1][0]);
    return 0;
}
