#include<bits/stdc++.h>

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

const int maxn = 1000;

int n, m, C, cnt = 0, col[maxn + 5];

int Run(int u) {
    if(u <= (C >> 1)) {
        for(int i = 1; i <= n; ++i) {
            if(!col[i]) { ++cnt; col[i] = u; return i; }
            if(u < col[i]) { col[i] = u; return i; }
        }
        col[n] = u; return n;
    }
    else {
        for(int i = n; i >= 1; --i) {
            if(!col[i]) { ++cnt; col[i] = u; return i; }
            if(u > col[i]) { col[i] = u; return i; }
        }
        col[1] = u; return 1;
    }
}

int main() {
    int u;
    scanf("%d%d%d", &n, &m, &C);
    while(m--) {
        scanf("%d", &u);
        printf("%d\n", Run(u));
        fflush(stdout);
        if(cnt == n) break;
    }
    return 0;
}
