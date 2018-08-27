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

const int maxn = 2e4;
const LL INF = 1LL << 61;

int n, m, kk;
LL ss;
int ai[maxn+5];
LL sta[maxn+5];
int top = 0;
bool vi[maxn+5];

int q[maxn+5];
LL DP(int lim) {
    int l = 1, r = 1;
    LL ret = 0;
    q[1] = 0;
    for(int i = 1; i <= top*2; ++i) {
        while(l<=r && i-q[l]>lim) ++l;
        while(l<=r && sta[q[r]]>=sta[i]) --r;
        q[++r] = i;
        ret = max(ret, sta[i] - sta[q[l]]);
    }
    return ret;
}

LL Run() {
    LL sum = 0;
    REP(i,1,top) sum += sta[i], sta[i+top] = sta[i];
    REP(i,1,top*2) sta[i] += sta[i-1];
    if(sum <= 0) return DP( min(top,m) );
    LL ret = DP( min(top,m) );
    ret = max( ret, (m/top)*sum + DP(m%top) );
    if(m/top>=1) {
        ret = max(ret, (m/top-1)*sum + DP(top) );
    }
    return ret;
}

int main() {
    int __; scanf("%d", &__);
    for(int _ = 1; _ <= __; ++_) {
        scanf("%d%lld%d%d", &n, &ss, &m, &kk);
        REP(i,0,n-1) scanf("%d", ai+i), vi[i]=0;
        LL ans = 0LL;
        REP(i,0,n-1) {
            if(vi[i]) continue;
            sta[top=1] = ai[i], vi[i] = 1;
            for(int k = (i+kk)%n; k != i; k = (k+kk)%n) {
                sta[++top] = ai[k], vi[k] = 1;
            }
            ans = max(ans, Run());
        }
        printf("Case #%d: %lld\n", _, max(ss-ans, 0LL));
    }
    return 0;
}
