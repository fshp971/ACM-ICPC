#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 67;

LL ppow[maxn + 5], base;
LL f[13][maxn + 5][1200][2];
int ch[maxn + 5];

LL dfs(int pos, int msk, bool beg, bool lim) {
    if(!beg) msk = 0;
    if(pos == 0)
        return !msk ? 1 : 0;
    if(!lim && f[base][pos][msk][beg] != -1)
        return f[base][pos][msk][beg];
    LL res = 0;
    int x = lim ? ch[pos] : (base - 1);
    for(int i = 0; i <= x; ++i)
        res += dfs(pos - 1, msk ^ (1 << i), beg || i != 0, lim && i == ch[pos]);
    if(!lim) f[base][pos][msk][beg] = res;
    return res;
}

LL Calc(LL x) {
    int len = 0;
    while(x)
        ch[++len] = x % base, x /= base;
    return dfs(len, 0, 0, 1);
}

int main() {
    int T;
    LL l, r;
    scanf("%d", &T);
    mem(f, -1);
    while(T--) {
        scanf("%lld%lld%lld", &base, &l, &r);
        ppow[0] = 1;
        for(int i = 1; i <= maxn; ++i)
            ppow[i] = ppow[i-1] * (base - 1);
        printf("%lld\n", Calc(r) - Calc(l - 1));
    }
    return 0;
}
