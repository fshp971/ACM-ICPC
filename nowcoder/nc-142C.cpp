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

const int md = 1e9 + 7;
const int maxk = 60;

LL n;
LL f[maxk + 5][2][maxk*2 + 5];

inline void Add(LL &a, LL b) { a+=b; if(a>=md) a-=md; }

// fg1: 是否开始; fg2: 是否顶格
LL dfs(int pt, int las, int del, int fg1, int fg2) {
    if(pt < 0) {
        if(!fg1) return 0;
        return abs(del);
    }
    if(fg1 && !fg2 && f[pt][las][del+maxk] != -1)
        return f[pt][las][del+maxk];
    LL ret = 0;
    int lim = fg2 ? (n>>pt&1) : 1;
    for(int i = 0; i <= lim; ++i) {
        Add( ret, dfs(pt-1, i, del + fg1 * (i==las ? 1 : -1), fg1 || i==1, fg2 && i==lim) );
    }
    if(fg1 && !fg2) f[pt][las][del+maxk] = ret;
    return ret;
}

int main() {
    mem(f, -1);
    int T; scanf("%d", &T);
    while(T--) {
        scanf("%lld", &n);
        printf("%lld\n", dfs(maxk, 0, 0, 0, 1));
    }
    return 0;
}
