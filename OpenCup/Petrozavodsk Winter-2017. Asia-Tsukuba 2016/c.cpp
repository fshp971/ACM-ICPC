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

const int maxn = 2e5;

int n, m, f[maxn + 5], L[maxn + 5], R[maxn + 5];
int cnt[maxn + 5];
vector<pii> G[maxn + 5];

int Find(vector<pii>& seg, int x) {
    int l = 0, r = int(seg.size()) - 1, res = -1;
    while(l <= r) {
        int mid = (l + r) >> 1;
        if(seg[mid].fi >= x) res = mid, r = mid - 1;
        else l = mid + 1;
    }
    return res;
}

int main() {
    //freopen("in.txt", "r", stdin);
    scanf("%d%d", &n, &m);
    for(int i = 1, x, y; i <= m; ++i)
        scanf("%d%d", &x, &y), G[y].PB(MP(x,i));
    REP(i,1,n) sort(G[i].begin(), G[i].end()), L[i] = R[i] = i;
    for(int i = n-1; i >= 1; --i) {
        for(auto it : G[i]) {
            int t = Find(G[i+1], it.fi);
            if(t == -1) f[it.se] = i+1;
            else f[it.se] = f[G[i+1][t].se];
        }
    }
    for(int i = 1; i <= n; ++i)
        if(G[i].size()) R[i] = f[G[i][0].se];
    for(int i = 1; i <= n-1; ++i) {
        for(auto it : G[i]) {
            int t = Find(G[i-1], it.fi);
            if(t == -1) f[it.se] = i;
            else f[it.se] = f[G[i-1][t].se];
        }
    }
    for(int i = 1; i <= n; ++i)
        if(G[i-1].size()) L[i] = f[G[i-1][0].se];

    /*
    for(int i = 1; i <= n; ++i)
        printf("L[%d] = %d, R[%d] = %d\n", i, L[i], i, R[i]);
    */

    for(int i = 1; i <= n; ++i) ++cnt[L[i]], --cnt[R[i]+1];
    int now = 0;
    for(int i = 1; i <= n; ++i) {
        now += cnt[i];
        printf("%d%c", now, (i==n) ? '\n' : ' ');
    }
    return 0;
}
