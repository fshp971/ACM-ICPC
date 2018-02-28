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

const int maxn = 1e3, maxm = 1e4;

int n, W, B, X, ci[maxn + 5], wi[maxn + 5];
LL f[maxn + 3][maxm + 3];

LL sta[maxm + 5];
int key[maxm + 5];

int main() {
    scanf("%d%d%d%d", &n, &W, &B, &X);
    REP(i,1,n) scanf("%d", ci + i);
    REP(i,1,n) scanf("%d", wi + i);
    mem(f,0x80);
    int m = 0;
    for(int i = 1; i <= n; ++i) {
        m += ci[i];
        f[i][0] = W;
        int head = 1, tail = 1;
        sta[1] = W, key[1] = 0;
        for(int k = 1; k <= m; ++k) {
            while(head <= tail && key[head] + ci[i] < k) ++head;
            if(f[i-1][k] >= 0) {
                LL tmp = min(f[i-1][k] + X, LL(k)*B + W) + LL(k) * wi[i];
                while(head <= tail && tmp >= sta[tail]) --tail;
                sta[++tail] = tmp, key[tail] = k;
            }
            if(head <= tail)
                f[i][k] = min(sta[head] - LL(k) * wi[i], LL(k)*B + W);
        }
    }
    for(int i = m; i >= 0; --i) {
        if(f[n][i] >= 0) { printf("%d\n", i); exit(0); }
    }
    return 0;
}
