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

const int maxn = 2e5;

int n, xx[maxn+5], yy[maxn+5];
int tot, seg[maxn+5];
vector<int> G1[maxn+5], G2[maxn+5];
int ans[maxn+5];
unordered_set<int> Set;
int rem[maxn+5], all;

int main() {
    int _; scanf("%d", &_);
    while(_--) {
        int y0;
        scanf("%d%d", &n, &y0);
        tot = 0;
        seg[++tot] = 0;
        REP(i,1,n) {
            scanf("%d%d", xx+i, yy+i);
            seg[++tot] = xx[i];
            seg[++tot] = xx[i]+1;
            yy[i] = abs(yy[i]-y0);
        }
        sort(seg+1, seg+1+tot);
        tot = unique(seg+1, seg+1+tot) - seg - 1;
        REP(i,1,tot) G1[i].clear(), G2[i].clear(), ans[i] = 0;
        REP(i,1,n) {
            int rk = lower_bound(seg+1, seg+1+tot, xx[i]) - seg;
            G1[rk].PB(yy[i]-xx[i]);
            G2[rk].PB(yy[i]+xx[i]);
        }

        Set.clear();
        for(int i = 1; i <= tot; ++i) {
            ans[i] += G1[i].size() + Set.size();
            all = 0;
            for(auto v : G1[i]) {
                if(Set.find(v) != Set.end()) rem[++all] = v;
                else Set.insert(v);
            }
            REP(k,1,all) Set.erase(rem[k]);
        }

        Set.clear();
        for(int i = tot; i >= 1; --i) {
            ans[i] += Set.size();
            all = 0;
            for(auto v : G2[i]) {
                if(Set.find(v) != Set.end()) rem[++all] = v;
                else Set.insert(v);
            }
            REP(k,1,all) Set.erase(rem[k]);
        }
        int mi = n+1, mx = 0;
        REP(i,1,tot)
            mi = min(mi, ans[i]), mx = max(mx, ans[i]);
        printf("%d %d\n", mi, mx);
    }
    return 0;
}
