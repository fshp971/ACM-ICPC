#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define PER(i,a,b) for(int i = a; i >= b; --i)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
typedef long long LL;
typedef long double LD;

const int maxn = 1e5;

int ai[2][maxn+5];

int main() {
    int _; scanf("%d", &_);
    while(_--) {
        int n, zero = 0, fg = 0; scanf("%d", &n);
        REP(i,1,n) scanf("%d", ai[fg]+i);
        for(int i = 1; i <= n; ++i) {
            if(ai[fg][i] > 0) break;
            ++zero;
        }
        for(int i = zero+1; i <= n; ++i)
            ai[fg][i-zero] = ai[fg][i];
        n -= zero;
        while(n > 1) {
            sort(ai[fg]+1, ai[fg]+1+n);
            int tn = unique(ai[fg]+1, ai[fg]+1+n) - ai[fg] - 1;
            int tp = 0;
            for(int i = 1; i < tn; ++i)
                ai[fg^1][++tp] = ai[fg][i+1] - ai[fg][i];
            if(zero) ai[fg^1][++tp] = ai[fg][1], --zero;
            zero += n-tn;
            fg ^= 1, n = tp;
        }
        if(n == 0) puts("0");
        else printf("%d\n", ai[fg][1]);
    }
    return 0;
}
