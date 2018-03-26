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

const int maxn = 6e6;

int tot = 0;
map<int,int> Id;
vector<pii> vec[maxn + 5];

int GetId(int x) {
    if(Id.find(x) != Id.end()) return Id[x];
    return Id[x] = tot++;
}

int main() {
    freopen("brick-count.in", "r", stdin);
    freopen("brick-count.out", "w", stdout);
    int n;
    scanf("%d", &n);
    for(int i = 1, r, c; i <= n; ++i) {
        scanf("%d%d", &r, &c);
        vec[GetId(r)].PB(MP(c,c));
    }
    LL ans = 0;
    while(Id.size()) {
        pii x = *Id.begin();
        if(vec[x.se].size() == 0) {
            Id.erase(Id.begin());
            continue;
        }
        int nid = GetId(x.fi + 1);
        sort(vec[x.se].begin(), vec[x.se].end());
        for(int i = 0; i < vec[x.se].size(); ++i) {
            pii tmp = vec[x.se][i];
            while(i+1 < vec[x.se].size() && vec[x.se][i+1].fi <= tmp.se + 2)
                tmp.se = max(tmp.se, vec[x.se][i+1].se), ++i;
            ans += ((tmp.se - tmp.fi) >> 1) + 1;
            if(tmp.fi+1 <= tmp.se-1)
                vec[nid].PB( MP(tmp.fi+1, tmp.se-1) );
        }
        Id.erase(Id.begin());
    }
    printf("%lld\n", ans);
    return 0;
}
