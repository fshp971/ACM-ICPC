#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
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

const int maxn = 1e5;
const int md = 998244353;

int n, seg[maxn + 5];

LL Task1() {
    LL res = 0;
    for(int i = 0; i <= 19; ++i) {
        int one = 0, zero = 0;
        for(int k = 1; k <= n; ++k) {
            if(seg[k] >> i & 1) {
                res = (res + (1LL << i) * (zero + 1)) % md;
                swap(one, zero); ++one;
            }
            else res = (res + (1LL << i) * one) % md, ++zero;
        }
    }
    return res;
}

LL S[maxn + 5], seg2[maxn + 5], key[maxn + 5];
int tot, tree[maxn + 5];

void Inc(int x) { for(; x <= tot; x += x&(-x)) ++tree[x]; }
int Sum(int x) { int res = 0; for(; x; x -= x&(-x)) res += tree[x]; return res; }

LL Task2() {
    LL res = 0;
    for(int i = 1; i <= n; ++i) S[i] = S[i-1] + seg[i];
    for(int i = 0; i <= 37; ++i) {
        for(int k = 1; k <= n; ++k)
            seg2[k] = key[k] = S[k] % (1LL << (i+1));
        key[n + 1] = 0;
        sort(key + 1, key + 1 + n + 1);
        tot = unique(key + 1, key + 1 + n + 1) - key - 1;
        for(int k = 1; k <= tot; ++k) tree[k] = 0;
        Inc(1);
        for(int k = 1; k <= n; ++k) {
            int ps = upper_bound(key + 1, key + 1 + tot, seg2[k] - (1LL << i)) - key - 1;
            int tmp = Sum(ps);
            ps = upper_bound(key + 1, key + 1 + tot, seg2[k] + (1LL << i)) - key - 1;
            tmp += Sum(ps);
            ps = lower_bound(key + 1, key + 1 + tot, seg2[k]) - key;
            tmp -= Sum(ps);
            res ^= ((tmp & 1LL) << i);
            Inc(ps);
        }
    }
    return res;
}

int main() {
    scanf("%d", &n);
    REP(i,1,n) scanf("%d", seg + i);
    printf("%lld %lld\n", Task1(), Task2());
    return 0;
}
