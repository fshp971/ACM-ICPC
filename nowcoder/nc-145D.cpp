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
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
typedef long long LL;
typedef pair<int,int> pii;

int seg[][3] = {
    { 3, 3, 2 },
    { 7, 21, 3 },
    { 23, 253, 5 },
    { 71, 2485, 7 },
    { 311, 48205, 11 },
    { 479, 114481, 13 },
    { 1559, 1214461, 17 },
    { 5711, 16304905, 19 },
    { 10559, 55740961, 23 },
    { 18191, 165447145, 29 },
    { 31391, 492681745, 31 }
};

int main() {
    int M; scanf("%d", &M);
    int pt = 0;
    while(pt+1 < 11 && seg[pt+1][0] <= M) ++pt;
    int X = 1, N = seg[pt][1], T = 0, P = seg[pt][0];
    printf("%d %d %d %d\n", X, N, T, P);
    return 0;
}

// Pre
/*
LL Gcd(LL a, LL b) { return b ? Gcd(b,a%b) : a; }
inline LL Lcm(LL a, LL b) { return a / Gcd(a,b) * b; }

const int maxn = 1e5;

LL pn = -1, pa = -1;
bool Rank[maxn + 5];
bool vist[maxn + 5];

void Run(int p) {
    FOR(i,0,p) Rank[i] = 0;
    LL nn = p, aa;
    for(int i = 2; i < p; ++i) {
        if(Rank[i]) continue;
        int rk = 1;
        Rank[i] = 1;
        for(LL k = LL(i)*i; k != i; k = k*i%p) ++rk, Rank[k] = 1;
        LL tn = Lcm(nn, rk);
        if(tn%(p-1) == 0) { aa = i; break; }
        nn = tn;
    }
    if(pa < aa) {
        pn = nn, pa = aa;
        //printf("p = %d, pn = %lld, pa = %lld\n", p, pn, pa);
        printf("{ %d, %lld, %lld },\n", p, pn, pa);
    }
}

int main() {
    for(int i = 3; i <= maxn; i += 2) {
        if(!vist[i]) {
            Run(i);
            for(LL k = LL(i)*i; k <= maxn; k += i)
                vist[k] = 1;
        }
    }
    return 0;
}
*/
