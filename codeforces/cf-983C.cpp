#include <bits/stdc++.h>

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

const int maxn = 2000;
const int INF = 2000000000;

unordered_map<int,int> Hash;

int tot = 0, rev[750];
int n, ai[maxn + 5], bi[maxn + 5];
int f[2][750][10];

pii GetNx(int ii, int kk) {
    int c[4];
    int ret = 0, cost = 0;
    ii = rev[ii];
    for(int i = 3; i >= 0; --i) {
        c[i] = ii%10, ii /= 10;
        if(c[i] == kk) ++cost, c[i] = 0;
    }
    sort(c, c+4);
    ret = c[0]*1000 + c[1]*100 + c[2]*10 + c[3];
    return MP(Hash[ret], cost);
}

priority_queue<pii> que;
void Dij(int par) {
    for(int i = 0; i < tot; ++i) {
        for(int k = 1; k <= 9; ++k)
            if(f[par][i][k] < INF)
                que.push( MP(-f[par][i][k], k*1000+i) );
    }
    while(!que.empty()) {
        pii tmp = que.top(); que.pop();
        int ii = tmp.se % 1000, kk = tmp.se / 1000;
        if(-tmp.fi != f[par][ii][kk]) continue;
        for(int d = -1; d <= 1; ++d) {
            if(kk+d < 1 || kk+d > 9) continue;
            pii tmp2 = GetNx(ii, kk+d);
            if(f[par][ii][kk] + tmp2.se + abs(d) < f[par][tmp2.fi][kk+d]) {
                f[par][tmp2.fi][kk+d] = f[par][ii][kk] + tmp2.se + abs(d);
                que.push( MP(-f[par][tmp2.fi][kk+d], (kk+d)*1000+tmp2.fi) );
            }
        }
    }
}

int Chk(int ii, int nn) {
    int c[4], pt = -1;
    ii = rev[ii];
    for(int i = 3; i >= 0; --i) {
        c[i] = ii%10, ii /= 10;
        if(c[i] == 0) pt = i;
    }
    if(pt == -1) return -1;
    c[pt] = bi[nn];
    sort(c, c+4);
    return Hash[ c[0]*1000 + c[1]*100 + c[2]*10 + c[3] ];
}

int main() {
    REP(i1,0,9) REP(i2,i1,9) {
        REP(i3,i2,9) REP(i4,i3,9) {
            Hash[i1*1000 + i2*100 + i3*10 + i4] = tot;
            rev[tot++] = i1*1000 + i2*100 + i3*10 + i4;
        }
    }
    scanf("%d", &n);
    REP(i,1,n) scanf("%d%d", ai + i, bi + i);
    int par = 0;
    mem(f[par], 0x7f);
    f[par][ Hash[0] ][1] = 0;
    Dij(par);
    for(int nn = 1; nn <= n; ++nn) {
        mem(f[par^1], 0x7f);
        for(int i = 0; i < tot; ++i) {
            if(f[par][i][ai[nn]] >= INF) continue;
            int nx = Chk(i, nn);
            if(nx == -1) continue;
            f[par^1][nx][ai[nn]] = f[par][i][ai[nn]] + 1;
        }
        par ^= 1;
        Dij(par);
    }
    int ans = INF;
    for(int i = 1; i <= 9; ++i)
        ans = min(ans, f[par][ Hash[0] ][i]);
    printf("%d\n", ans);
    return 0;
}
