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
typedef unsigned long long ULL;
typedef pair<int,int> pii;

const ULL base = 19260817;
const int maxn = 50;

set<ULL> Set;
int n, ai[maxn+5];
int kk, q, ui[maxn+5], vi[maxn+5];
int ans = 0;

void dfs(int pt) {
    if(pt==0) { ++ans; return; }
    if(ai[ui[pt]] > ai[vi[pt]]) return;
    dfs(pt-1);
    swap(ai[ui[pt]], ai[vi[pt]]);
    dfs(pt-1);
    swap(ai[ui[pt]], ai[vi[pt]]);
}

int main() {
    int _; scanf("%d", &_);
    while(_--) {
        scanf("%d%d%d", &n, &kk, &q);
        REP(i,1,kk) scanf("%d%d", ui+i, vi+i);
        Set.clear();
        ans = 0;
        for(int i = 1; i <= n; ++i) {
            for(int k = 1; k <= n; ++k) {
                ai[k] = i;
                int pt = 1;
                for(int j = 1; j <= n; ++j) {
                    if(j==i) continue;
                    if(pt==k) ++pt;
                    ai[pt++] = j;
                }
                ULL ha = 0;
                REP(j,1,n) ha = ha*base + ai[j];
                if(Set.find(ha) != Set.end()) continue;
                Set.insert(ha);
                dfs(kk);
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
