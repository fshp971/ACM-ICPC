#include <bits/stdc++.h>

using namespace std;

#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define PER(i,a,b) for(int i = a; i >= b; --i)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
typedef long long LL;
typedef long double LD;

const int maxn = 1e6;

int n, f[maxn+5], mx[maxn+5], mi[maxn+5];
char ss[maxn+5];

int run(int lim) {
    int mmi = 0, mmx = 0, del = 0;
    for(int i = 1; i <= n; ++i) {
        if(ss[i]=='?' && mx[i]+del+2<=lim)
            del += 2;
        mmi = min(mmi, f[i]+del);
        mmx = max(mmx, f[i]+del);
    }
    return mmx-mmi;
}

int main() {
    scanf("%s", ss+1), n = strlen(ss+1);
    f[0] = 0;
    REP(i,1,n) {
        if(ss[i] == '1') f[i] = 1;
        else f[i] = -1;
        f[i] += f[i-1];
    }
    mx[n] = mi[n] = f[n];
    for(int i = n-1; i >= 0; --i) {
        mx[i] = max(f[i], mx[i+1]);
        mi[i] = min(f[i], mi[i+1]);
    }
    int ans = min(run(mx[0]), run(mx[0]+1));
    printf("%d\n", ans);
    return 0;
}
