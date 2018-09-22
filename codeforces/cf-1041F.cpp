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

const int maxn = 1e5;

int n, m;
LL ai[maxn+5], bi[maxn+5];
unordered_map<LL,int> cnt;

int main() {
    int y, ans = 0;
    scanf("%d%d", &n, &y);
    REP(i,1,n)
        scanf("%lld", ai+i), ++cnt[ai[i]];
    scanf("%d%d", &m, &y);
    REP(i,1,m) {
        scanf("%lld", bi+i);
        if(cnt[bi[i]]) ans = 2;
    }
    for(int i = 0; i <= 30; ++i) {
        LL dt = 1LL<<i;
        cnt.clear();
        REP(k,1,n) ++cnt[(ai[k]+dt) % (dt<<1)];
        REP(k,1,m) ++cnt[bi[k] % (dt<<1)];
        for(auto pp : cnt) ans = max(ans, pp.se);
    }
    printf("%d\n", ans);
    return 0;
}
