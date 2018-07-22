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

int n, kk, xi[maxn + 5], yi[maxn + 5];
int m, dx[maxn + 5];
int val[maxn + 5];
vector<int> G[maxn + 5];
priority_queue<LL> que;
multiset<LL> Set1, Set2;

int main() {
    scanf("%d%d", &n, &kk);
    for(int i = 1; i <= n; ++i)
        scanf("%d%d", xi + i, yi + i), dx[i] = xi[i];
    sort(dx + 1, dx + 1 + n);
    m = unique(dx+1, dx+1+n) - dx - 1;
    for(int i = 1; i <= n; ++i) {
        int id = lower_bound(dx+1, dx+1+m, xi[i]) - dx;
        G[id].PB(i);
        val[i] = yi[i] + xi[i] - dx[1];
    }
    sort(val + 1, val + 1 + n);
    LL now = 0, nx = dx[1];
    for(int i = 1; i <= kk; ++i) now += val[i], Set1.insert(val[i]);
    for(int i = kk+1; i <= n; ++i) Set2.insert(val[i]);
    LL ans = now;
    for(int i = 1; i <= m; ++i) {
        LL sb = dx[i] - dx[1];
        while(que.size() && Set2.size() && que.top()+sb >= *(Set2.begin()) - sb) {
            now -= que.top() + sb; que.pop();
            auto it = Set2.begin();
            int hh = *it;
            Set2.erase(it); Set1.insert(hh);
            now += hh - sb;
        }
        for(auto it : G[i]) {
            int hh = yi[it] + xi[it] - dx[1];
            if(Set2.find(hh) != Set2.end()) {
                auto it2 = Set2.find(hh);
                Set2.erase(it2);
            }
            else {
                auto it2 = Set1.find(hh);
                Set1.erase(it2);
                que.push( yi[it]-sb );
            }
        }
        ans = min(ans, now);
        now -= LL(Set1.size()) * (dx[i+1] - dx[i]);
        now += LL(que.size()) * (dx[i+1] - dx[i]);
    }
    printf("%lld\n", ans);
    return 0;
}
