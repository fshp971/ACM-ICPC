#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
typedef long long LL;
typedef unsigned long long ULL;
typedef pair<int,int> pii;

const int MaxBit = 61;
LL base[MaxBit], base2[MaxBit];

int main() {
    int T, n, m;
    LL u;
    scanf("%d", &T);
    for(int t = 1; t <= T; ++t) {
        scanf("%d", &n);
        mem(base, 0);
        bool zero = 0;
        for(int i = 1; i <= n; ++i) {
            scanf("%lld", &u);
            for(int k = MaxBit-1; k >= 0; --k) {
                if(!u) break;
                if(!(u >> k & 1)) continue;
                if(!base[k]) { base[k] = u; break; }
                u ^= base[k];
            }
            if(!u) zero = 1;
        }
        for(int i = 0; i < MaxBit; ++i) {
            for(int k = 0; k < i; ++k)
                if(base[i] >> k & 1) base[i] ^= base[k];
        }
        int cnt = 0;
        for(int i = 0; i < MaxBit; ++i)
            if(base[i]) base2[cnt++] = base[i];
        scanf("%d", &m);
        printf("Case #%d:\n", t);
        for(int i = 1; i <= m; ++i) {
            scanf("%lld", &u);
            if(zero) {
                if(u == 1) { puts("0"); continue; }
                --u;
            }
            if(u >= (1LL << cnt)) { puts("-1"); continue; }
            LL tmp = 0;
            for(int k = 0; k < cnt; ++k)
                if(u >> k & 1) tmp ^= base2[k];
            printf("%lld\n", tmp);
        }
    }
    return 0;
}
