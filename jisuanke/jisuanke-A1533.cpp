// ICPC 2017 南宁 D
// 其实复杂度是错的, 理论上可以卡成O(1e5 ^ 2), 然而出题人没卡
// (可能出题人没意识到自己想了个假算法)
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
#define PER(i,a,b) for(int i=a; i>=b; --i)
#define MP make_pair
#define PB push_back
#define fi first
#define se second
typedef long long LL;
typedef pair<int,int> pii;

const int maxn = 1e5;

int tot, dep[maxn+5], fail[maxn+5];
bool vi[maxn+5];
map<int,int> nx[maxn+5];

int ch[int(1e6)+10], pre[30];
char str[int(1e6)+10];

void Insert(int *a, int len) {
    int u = 0;
    for(int i = 0; i < len; ++i) {
        if(nx[u].find(a[i]) == nx[u].end()) {
            nx[u][a[i]] = ++tot;
            vi[tot] = 0, dep[tot] = dep[u]+1, nx[tot].clear();
        }
        u = nx[u][a[i]];
    }
    vi[u] = 1;
}

void GetFail() {
    fail[0] = 0;
    queue<int> q;
    for(auto pp : nx[0]) {
        fail[pp.se] = 0;
        q.push(pp.se);
    }
    while(!q.empty()) {
        int x = q.front(); q.pop();
        for(auto pp : nx[x]) {
            int u = pp.se, v = fail[x];
            q.push(u);
            while(1) {
                int c = pp.fi;
                if(pp.fi > dep[v]) c = -1;
                if(nx[v].find(c) != nx[v].end()) { fail[u] = nx[v][c]; break; }
                v = fail[v];
            }
            vi[u] |= vi[fail[u]];
        }
    }
}

int main() {
    int __; scanf("%d", &__);
    for(int _ = 1; _ <= __; ++_) {
        int T; scanf("%d", &T);
        tot = 0; nx[0].clear();
        while(T--) {
            scanf("%s", str);
            int len = 0;
            REP(i,0,25) pre[i] = -1;
            for(int i = 0; str[i] != '\0'; ++i) {
                if(pre[str[i]-'A'] == -1) ch[i] = -1;
                else ch[i] = i-pre[str[i]-'A'];
                pre[str[i]-'A'] = i;
                ++len;
            }
            Insert(ch, len);
        }
        GetFail();
        printf("Case #%d:", _);
        scanf("%d", &T);
        while(T--) {
            scanf("%s", str);
            int u = 0;
            bool fg = 0;
            REP(i,0,25) pre[i] = -1;
            for(int i = 0; str[i] != '\0'; ++i) {
                if(pre[str[i]-'A'] == -1) ch[i] = -1;
                else ch[i] = i-pre[str[i]-'A'];
                pre[str[i]-'A'] = i;

                while(1) {
                    int c = ch[i];
                    if(ch[i] > dep[u]) c = -1;
                    if(nx[u].find(c) != nx[u].end()) { u = nx[u][c]; break; }
                    u = fail[u];
                }
                if(vi[u]) { fg = 1; break; }
            }
            printf(" %c", fg ? 'Y' : 'N');
        }
        puts("");
    }
    return 0;
}
