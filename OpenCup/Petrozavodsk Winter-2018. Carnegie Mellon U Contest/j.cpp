#include<cstdio>
#include<cstdlib>
#include<cstring>
#include<cmath>
#include<ctime>
#include<cassert>
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

const int maxn = 2000;

struct Tree {
    int bit[maxn*2 + 5][maxn + 5];
    void clear() { mem(bit, 0); }
    void Upd(int i, int j, int v) {
        for(; i <= maxn*2; i += i&(-i)) {
            for(int jj = j; jj <= maxn; jj += jj&(-jj))
                bit[i][jj] = max(bit[i][jj], v);
        }
    }
    int Get(int i, int j) {
        int res = 0;
        for(; i; i -= i&(-i)) {
            for(int jj = j; jj; jj -= jj&(-jj))
                res = max(res, bit[i][jj]);
        }
        return res;
    }
} bt1, bt2;
// bt1 stand for the lower_slope_tree
// bt2 stand for the higher_slope_tree

int n, m, seg1[maxn + 5], seg2[maxn + 5];
bool cnt[maxn + 5][maxn + 5];
map<int,int> Map;

int main() {
    scanf("%d", &n);
    REP(i,1,n) scanf("%d", seg1 + i), Map[seg1[i]] = 0;
    scanf("%d", &m);
    REP(i,1,m) scanf("%d", seg2 + i), Map[seg2[i]] = 0;
    int T = 0;
    for(auto it = Map.begin(); it != Map.end(); ++it) it->se = (++T);
    REP(i,1,n) seg1[i] = Map[seg1[i]];
    REP(i,1,m) seg2[i] = Map[seg2[i]];
    int ans = 0;
    bt1.clear(), bt2.clear();
    for(int i = n; i >= 1; --i) {
        for(int k = m; k >= 1; --k) {
            if(seg1[i] == seg2[k]) cnt[i][k] |= 1;
            cnt[i][k] |= cnt[i+1][k] | cnt[i][k+1];
        }
    }
    for(int i = 1; i <= n; ++i) {
        for(int k = 1; k <= m; ++k) {
            if(seg1[i] != seg2[k]) continue;

            int tmp = bt1.Get(seg1[i]-1, k-1) + 1;
            bt2.Upd(maxn*2-seg1[i]+1, k, tmp);
            if(tmp == 1 && cnt[i+1][k+1]) ++tmp;
            ans = max(ans, tmp);

            tmp = bt2.Get(maxn*2-seg1[i], k-1) + 1;
            bt1.Upd(seg1[i], k, tmp);
            if(tmp == 1 && cnt[i+1][k+1]) ++tmp;
            ans = max(ans, tmp);
        }
    }
    printf("%d\n", ans);
    return 0;
}
