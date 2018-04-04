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

const int maxn = 1e5;

int n, m, hh, val[maxn + 5], cnt[maxn + 5];
vector<int> G[maxn + 5];

int scc, top, Index;
int sta[maxn + 5], DFN[maxn + 5], Low[maxn + 5], Belong[maxn + 5];
bool Insta[maxn + 5], deg[maxn + 5];

void Tarjan(int u) {
    DFN[u] = Low[u] = ++Index;
    sta[++top] = u, Insta[u] = 1;
    for(auto it : G[u]) {
        if(!DFN[it]) Tarjan(it), Low[u] = min(Low[u], Low[it]);
        else if(Insta[it]) Low[u] = min(Low[u], Low[it]);
    }
    int t;
    if(DFN[u] == Low[u]) {
        ++scc;
        do {
            t = sta[top--], Insta[t] = 0, Belong[t] = scc;
        } while(t != u);
    }
}

int main() {
    scanf("%d%d%d", &n, &m, &hh);
    REP(i,1,n) scanf("%d", val + i);
    for(int i = 1, u, v; i <= m; ++i) {
        scanf("%d%d", &u, &v);
        if((val[u] + 1) % hh == val[v]) G[u].PB(v);
        if((val[v] + 1) % hh == val[u]) G[v].PB(u);
    }
    for(int i = 1; i <= n; ++i) if(!DFN[i]) Tarjan(i);
    for(int i = 1; i <= n; ++i) {
        ++cnt[Belong[i]];
        for(auto it : G[i]) if(Belong[i] != Belong[it]) deg[Belong[i]] = 1;
    }
    int pt = 0;
    for(int i = 1; i <= scc; ++i) {
        if(deg[i]) continue;
        if(!pt || cnt[i] < cnt[pt]) pt = i;
    }
    printf("%d\n", cnt[pt]);
    for(int i = 1; i <= n; ++i) if(Belong[i] == pt) printf("%d ", i);
    printf("\n");
    return 0;
}
