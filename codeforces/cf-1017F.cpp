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
typedef unsigned int UINT;
typedef pair<int,int> pii;

const int maxn = 100000000 + 10;

bitset<maxn> vist;
UINT A, B, C, D;

inline int GetId(int x) {
    int d = x/6, r = x%6;
    if(r!=1 && r!=5) return -1;
    d = d*2-1;
    if(r==1) d += 1;
    else d += 2;
    return d-1;
}

void Go(int x, int n) {
    for(LL i=LL(x)*x; i<=n; i+=x) {
        int t = GetId(i);
        if(t != -1) vist[t] = 1;
    }
}

inline UINT Calc(int p, int n) {
    UINT ret = 0;
    for(LL t=p; t<=n; t*=p) ret += n/t;
    ret = ret * (A*UINT(p)*UINT(p)*UINT(p) + B*UINT(p)*UINT(p) + C*UINT(p) + D);
    return ret;
}

UINT Run(int n) {
    UINT ret = Calc(2,n) + Calc(3,n);
    Go(2,n); Go(3,n);
    int now = 5, fg = 0;
    for(int i = 0; now <= n; ++i) {
        if(!vist[i]) {
            ret += Calc(now,n);
            Go(now,n);
        }
        now += fg?4:2, fg ^= 1;
    }
    return ret;
}

int main() {
    int n; scanf("%d", &n);
    scanf("%u%u%u%u", &A, &B, &C, &D);
    printf("%u\n", Run(n));
    return 0;
}
