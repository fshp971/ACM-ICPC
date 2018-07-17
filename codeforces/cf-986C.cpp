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

const int maxn = 1 << 22;

int n, m;
bool ok[maxn + 5], vist[maxn + 5];
queue<int> que;

int main() {
    scanf("%d%d", &n, &m);
    for(int i = 1, a; i <= m; ++i)
        scanf("%d", &a), ok[a] = 1;
    int Mask = (1 << n) - 1, ans = 0;
    for(int i = 0; i <= Mask; ++i) {
        if(!ok[i]) continue;
        ++ans;
        ok[i] = 0, vist[Mask-i] = 1;
        que.push(Mask-i);
        while(!que.empty()) {
            int x = que.front(); que.pop();
            if(ok[x]) {
                ok[x] = 0, vist[Mask-x] = 1;
                que.push(Mask-x);
            }
            for(int k = 0; k < n; ++k) {
                if((x>>k&1) && !vist[x-(1<<k)])
                    vist[x-(1<<k)] = 1, que.push(x-(1<<k));
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}
