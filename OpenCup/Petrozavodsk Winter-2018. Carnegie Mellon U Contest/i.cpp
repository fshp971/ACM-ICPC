#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<cassert>
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

const int maxn = 5000;

int n, V, seg[maxn + 5], f1[maxn + 5], f2[maxn + 5];
int m, val[maxn + 5], cnt[maxn + 5];
int mini;

void DP(int n, int V, int *seg, int *f) {
    memset(f, 0x7f, sizeof(int) * (V+1));
    f[0] = 0;
    for(int i = 1; i <= n; ++i) {
        for(int k = V; k >= seg[i]; --k)
            f[k] = min(f[k], f[k-seg[i]] + 1);
    }
}

int Solve2() {
    int l = 1, r = n, res = n+1, ps = (mini+1) >> 1;
    while(l <= r) {
        int mid = (l + r) >> 1;
        DP(mid, V, seg, f1);
        DP(n-mid, V, seg+mid, f2);
        bool fg = 0;
        for(int i = 0; i <= V; ++i) {
            if(f1[i]>n || f2[V-i]>n) continue;
            if(f1[i] + f2[V-i] != mini) continue;
            if(ps <= f1[i]) { fg = 1; break; }
        }
        if(fg) res = mid, r = mid - 1;
        else l = mid + 1;
    }
    return seg[res];
}

int Solve3() {
    m = 0;
    for(int i = 1; i <= n; ++i) {
        val[++m] = seg[i], cnt[m] = 1;
        while(i+1 <= n && seg[i+1] == val[m]) ++i, ++cnt[m];
    }
    int l = 1, r = n, res = n+1;
    while(l <= r) {
        int mid = (l + r) >> 1;
        mem(f1, 0x7f), f1[0] = 0;
        for(int i = 1; i <= m; ++i) {
            for(int k = min(cnt[i],mid); k >= 1; --k) {
                for(int j = V; j >= val[i]; --j)
                    f1[j] = min(f1[j], f1[j-val[i]] + 1);
            }
        }
        if(f1[V] == mini) res = mid, r = mid - 1;
        else l = mid + 1;
    }
    return res;
}

pii ff[maxn + 5];
int Solve4() {
    REP(i,0,V) ff[i] = MP(n+100, -1);
    int res = 1<<30;
    for(int i = 1; i <= n; ++i) {
        for(int k = V; k > seg[i]; --k) {
            if(ff[k-seg[i]].fi+1 < ff[k].fi)
                ff[k] = ff[k-seg[i]], ++ff[k].fi;
            else if(ff[k-seg[i]].fi+1 == ff[k].fi && ff[k-seg[i]].se > ff[k].se)
                ff[k] = ff[k-seg[i]], ++ff[k].fi;
        }
        ff[seg[i]] = MP(1,seg[i]);
        if(ff[V].fi == mini)
            res = min(res, seg[i] - ff[V].se);
    }
    return res;
}

int main() {
    scanf("%d%d", &n, &V);
    REP(i,1,n) scanf("%d", seg + i);
    sort(seg + 1, seg + 1 + n);
    DP(n, V, seg, f1), mini = f1[V];
    if(f1[V] > n) exit(puts("-1") * 0);
    double a = double(V) / f1[V];
    int b = Solve2();
    int c = Solve3();
    int d = Solve4();
    printf("%.12f %d %d %d\n", a, b, c, d);
    return 0;
}
