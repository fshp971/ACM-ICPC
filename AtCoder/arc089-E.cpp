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

const int maxn = 100;

int A, B, dis[12][12];
int D[maxn + 5][maxn + 5];

int main() {
    scanf("%d%d", &A, &B);
    REP(i,1,A) REP(k,1,B) scanf("%d", &dis[i][k]);
    for(int a = 0; a <= 100; ++a)
        for(int b = 0; b <= 100; ++b) {
            REP(i,1,A) REP(k,1,B)
                D[a][b] = max(D[a][b], dis[i][k] - a*i - b*k);
            D[a][b] = min(D[a][b], 100);
        }
    for(int i = 1; i <= A; ++i)
        for(int k = 1; k <= B; ++k) {
            int d = 1 << 30;
            REP(a,0,100) REP(b,0,100)
                d = min(d, D[a][b] + a*i + b*k);
            if(d != dis[i][k]) exit(0 * puts("Impossible"));
        }
    puts("Possible");
    printf("%d %d\n", 202, 101*101 + 100*2);
    for(int i = 1; i <= 100; ++i) printf("%d %d X\n", i, i+1);
    for(int i = 1; i <= 100; ++i) printf("%d %d Y\n", i+101, i+1+101);
    for(int i = 0; i <= 100; ++i)
        for(int k = 0; k <= 100; ++k)
            printf("%d %d %d\n", i+1, 101-k + 101, D[i][k]);
    puts("1 202");
    return 0;
}
