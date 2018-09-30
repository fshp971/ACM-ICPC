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

const int maxn = 1e6;
const int P = 1e9+7;

LL Gcd(LL a, LL b) { return b ? Gcd(b,a%b) : a; }
inline void Add(LL &a, LL b) { a+=b; if(a>=P) a-=P; }

int n, pi[maxn+5];
int f[maxn+5];
LL ai[maxn+5], cnt[maxn+5];

int main() {
    scanf("%d", &n);
    REP(i,1,n) scanf("%lld", ai+i);
    REP(i,2,n) scanf("%d", pi+i);
    PER(i,n,2) ai[pi[i]] += ai[i];
    REP(i,1,n) {
        LL v = ai[1] / Gcd(ai[1],ai[i]);
        if(v <= n) ++f[v];
    }
    PER(i,n,1) {
        for(int k = i+i; k <= n; k += i)
            f[k] += f[i];
    }
    LL ans = 0;
    cnt[1] = 1;
    for(int i = 1; i <= n; ++i) {
        if(f[i] != i) continue;
        Add(ans, cnt[i]);
        for(int k = i+i; k <= n; k += i)
            Add(cnt[k], cnt[i]);
    }
    printf("%lld\n", ans);
    return 0;
}
