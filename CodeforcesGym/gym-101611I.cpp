#include <bits/stdc++.h>

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

const int maxn = 1501;
typedef bitset<maxn> BIT;

int n, m;
bool vist[maxn + 5];
BIT bt[maxn + 5];

int main() {
    scanf("%d%d", &m, &n);
    BIT tmp;
    for(int i = 1; i <= m; ++i) {
        for(int k = 0, a; k < n; ++k)
            scanf("%d", &a), tmp[k] = abs(a)&1;
        tmp[n] = 1;
        bool fg = 0;
        for(int k = 0; k < n; ++k) {
            if(!tmp[k]) continue;
            if(!vist[k]) {
                vist[k] = 1, fg = 1;
                bt[k] = tmp;
                break;
            }
            tmp ^= bt[k];
        }
        if(!fg && tmp[n]) exit( puts("No")*0 );
    }
    puts("Yes");
    return 0;
}
