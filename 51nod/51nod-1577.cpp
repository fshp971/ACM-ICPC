//#include<cstdio>
#include<stdio.h>
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

const int maxn = 5e5;

template<class T> inline void Read(T &x) {
    char c;
    for(c = getchar(); c < '0' || c > '9'; c = getchar());
    for(x = 0; '0' <= c && c <= '9'; c = getchar())
        x = (x << 3) + (x << 1) + c - '0';
}

int n, m;
int f[maxn][30], id[maxn + 5][30];

int main() {
    int u, v, l, r;
    Read(n);
    for(int i = 1; i <= n; ++i) {
        Read(u), v = i;
        memcpy(f[i], f[i-1], sizeof(f[i-1]));
        memcpy(id[i], id[i-1], sizeof(id[i-1]));
        for(int k = 29; k >= 0; --k) {
            if(!(u >> k & 1)) continue;
            if(f[i][k] == 0) { f[i][k] = u, id[i][k] = v; break; }
            if(id[i][k] < v) swap(f[i][k], u), swap(id[i][k], v);
            u ^= f[i][k];
        }
    }
    Read(m);
    for(int i = 1; i <= m; ++i) {
        Read(l), Read(r), Read(u);
        int fg = 1;
        for(int k = 29; k >= 0; --k) {
            if(!(u >> k & 1)) continue;
            if(f[r][k] == 0 || id[r][k] < l) { fg = 0; break; }
            u ^= f[r][k];
        }
        printf(fg ? "YES\n" : "NO\n");
    }
    return 0;
}
