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

const int maxn = 1e6;

int n, id[maxn + 5], off[maxn + 5];
int ans[maxn + 5], cnt[maxn + 5];
vector<int> G[maxn + 5];
map<int,int> Map[maxn + 5];

void Upd(int a1, int b1, int a2, int b2) {
}

void dfs(int x, int p) {
    id[x] = x, off[id[x]] = 0, ans[x] = 0, cnt[x] = 1;
    Map[id[x]][0] = 1;
    for(auto it : G[x]) {
        if(it == p) continue;
        dfs(it, x); ++off[id[it]];
        if(Map[id[it]].size() > Map[id[x]].size()) {
            swap(id[it], id[x]);
            ans[x] = ans[it] + 1;
            cnt[x] = cnt[it];
        }
        for(auto it2 : Map[id[it]]) {
            int key = it2.fi + off[id[it]] - off[id[x]];
            Map[id[x]][key] += it2.se;
            int sum = Map[id[x]][key];
            key += off[id[x]];
            if(cnt[x] < sum)
                cnt[x] = sum, ans[x] = key;
            else if(cnt[x] == sum && ans[x] > key)
                ans[x] = key;
        }
    }
}

int main() {
    scanf("%d", &n);
    for(int i = 1, u, v; i < n; ++i) {
        scanf("%d%d", &u, &v);
        G[u].PB(v), G[v].PB(u);
    }
    dfs(1, 0);
    for(int i = 1; i <= n; ++i) printf("%d\n", ans[i]);
    return 0;
}
