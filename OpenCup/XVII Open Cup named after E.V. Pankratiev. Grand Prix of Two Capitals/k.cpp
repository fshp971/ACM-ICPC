#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<cassert>
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

LL S, cc[70][2], ans = 0;
int n;

bool dfs(int pt, LL sum) {
    if(pt < 0) return sum == S;
    if(double((1LL<<(pt+1)) - 1) * n < S - sum) return false;
    if(double(1LL<<pt) * cc[pt][0] <= S - sum) {
        if(dfs(pt - 1, sum + (1LL << pt) * cc[pt][0]))
            return true;
    }
    if(double(1LL<<pt) * cc[pt][1] <= S - sum) {
        ans ^= 1LL << pt;
        if(dfs(pt - 1, sum + (1LL << pt) * cc[pt][1]))
            return true;
        ans ^= 1LL << pt;
    }
    return false;
}

int main() {
    freopen("xor-cypher.in", "r", stdin);
    freopen("xor-cypher.out", "w", stdout);
    scanf("%d%lld", &n, &S);
    for(int i = 1; i <= n; ++i) {
        LL x; scanf("%lld", &x);
        for(int k = 0; k <= 59; ++k) {
            if(x>>k&1) ++cc[k][0];
            else ++cc[k][1];
        }
    }
    if(dfs(59, 0LL)) printf("%lld\n", ans);
    else puts("-1");
    return 0;
}
