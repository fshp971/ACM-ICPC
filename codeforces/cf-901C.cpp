#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i = a; i <= b; ++i)
#define FOR(i,a,b) for(int i = a; i < b; ++i)
#define MP make_pair
#define PB push_back
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 3e5;

int n, m, R[maxn + 5], vist[maxn + 5], pre[maxn + 5];
LL S[maxn + 5];
vector<int> G[maxn + 5];

void dfs(int x) {
    vist[x] = 1;
    for(auto it : G[x]) {
        if(it == pre[x] || vist[it] == 2) continue;
        if(!vist[it])
            pre[it] = x, dfs(it);
        else {
            int mn = it, mx = it, u = x;
            while(u != it) {
                mn = min(mn, u);
                mx = max(mx, u);
                u = pre[u];
            }
            R[mn] = min(R[mn], mx - 1);
        }
    }
    vist[x] = 2;
}

inline LL S1(LL x) { return (x*(x+1)) >> 1; }

int main() {
    int T, u, v;
    scanf("%d%d", &n, &m);
    REP(i,1,m) {
        scanf("%d%d", &u, &v);
        G[u].PB(v), G[v].PB(u);
    }
    REP(i,1,n) R[i] = n;
    REP(i,1,n) {
        if(!vist[i])
            dfs(i);
    }
    for(int i = n-1; i >= 1; --i) R[i] = min(R[i], R[i+1]);
    REP(i,1,n) S[i] = S[i-1] + R[i];
    scanf("%d", &T);
    while(T--) {
        scanf("%d%d", &u, &v);
        int l = u, r = v, ps = u-1;
        while(l <= r) {
            int mid = (l + r) >> 1;
            if(R[mid] <= v) ps = mid, l = mid + 1;
            else r = mid - 1;
        }
        LL ans = (S[ps] - S[u-1]) + LL(v) * LL(v - ps) + LL(v - u + 1);
        ans -= S1(v) - S1(u-1);
        printf("%lld\n", ans);
    }
    return 0;
}
