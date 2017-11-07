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

const int maxn = 100000, maxd = 100;

int n, dd, kk;
int A[maxn + 2][maxd + 2], res[maxd + 2][maxd + 2], diag[maxn + 2], vec[maxn + 2];

inline void Read(int &x) {
    int c;
    for(c = getchar(); c < '0' || c > '9'; c = getchar());
    for(x = 0; '0' <= c && c <= '9'; c = getchar())
        x = (x << 3) + (x << 1) + c - '0';
}

void Check(int x) {
    int tmp;
    for(int i = 1; i <= n; ++i)
        if(i != x) {
            tmp = 0;
            for(int k = 1; k <= dd; ++k)
                tmp += A[x][k] * A[i][k];
            if(tmp % kk == 0) {
                printf("%d %d\n", min(x,i), max(x,i));
                return;
            }
        }
}

void Run2() {
    REP(i,1,n) {
        REP(k,1,dd) diag[i] += A[i][k] * A[i][k];
        diag[i] &= 1;
    }
    int T = 5, tmp, fg;
    while(T--) {
        fg = 0;
        for(int i = 1; i <= n; ++i) vec[i] = rand() & 1, fg += vec[i];
        for(int i = 1; i <= dd; ++i) {
            res[0][i] = 0;
            for(int k = 1; k <= n; ++k)
                res[0][i] += A[k][i] * vec[k];
            res[0][i] &= 1;
        }
        for(int i = 1; i <= n; ++i) {
            tmp = 0;
            for(int k = 1; k <= dd; ++k)
                tmp += A[i][k] * res[0][k];
            tmp = (tmp - diag[i] * vec[i] + kk) & 1;
            if(tmp != (fg - vec[i]) % kk) { Check(i); return; }
        }
    }
    puts("-1 -1");
}

void Run3() {
    REP(i,1,n) {
        REP(k,1,dd) diag[i] += A[i][k] * A[i][k];
        diag[i] = (bool)diag[i];
    }
    int T = 5, tmp, fg;
    while(T--) {
        fg = 0;
        for(int i = 1; i <= n; ++i) vec[i] = rand() % kk, fg += vec[i];
        for(int t = 1; t <= dd; ++t) {
            for(int i = 1; i <= dd; ++i) {
                res[t][i] = 0;
                for(int k = 1; k <= n; ++k)
                    res[t][i] += A[k][i] * A[k][t] * vec[k];
                res[t][i] %= kk;
            }
        }
        for(int i = 1; i <= n; ++i) {
            tmp = 0;
            for(int t = 1; t <= dd; ++t) {
                for(int k = 1; k <= dd; ++k)
                    tmp += A[i][k] * A[i][t] * res[t][k];
            }
            tmp = (tmp - diag[i] * vec[i] + kk) % kk;
            if(tmp != (fg - vec[i]) % kk) { Check(i); return; }
        }
    }
    puts("-1 -1");
}

int main() {
    srand(345793289);
    Read(n), Read(dd), Read(kk);
    REP(i,1,n) REP(k,1,dd) Read(A[i][k]), A[i][k] %= kk;
    if(kk == 2) Run2();
    else Run3();
    return 0;
}
