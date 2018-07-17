#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
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
#include<stack>

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
const int maxnode = 1e5, c_sz = 26;

struct Tire {
    int top;
    int nex[maxnode + 5][c_sz + 5], val[maxnode + 5];
    int fail[maxnode + 5];
    void Clear() { top = val[0] = 0; mem(nex[0],0); }
    inline int c_id(char c) { return c-'a'; }
    void Insert(char *a, int len, int vv) {
        int u = 0, t;
        for(int i = 0; i < len; ++i) {
            t = c_id(a[i]);
            if(!nex[u][t]) {
                nex[u][t] = ++top, val[top] = 0;
                mem(nex[top], 0);
            }
            u = nex[u][t];
        }
        val[u] = vv;
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
                if(!u) { nex[x][i] = nex[fail[x]][i]; continue; }
                q.push(u);
                int v = fail[x];
                while(v && !nex[v][i]) v = fail[v];
                fail[u] = nex[v][i];
            }
        }
    }
} AC;

char str[maxn + 5], buf[maxn + 5];
int n, kk[maxn + 5], off[maxn + 5], llen[maxn + 5];
int ans[maxn + 5];
vector<int> gp[maxn + 5], ok[maxn + 5];

int main() {
    scanf("%s", str);
    scanf("%d", &n);
    for(int i = 1; i <= n; ++i) {
        off[i] = off[i-1] + llen[i-1];
        scanf("%d%s", kk + i, buf + off[i]);
        llen[i] = strlen(buf + off[i]);
        gp[llen[i]].PB(i);
    }
    for(int i = 1; i <= maxn; ++i) {
        if(!gp[i].size()) continue;
        AC.Clear();
        for(auto x : gp[i])
            AC.Insert(buf+off[x], llen[x], x);
        AC.GetFail();
        for(int k = 0, u = 0; str[k] != '\0'; ++k) {
            int c = str[k] - 'a';
            u = AC.nex[u][c];
            if(AC.val[u]) ok[ AC.val[u] ].PB(k);
        }
        for(auto x : gp[i]) {
            ans[x] = 1<<30;
            for(int s = 0, t = 0; t < ok[x].size(); ++t) {
                if(t-s+1 > kk[x]) ++s;
                if(t-s+1 == kk[x])
                    ans[x] = min(ans[x], ok[x][t] - ok[x][s] + i);
            }
            if(ans[x] == (1<<30)) ans[x] = -1;
        }
    }
    for(int i = 1; i <= n; ++i) printf("%d\n", ans[i]);
    return 0;
}
