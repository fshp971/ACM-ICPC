#include<bits/stdc++.h>

using namespace std;

#define mem(a,b) memset(a,b,sizeof(a))
#define REP(i,a,b) for(int i=a; i<=b; ++i)
#define FOR(i,a,b) for(int i=a; i<b; ++i)
#define MP make_pair
#define PB push_back
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 1e6;
const int maxnode = 1e6, c_sz = 26;

struct Tire {
    int top;
    int nex[maxnode + 5][c_sz], dep[maxnode + 5];
    int fail[maxnode + 5];
    void clear() { dep[top = 0] = 0; mem(nex[0], 0); }
    inline int c_id(char c) { return c - 'a'; }
    void Insert(char *a) {
        int len = strlen(a), u = 0, t;
        for(int i = 0; i < len; ++i) {
            t = c_id(a[i]);
            if(!nex[u][t]) {
                nex[u][t] = ++top;
                dep[top] = dep[u] + 1;
                mem(nex[top], 0);
            }
            u = nex[u][t];
        }
    }
    void GetFail() {
        fail[0] = 0;
        queue<int> q;
        for(int i = 0; i < c_sz; ++i) if(int &t = nex[0][i]) {
            fail[t] = 0; q.push(t);
        }
        while(!q.empty()) {
            int x = q.front(); q.pop();
            for(int i = 0; i < c_sz; ++i) {
                int u = nex[x][i];
                if(!u) continue;
                q.push(u);
                int v = fail[x];
                while(v && !nex[v][i]) v = fail[v];
                fail[u] = nex[v][i];
            }
        }
    }
} AC;

char str[maxn + 5];
vector<int> G[maxnode + 5];
LL f[maxnode + 5][2];

void dfs(int x, int pre) {
    f[x][0] = 0, f[x][1] = 1;
    for(auto it : G[x]) {
        if(it == pre) continue;
        dfs(it, x);
        f[x][0] += max(f[it][0], f[it][1]);
        if(AC.dep[x] + 1 == AC.dep[it])
            f[x][1] += f[it][0];
        else f[x][1] += max(f[it][0], f[it][1]);
    }
}

int main() {
    int T, n;
    scanf("%d", &T);
    while(T--) {
        scanf("%d", &n);
        AC.clear();
        for(int i = 1; i <= n; ++i) {
            scanf("%s", str);
            AC.Insert(str);
        }
        AC.GetFail();
        for(int i = 0; i <= AC.top; ++i) G[i].clear();
        for(int i = 1; i <= AC.top; ++i)
            G[AC.fail[i]].PB(i);
        dfs(0, -1);
        printf("%lld\n", f[0][0]);
    }
    return 0;
}
