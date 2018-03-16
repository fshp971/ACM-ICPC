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
typedef unsigned int UINT;

const int maxn = 1e7;

namespace fuck {
    UINT x0, x1, a, b, c;
    UINT next() {
        UINT t = x0*a  + x1*b + c;
        x0 = x1; x1 = t;
        return x0 >> 2;
    }
}

int n;
UINT seg[maxn + 5];

UINT mi;
int cnt;
void GetMi() {
    mi = seg[0], cnt = 1;
    for(int i = 1; i < n; ++i) {
        if(mi > seg[i]) mi = seg[i], cnt = 1;
        else if(mi == seg[i]) ++cnt;
    }
}

int main() {
    //freopen("in.txt", "r", stdin);
    int T, x0, x1, a, b, c;
    scanf("%d%d%d%d%d%d%d", &n, &T, &x0, &x1, &a, &b, &c);
    fuck::x0 = x0, fuck::x1 = x1, fuck::a = a, fuck::b = b, fuck::c = c;
    FOR(i,0,n) seg[i] = (UINT(1) << 31) - 1;
    //printf("seg[0] = %d\n", seg[0]);
    /*
    for(int t = 0; t <= 15; ++t) {
        UINT i = fuck::next() % n, x = fuck::next();
        printf("i = %lld, x = %lld\n", LL(i), LL(x));
    }
    exit(0);
    */
    GetMi();
    UINT base = 1, ans = 0;
    while(T--) {
        base *= 10099;
        UINT i = fuck::next() % n, x = fuck::next();
        //printf("i = %d, x = %d\n", i, x);
        if(seg[i] == mi) --cnt;
        seg[i] = x;
        if(seg[i] < mi) mi = seg[i], cnt = 1;
        else if(seg[i] == mi) ++cnt;
        if(cnt == 0) GetMi();
        ans += mi*base;
    }
    printf("%lld\n", LL(ans));
    return 0;
}
