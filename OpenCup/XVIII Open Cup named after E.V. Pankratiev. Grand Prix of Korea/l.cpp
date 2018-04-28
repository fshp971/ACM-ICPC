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

const int maxn = 1e5;

int n, kk;
LL T;
int A[maxn + 5], B[maxn + 5], C[maxn + 5];
bool vist[maxn + 5];

void Run(int mk) {
    int d = (1LL << mk) % n;
    FOR(i,0,n) vist[i] = 0;
    for(int i = 0; i < n; ++i) if(!vist[i]) {
        int len = 0, sum = 0;
        for(int u = i; !vist[u]; u = (u+d)%n)
            vist[u] = 1, B[len] = u, C[len++] = A[u], sum ^= A[u];
        int now = 0, be = 0, ed = (kk-1)%len;
        now = sum * ((kk/len)&1);
        int rem = kk % len;
        for(int k = 0; k < rem; ++k) now ^= C[k%len];
        for(int k = 0; k < len; ++k) {
            A[B[k]] = now;
            now ^= C[be], be = (be+1) % len;
            ed = (ed+1) % len, now ^= C[ed];
        }
    }
}

int main() {
    scanf("%d%d%lld", &n, &kk, &T);
    FOR(i,0,n) scanf("%d", A + i);
    for(int i = 0; i <= 60; ++i) {
        if(T>>i&1) Run(i);
    }
    FOR(i,0,n) printf("%d%c", A[i], (i==n-1) ? '\n' : ' ');
    return 0;
}
