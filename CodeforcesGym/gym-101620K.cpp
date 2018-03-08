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

const int maxn = 500, INF = 1 << 28;

int n = 0, seg[maxn + 5], cnt[7];
int val[4], all[4];
int f[2][maxn + 5][maxn + 5][7];

inline void Min(int &a, int b) { a = min(a,b); }

int main() {
    int T;
    char str[20];
    scanf("%d", &T);
    while(T--) {
        scanf("%s", str);
        memcpy(str+7, str, 7);
        int mx = -1, v = -1, ct = 0;
        for(int i = 0; i < 7; ++i) {
            int t = 0;
            for(int k = 0; k < 7; ++k)
                t = (t<<3) + (t<<1) + str[i+k] - '0';
            if(mx < t) mx = t, v = i, ct = 0;
            else if(mx == t) ct = 1;
        }
        if(ct) continue;
        seg[++n] = v;
    }
    ++n;
    for(int i = 1; i <= n; ++i) ++cnt[(seg[i] - seg[i-1] + 7) % 7];
    int ans = 0;
    for(int i = 1; i <= 3; ++i) {
        if(cnt[i] < cnt[7-i]) val[i-1] = 7-i, all[i-1] = cnt[7-i] - cnt[i];
        else val[i-1] = i, all[i-1] = cnt[i] - cnt[7-i];
        ans += min(cnt[i], cnt[7-i]);
    }
    int par = 0;
    REP(k,0,all[1]) REP(j,0,all[2]) FOR(t,0,7) f[par][k][j][t] = INF;
    f[par][0][0][0] = 0;
    for(int i = 0; i <= all[0]; ++i) {
        REP(k,0,all[1]) REP(j,0,all[2]) FOR(t,0,7) f[par^1][k][j][t] = INF;
        for(int k = 0; k <= all[1]; ++k) {
            for(int j = 0; j <= all[2]; ++j) {
                for(int t = 0; t < 7; ++t) {
                    int tt = (t + val[0]) % 7;
                    Min(f[par^1][k][j][tt], f[par][k][j][t] + (tt != 0));
                    tt = (t + val[1]) % 7;
                    Min(f[par][k+1][j][tt], f[par][k][j][t] + (tt != 0));
                    tt = (t + val[2]) % 7;
                    Min(f[par][k][j+1][tt], f[par][k][j][t] + (tt != 0));
                }
            }
        }
        par ^= 1;
    }
    printf("%d\n", ans + f[par^1][all[1]][all[2]][0]);
    return 0;
}
