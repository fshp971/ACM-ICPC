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

int n, m, kk;
int r1[maxn+5], c1[maxn+5], r2[maxn+5], c2[maxn+5], ti[maxn+5];
int col[maxn*2+5], tot;

vector<pii> v1[maxn+5], v2[maxn+5];

vector<pii> eve[maxn+5];
int fa[maxn+5], inc[maxn+5];
LL add[maxn+5];
int find(int x) { return fa[x]==x ? x : fa[x] = find(fa[x]); }

int main() {
    int _; scanf("%d", &_);
    while(_--) {
        scanf("%d%d%d", &n, &m, &kk);
        tot = 0;
        REP(i,1,kk) {
            scanf("%d%d%d%d", r1+i, c1+i, r2+i, c2+i);
            ti[i] = (r1[i]==r2[i]) ? 1 : 2;
            col[++tot] = c1[i], col[++tot] = c2[i];
            fa[i] = i;
        }
        sort(col+1, col+1+tot);
        tot = unique(col+1, col+1+tot) - col - 1;
        REP(i,1,n) v1[i].clear(), eve[i].clear(), inc[i] = 0, add[i] = 0;
        REP(i,1,tot) v2[i].clear();
        REP(i,1,kk) {
            c1[i] = lower_bound(col+1, col+1+tot, c1[i]) - col;
            c2[i] = lower_bound(col+1, col+1+tot, c2[i]) - col;
            v1[r1[i]].PB( MP(c2[i],i) );
            if(r1[i] < r2[i]) {
                v1[r2[i]].PB( MP(c2[i],i) );
                add[r1[i]] += 1;
                add[r2[i]+1] -= 1;
            }
            else {
                add[r1[i]] += col[c2[i]] - col[c1[i]] + 1;
                add[r1[i]+1] -= col[c2[i]] - col[c1[i]] + 1;
            }

            v2[c1[i]].PB( MP(r2[i],i) );
            if(c1[i] < c2[i]) v2[c2[i]].PB( MP(r2[i],i) );

            ++inc[r1[i]];
        }
        PER(i,n,1) {
            if(v1[i].size() == 0) continue;
            sort(v1[i].begin(), v1[i].end());
            if(i+1>n || v1[i+1].size()==0) continue;
            for(auto pp : v1[i]) {
                int x = pp.se;
                auto it = lower_bound(v1[i+1].begin(), v1[i+1].end(), pii(c1[x],-1));
                for(;it!=v1[i+1].end();++it) {
                    if(c1[x]<=c2[it->se] && c1[it->se]<=c2[x])
                        eve[i+1].PB( MP(x,it->se) );
                }
            }
        }
        PER(i,tot,1) {
            if(v2[i].size() == 0) continue;
            sort(v2[i].begin(), v2[i].end());
            if(i+1>tot || col[i]+1 != col[i+1]) continue;
            for(auto pp : v2[i]) {
                int x = pp.se;
                auto it = lower_bound(v2[i+1].begin(), v2[i+1].end(), pii(r1[x],-1));
                //printf("it->fi = %d, it->se = %d\n", it->fi, it->se);
                for(;it!=v2[i+1].end();++it) {
                    if(r1[x]<=r2[it->se] && r1[it->se]<=r2[x])
                        eve[ max(r1[it->se],r1[x]) ].PB( MP(x,it->se) );
                }
            }
        }

        /*
        PER(i,tot,1) {
            printf("v2[%d]:", i);
            for(auto it : v2[i]) {
                printf("(%d,%d) ", it.fi, it.se);
            }
            puts("");
        }
        puts("");
        */

        int now = 0;
        LL sum = 0, fk = 0;
        for(int i = 1; i <= n; ++i) {
            now += inc[i];
            fk += add[i];
            sum += fk;
            //printf("add[%d] = %lld\n", i, add[i]);
            for(auto pp : eve[i]) {
                //printf("pp.fi = %d, pp.se = %d\n", pp.fi, pp.se);
                if(find(pp.fi) != find(pp.se)) --now, fa[find(pp.fi)] = find(pp.se);
            }
            printf("%lld %d\n", sum, now);
        }
    }
    return 0;
}
