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
typedef pair<LL,LL> pLL;

const int maxn = 2e5;

int n;
int xi[maxn + 5], ri[maxn + 5];
multiset<int> Set;

int main() {
    freopen("lights.in", "r", stdin);
    freopen("lights.out", "w", stdout);
    scanf("%d", &n);
    REP(i,1,n) scanf("%d%d", xi + i, ri + i);
    for(int i = 2, ran = xi[1] + ri[1]; i <= n; ++i) {
        if(ran < xi[i]) exit(puts("-1") * 0);
        ran = max(ran, xi[i] + ri[i]);
    }
    for(int i = 1; i <= n; ++i) Set.insert(xi[i] - ri[i]);
    for(int i = 1; i <= n; ++i) {
        Set.erase( Set.find(xi[i] - ri[i]) );
        if(xi[i] < *Set.begin()) exit(puts("-1") * 0);
    }
    printf("%lld\n", 3LL * (xi[n] - xi[1]));
    return 0;

}
